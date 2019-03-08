import pandas as pd
import numpy as np

fname = "BICG_1to4"
df_cpu = pd.read_csv("data/Seperate/"+fname+"_Sep_LatReq_CPU.csv", names=["tick", "lat", "req"])
df_gpu = pd.read_csv("data/Seperate/"+fname+"_Sep_LatReq_GPU.csv", names=["tick", "lat", "req"])

for attr in ["lat", "req"]:
    length = len(df_cpu.index)
    maxTick = max(df_cpu['tick'].max(), df_gpu['tick'].max())
    gpuMax = df_gpu[attr].max()
    cpuMax = df_cpu[attr].max()
    print(fname+" "+attr+" GPU "+str(gpuMax)+" CPU "+str(cpuMax));
