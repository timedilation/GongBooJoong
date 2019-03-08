import pandas as pd

df = pd.read_csv("data/BICG_1to4.txt", names=["tick","debugLabel","cpuLat", "gpuLat", "cpuReq", "gpuReq"] )
#df= df.loc[:, ['tick', 'cpuLat', 'cpuReq']]
start = df.iloc[0]['tick']
df['tick'] = df['tick'].apply(lambda x:x-start)
df.to_csv("BICG_1to4_tickadj.csv")
