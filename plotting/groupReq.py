import pandas as pd
import numpy as np
from collections import OrderedDict
from bokeh.plotting import figure
from bokeh.core.properties import value
from bokeh.io import export_png

fname = "BICG_16to1"
df_cpu = pd.read_csv("data/"+fname+"_LatReq_CPU.csv", names=["tick", "val"])
df_gpu = pd.read_csv("data/"+fname+"_LatReq_GPU.csv", names=["tick", "val"])
df_cpu['gpu'] = df_gpu['val']

length = len(df_cpu.index)
maxTick = max(df_cpu['tick'].max(), df_gpu['tick'].max())
gpuMax = df_gpu['val'].max()
cpuMax = df_cpu['val'].max()
maxVal = max(gpuMax, cpuMax)
x_range = (0, length)
y_range = (0, maxVal)

title = fname_"Lat/Req"
plot = figure(plot_width=2000, plot_height=600, title=title)
plot.title.align = 'center';
plot.title.text_font_size = '30pt';
#plot.scatter(df_cpu['tick'], df_cpu['val'], size=3, marker='circle', fill_color='blue', line_color=None, alpha=1)
#plot.scatter(df_cpu['tick'], df_cpu['gpu'], size=3, marker='circle', fill_color='red', line_color=None, alpha=1)
plot.line(df_cpu['tick'], df_cpu['val'], line_width=1, line_color='blue')
plot.line(df_cpu['tick'], df_cpu['gpu'], line_width=1, line_color='red')
output_fname="out/"+fname+"_LatReq_200_line.png"
export_png(plot, filename=output_fname)
