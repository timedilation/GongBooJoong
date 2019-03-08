import pandas as pd
import numpy as np
from collections import OrderedDict
from bokeh.plotting import figure
from bokeh.core.properties import value
from bokeh.io import export_png

title = "Lat/Req together"
plot = figure(plot_width=2000, plot_height=600, title=title)
plot.title.align = 'center';
plot.title.text_font_size = '30pt';
for fname in ["BICG_16to1", "BICG_1to4"]:
    df_cpu = pd.read_csv("data/LatReq/"+fname+"_LatReq_CPU.csv", names=["tick", "val"])
    df_gpu = pd.read_csv("data/LatReq/"+fname+"_LatReq_GPU.csv", names=["tick", "val"])
    df_cpu['gpu'] = df_gpu['val']

    length = len(df_cpu.index)
    maxTick = max(df_cpu['tick'].max(), df_gpu['tick'].max())
    gpuMax = df_gpu['val'].max()
    cpuMax = df_cpu['val'].max()
    maxVal = max(gpuMax, cpuMax)
    x_range = (0, length)
    y_range = (0, maxVal)
    color1 = ''
    color2 = ''
    marker = ''
    if fname == "BICG_16to1":
        color1 = 'blue'
        color2 = 'red'
        marker = 'circle'
    else:
        color1 = 'skyblue'
        color2 = 'pink'
        marker = 'square'
    plot.scatter(df_cpu['tick'], df_cpu['val'], size=3, marker=marker, fill_color=color1, line_color=None, alpha=1)
    plot.scatter(df_cpu['tick'], df_cpu['gpu'], size=3, marker=marker, fill_color=color2, line_color=None, alpha=1)

#plot.line(df_cpu['tick'], df_cpu['val'], line_width=1, line_color='blue')
#plot.line(df_cpu['tick'], df_cpu['gpu'], line_width=1, line_color='red')
output_fname="out/together_LatReq.png"
export_png(plot, filename=output_fname)
