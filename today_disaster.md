## 2019.1.언젠가
python file 이름을 package_name.py로 하고 그 파일 안에서 ```import package```를 함
분명 패키지는 가져왔는데 안에 함수가 하나도 없다고 뜸.
버전 검사하고 다른 환경에서 해보고 별짓을 다해봄(심지어 다른 환경에서도 파일 이름 똑같이 써서 안됨)

## 2019.3.21
```memcpy(src, dst, ... ) ``` 로 썼다.
결과가 전부 0이 나왔다.

## 2019.4.28
```if(prev_count + 10000 > curr_count) { ... } ```
prev, curr 둘다 0인데 if문 안에 계속 들어감.

## 2019.5.28
와 한달만임
```/usr/include/signal.h:30:1: error: expected initializer before ‘extern’```
```support/common.h:51:1: error: expected initializer before ‘typedef’```
첨부한 첫번째 헤더 파일에서 이런 오류가 자꾸 떴는데 다른 헤더에서 함수 정의하고 마지막에 ;를 안찍어서였음
