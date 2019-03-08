import pandas as pd
import numpy as np
from collections import OrderedDict
from bokeh.plotting import figure
from bokeh.core.properties import value
from bokeh.io import export_png

fname = "BICG_16to1"
df_cpu = pd.read_csv("data/Seperate/"+fname+"_Sep_LatReq_CPU.csv", names=["tick", "lat", "req"])
df_gpu = pd.read_csv("data/Seperate/"+fname+"_Sep_LatReq_GPU.csv", names=["tick", "lat", "req"])

for attr in ["lat", "req"]:
    length = len(df_cpu.index)
    maxTick = max(df_cpu['tick'].max(), df_gpu['tick'].max())
    gpuMax = df_gpu[attr].max()
    cpuMax = df_cpu[attr].max()
    maxVal = max(gpuMax, cpuMax)
    x_range = (0, length)
    y_range = (0, maxVal)

    title = fname+"_"+attr
    plot = figure(plot_width=2000, plot_height=600, title=title)
    plot.title.align = 'center';
    plot.title.text_font_size = '30pt';
    plot.scatter(df_cpu['tick'], df_cpu[attr], size=3, marker='circle', fill_color='blue', line_color=None, alpha=1)
    plot.scatter(df_gpu['tick'], df_gpu[attr], size=3, marker='circle', fill_color='red', line_color=None, alpha=1)
    output_fname="out/"+title+".png"
    export_png(plot, filename=output_fname)

'''
cvs = ds.Canvas(x_range=x_range, y_range=y_range, plot_width=2000, plot_height=600)
aggs = OrderedDict((c, cvs.points(df_cpu, 'tick', c)) for c in ['val', 'gpu'])
imgs = [tf.shade(aggs[i], cmap=[c]) for i,c in zip(['val', 'gpu'],['blue', 'red'])]
img = tf.stack(*imgs)
export_image(img, fname+'_LatReq', background="white")
'''
