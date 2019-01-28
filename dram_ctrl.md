#gem5/src/mem/dram\_ctrl.cc
##Static Latency
- cpu처럼 메모리 컨트롤러 안에도 request를 처리하는 stage들이 나뉘어져(pipelined) 있다.
(Request를 decode하는 스테이지, scheduling하는 스테이지 등등) 이 때 각 단계에서 발생하는 latency는
거쳐야 하는 pipelining stage의 개수가 일정하기 때문에 static하다. gem5에서는 10 pipeline stages in
total at 500 MHz -> 2ns * 10 -> 20ns로 계산한 것으로 보인다.(추측..)
실제로 DRAM 데이터에 접근하면서 생기는 latency와는 무관한, 컨트롤러 자체에서 발생하는 latency이다. 
- stages들은 리퀘스트를 처리하는 frontend와 메모리와 통신하는 backend로 구분된다. read request가
write queue에서 정보를 읽어오는 경우 메모리에 접근하지 않으므로 frontend latency(20/2=10ns로 계산
한 것으로 추정)만 더해지며, 그렇지 않은 경우 memory까지 접근하므로 backend latency 또한 더해진다.
- 총 latency는 DRAM의(static latency + dynamic latency) + DRAM Controller의(static latency +
dynamic latency(queueing)) 로 계산된다. response를 올려보내기 전에 response\_time = curTick() +
static\_latency + pkt-\>headerDelay + pkt-\>payloadDelay으로 계산된다. 여기서 headerDelay, payloadDelay가 나머지 delay들과 관련이 있을 것으로 추측된다.


##recvTimingReq(PacketPtr pkt)
- totGap(request간의 간격)측정
- packet size를 dram burst size로 분할할 때의 개수 구함(이 때 만약에 packet size가 더 작더라도 offset을 고려해서 걸쳐 있다면 2개로 나뉨)
- read/write queue에 패킷 추가, 이 때 queue가 차있으면 numRdRetry/numWrRetry가 증가하고 재시도, 성공시 readReqs/writeReqs++, bytesReadSys/bytesWriteSys+=size
- read/write가 아닐 경우 Queue추가 없이 accessAndRespond바로 호출

##addToReadQueue(PacketPtr pkt, unsigned int pktCount)
- writeQueue에서 각 burstaddr를 통해 해당 데이터가 있으면 writeQueue에서 읽어옴.
- 찾지 못한경우 readQueue.push\_back(dram\_pkt)
- 만약 모든 dram\_pkt들이 writeQueue에서 발견된경우 바로 accessAndRespond(pkt, frontendLatency)가 콜됨
- 남아있는 경우 schedule(nextReqEvent, curTick()) 호출

##processNextReqEvent()
- 놀고있는 Rank가 있을 경우 진행
- bus 방향을 바꿈(Read-\>Write / Write-\>Read)
- bus상태가 read인데, read queue가 비어있을 경우 무언가 상태를 확인하고 write로 돌림.
- 비어있지 않을 경우: found\_read = chooseNext() 호출하여 처리할 request를 queue의 맨앞으로 돌림
- doDRAMAccess(dram\_pkt) 호출
- respQueue.push\_back(dram\_pkt) 호출

##doDRAMAccess(DRAMPacket\* dram\_pkt)
- DRAM관련 timing 설정

##processRespondEvent()
- split packet일경우 bursts를 전부 service한 후에 accessAndRespond콜. 그렇지 않은경우 바로 호출.
- queue에서 front삭제, queue가 비어있지 않을 경우 schedule new respondEvent, 비어있을 경우 drain이 끝났다는 signal보냄.


##frontend\_latency vs backend\_latency
\#pipeline latency of the controller and PHY, split into a
\#frontend part and a backend part, with reads and writes serviced
\#by the queues only seeing the frontend contribution, and reads
serviced by the memory seeing the sum of the two
static\_frontend\_latency = Param.Latency("10ns", "Static frontend latency")
static\_backend\_latency = Param.Latency("10ns", "Static backend latency")

##headerDelay, payloadDelay
\* The extra delay from seeing the packet until the header is
\* transmitted. This delay is used to communicate the crossbar
\* forwarding latency to the neighbouring object (e.g. a cache)
\* that actually makes the packet wait. As the delay is relative,
\* a 32-bit unsigned should be sufficient.
uint32\_t headerDelay;

\* The extra pipelining delay from seeing the packet until the end of
\* payload is transmitted by the component that provided it (if
\* any). This includes the header delay. Similar to the header
\* delay, this is used to make up for the fact that the
\* crossbar does not make the packet wait. As the delay is
\* relative, a 32-bit unsigned should be sufficient.
uint32\_t payloadDelay;
