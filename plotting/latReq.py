import pandas as pd
import numpy as np
import datashader as ds
from datashader import transfer_functions as tf
from datashader.utils import export_image
from collections import OrderedDict
from sklearn.preprocessing import MinMaxScaler

fname = "BICG_16to1"
df = pd.read_csv(fname+".txt", names=["tick","debugLabel","cpuLat", "gpuLat", "cpuReq", "gpuReq"] )
df= df.loc[:, ['tick', 'gpuLat']]
maxTick = df['tick'].max()
df= df.groupby(pd.cut(df['tick'], np.arange(0, maxTick, 200000))).sum()
col = np.arange(0,maxTick,200000)
df['tick'] = col;
df.to_pickle(fname+"_gpuLat_grouped.pkl")
print(df.tail)

'''
df['val'] = df['gpuLat']/df['gpuReq']
df.drop(columns=['gpuLat', 'gpuReq'])

x_range = (0, df['tick'].max())
y_range = (0, df['val'].max())


cvs = ds.Canvas(x_range=x_range, y_range=y_range, plot_width=2000, plot_height=600)
cvs = ds.Canvas(x_range=x_range, y_range=y_range, plot_width=2000, plot_height=600)
agg = cvs.points(df,'tick','val')
#aggs = OrderedDict((c, cvs.points(df_new, 'tick', c)) for c in ['cpuReq', 'gpuReq'])
#agg = cvs.line(df, 'tick', 'cpuLat')
img = tf.shade(agg, cmap='red')
#imgs = [tf.shade(aggs[i], cmap=[c]) for i,c in zip(['cpuReq', 'gpuReq'],['blue', 'red'])]
#export_image(img, fname+"_"+attr, background="white")
#img = tf.stack(*reversed(imgs))
#img = tf.stack(*imgs)
export_image(img, fname+'_lat/req', background="white")
'''
