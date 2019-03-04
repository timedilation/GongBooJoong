import pandas as pd
import numpy as np
import datashader as ds
from datashader import transfer_functions as tf
from datashader.utils import export_image
from collections import OrderedDict
from sklearn.preprocessing import MinMaxScaler

fname = "BICG_16to1"
'''
df = pd.read_csv(fname+".txt", names=["tick","debugLabel","cpuLat", "gpuLat", "cpuReq", "gpuReq"] )
start = df.iloc[0]['tick']
df['tick'] = df['tick'].apply(lambda x:x-start)
#for (attr, color) in [('cpuReq','blue'), ('gpuReq', 'red')]:
df_new = df.loc[:, ['tick', 'cpuReq', 'gpuReq']]
df_new = df_new.groupby(pd.cut(df['tick'], np.arange(0, maxTick, 200000))).sum()
df_new.to_pickle("req16toq.pkl")
'''
df_new = pd.read_pickle("req16toq.pkl")
maxTick = 1049935*200000
col = np.arange(0,maxTick,200000)
print(col.size)
print(df_new['tick'].size)
df_new['tick'] = col;
gpuReqMax = df_new['gpuReq'].max()
#gpuReqMax = df_new['cpuReq'].min()
scaler = MinMaxScaler(feature_range=(0, gpuReqMax))
df_new[['cpuReq']] = scaler.fit_transform(df_new[['cpuReq']])
#print(df_new.columns.values)
#print(df_new.head)
#    df_new=df.drop(df[df[attr] == 0].index)
#end = df['tick'].max()
#length = len(df.index)
x_range = (0, maxTick)
y_range = (0, gpuReqMax)
#y_range = (0, max(cpuReqMax, gpuReqMax))

#print(df_new.head)
cvs = ds.Canvas(x_range=x_range, y_range=y_range, plot_width=2000, plot_height=600)
#agg = cvs.points(df_new, 'tick', attr)
aggs = OrderedDict((c, cvs.points(df_new, 'tick', c)) for c in ['cpuReq', 'gpuReq'])
#agg = cvs.line(df, 'tick', 'cpuLat')
#img = tf.shade(agg, cmap=[color])
imgs = [tf.shade(aggs[i], cmap=[c]) for i,c in zip(['cpuReq', 'gpuReq'],['blue', 'red'])]
#export_image(img, fname+"_"+attr, background="white")
#img = tf.stack(*reversed(imgs))
img = tf.stack(*imgs)
export_image(img, fname+'_req', background="white")
