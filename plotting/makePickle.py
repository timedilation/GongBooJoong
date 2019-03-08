import pandas as pd
import numpy as np

fnames = ["BICG_16to1"]
for fname in fnames:
    df = pd.read_csv(fname+".txt", names=["tick","debugLabel","cpuLat", "gpuLat", "cpuReq", "gpuReq"] )
    '''
    df= df.loc[:, ['tick', 'cpuLat', 'gpuLat']]
    df['tick'] = df['tick'].apply(lambda x:x-start)
    df.to_pickle(fname+"_lat.pkl")
    '''
    df= df.loc[:, ['tick', 'cpuReq', 'gpuReq']]
    start = df.iloc[0]['tick']
    df['tick'] = df['tick'].apply(lambda x:x-start)
    df.to_pickle(fname+"_req.pkl")
