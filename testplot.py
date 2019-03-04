import pandas as pd
import numpy as np
import datashader as ds
from datashader import transfer_functions as tf
from datashader.utils import export_image
from collections import OrderedDict
from sklearn.preprocessing import MinMaxScaler

fname = "BICG_16to1"
df = pd.read_csv(fname+".txt", names=["tick","debugLabel","cpuLat", "gpuLat", "cpuReq", "gpuReq"] )
start = df.iloc[0]['tick']
df['tick'] = df['tick'].apply(lambda x:x-start)
#for (attr, color) in [('cpuLat','blue'), ('gpuLat', 'red'),('cpuReq','blue'), ('gpuReq', 'red')]:
#    df_new=df.drop(df[df[attr] == 0].index)
#end = df['tick'].max()
#length = len(df.index)
df_new = df.loc[:, ['tick', 'cpuLat', 'gpuLat']]
df_new.to_pickle("BICG_lat_16to1.pkl")
gpuLatMin = 0
#gpuLatMax = 476418750
gpuLatMax = df_new['gpuLat'].max()

scaler = MinMaxScaler(feature_range=(gpuLatMin, gpuLatMax))
df_new[['cpuLat']] = scaler.fit_transform(df_new[['cpuLat']])

x_range = (0, df_new['tick'].max())
#y_range = (min(cpuLatMin, gpuLatMin), max(df_new['cpuLat'].max(), df_new['gpuLat'].max()))
#y_range = (gpuLatMin, gpuLatMax)
y_range = (gpuLatMin, 476418750)
#y_range = (df_new[attr].min(), df_new[attr].max())
#print(df.describe())

#height = int(600*704/476)
height = 600
cvs = ds.Canvas(x_range=x_range, y_range=y_range, plot_width=2000, plot_height=height)
#agg = cvs.points(df_new, 'tick', attr)
aggs = OrderedDict((c, cvs.points(df_new, 'tick', c)) for c in ['cpuLat', 'gpuLat'])
#agg = cvs.line(df, 'tick', 'cpuLat')
#img = tf.shade(agg, cmap=[color])
imgs = [tf.shade(aggs[i], cmap=[c]) for i,c in zip(['cpuLat', 'gpuLat'],['blue', 'red'])]
#export_image(img, fname+"_"+attr, background="white")
#img = tf.stack(*reversed(imgs))
img = tf.stack(*imgs)
export_image(img, fname+"_mixLat_2", background="white")
