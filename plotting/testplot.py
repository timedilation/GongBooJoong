import pandas as pd
import numpy as np
import datashader as ds
from datashader import transfer_functions as tf
from datashader.utils import export_image
from collections import OrderedDict
from sklearn.preprocessing import MinMaxScaler
from datashader.bokeh_ext import InteractiveImage
import bokeh.plotting as bp
from bokeh.io import export_png
from bokeh.models import BoxZoomTool
import xarray as xr
col = ''
color = ''
def base_plot(x_range, y_range, tools='pan,wheel_zoom,reset'):
    p = bp.figure(tools=tools, plot_width=2000, plot_height=600,
        x_range=x_range, y_range=y_range, outline_line_color=None,
        min_border=0, min_border_left=0, min_border_right=0,
        min_border_top=0, min_border_bottom=0)
    return p
def create_image(x_range, y_range, w, h):
    cvs = ds.Canvas(x_range=x_range, y_range=y_range, plot_width=w, plot_height=h)
#    agg = cvs.points(df, 'tick', col)
    aggs = OrderedDict((c, cvs.points(df, 'tick', c)) for c in ['cpuLat', 'gpuLat'])
#    img = tf.shade(agg, cmap=[color])
    imgs = [tf.shade(aggs[i], cmap=[c]) for i,c in zip(['cpuLat', 'gpuLat'],['blue', 'red'])]
    img = tf.stack(*imgs)
    return img

fnames = ["BICG_1to4", "BICG_16to1"]
gpuLatMax = 0
cpuLatMax = 0
scalerMax = 0
flag = False
for fname in fnames:
    df = pd.read_pickle(fname+"_lat.pkl")
    if gpuLatMax == 0:
        flag = True
        gpuLatMax = df['gpuLat'].max()
        cpuLatMax = df['cpuLat'].max()
        scalerMax = gpuLatMax
    else:
        scalerMax = df['cpuLat'].max()*gpuLatMax/cpuLatMax
        
    scaler = MinMaxScaler(feature_range=(0, scalerMax))
    df[['cpuLat']] = scaler.fit_transform(df[['cpuLat']])
    if flag:
        df[['gpuLat']] = scaler.fit_transform(df[['gpuLat']])
    x_range = (0, df['tick'].max())
    y_range = (0, gpuLatMax)
    col = 'cpuLat'
    color = 'blue'
        
#export_image(img, fname+"_mixLat", background="white")
    p = base_plot(x_range=x_range, y_range=y_range)
    InteractiveImage(p, create_image)
    filename = fname+'_mixLat.png'
    export_png(p, filename=filename)
	

    
#for (attr, color) in [('cpuLat','blue'), ('gpuLat', 'red'),('cpuReq','blue'), ('gpuReq', 'red')]:
#    df_new=df.drop(df[df[attr] == 0].index)
#end = df['tick'].max()
#length = len(df.index)

'''
#y_range = (min(cpuLatMin, gpuLatMin), max(df_new['cpuLat'].max(), df_new['gpuLat'].max()))
#y_range = (gpuLatMin, gpuLatMax)
#y_range = (df_new[attr].min(), df_new[attr].max())
#print(df.describe())

#height = int(600*704/476)
#agg = cvs.points(df_new, 'tick', attr)
#agg = cvs.line(df, 'tick', 'cpuLat')
#img = tf.shade(agg, cmap=[color])
#export_image(img, fname+"_"+attr, background="white")
#img = tf.stack(*reversed(imgs))
'''
