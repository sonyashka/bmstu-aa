from matplotlib import colorbar
import numpy as np
import matplotlib
import matplotlib.pyplot as plt

def get_data(path):
    f = open(path)
    x = []
    y = []
    for line in f:
        line = line.split()
        x.append(int(line[0]))
        y.append(int(line[1]))
    return x, y

def print_sorted_keys(x, y, title, path):
    fig, axes = plt.subplots(4, 1)

    axes[0].bar(x[:500], y[:500],color='plum')
    axes[1].bar(x[500:1000], y[500:1000], color='plum')
    axes[2].bar(x[1000:1500], y[1000:1500], color='plum')
    axes[3].bar(x[1500:2200], y[1500:2200], color='plum')

    max_cmps = max(y)
    min_cmps = min(y)
    avg_cmps = sum(y) / len(y)

    for i in range(4):
        axes[i].set_facecolor('white')
        axes[i].axhline(y = min_cmps, xmin = 0, xmax = 2200, color="green")
        axes[i].axhline(y = avg_cmps, xmin = 0, xmax = 2200, color="yellow")
        axes[i].axhline(y = max_cmps, xmin = 0, xmax = 2200, color="red")
    axes[0].set_title(title)

    axes[1].set_facecolor('white')
    axes[2].set_facecolor('white')
    axes[3].set_facecolor('white')
    fig.set_facecolor('plum')
    fig.set_figwidth(35)
    fig.set_figheight(10)

    plt.savefig(path + "_keys.png")

def print_sorted_cmps(x, y, title, path):
    for i in range(0, len(x) - 1):
        for j in range(0, len(x) - i - 1):
            if y[j] > y[j + 1]:
                x[j], x[j + 1] = x[j + 1], x[j]
                y[j], y[j + 1] = y[j + 1], y[j]

    sub_x = [i for i in range(len(x))]
    
    fig, axes = plt.subplots(1, 1)

    axes.bar(sub_x, y, color='plum')

    max_cmps = max(y)
    min_cmps = min(y)
    avg_cmps = sum(y) / len(y)

    axes.axhline(y = min_cmps, xmin = 0, xmax = 2200, color="green")
    axes.axhline(y = avg_cmps, xmin = 0, xmax = 2200, color="yellow")
    axes.axhline(y = max_cmps, xmin = 0, xmax = 2200, color="red")

    axes.set_facecolor('white')
    axes.set_title(title)

    axes.set_facecolor('white')
    fig.set_facecolor('plum')
    fig.set_figwidth(35)
    fig.set_figheight(10)

    plt.savefig(path + "_cmps.png")

def create_pics(path, plot_title, pics_title):
    x, y = get_data(path)
    print_sorted_keys(x, y, plot_title, pics_title)
    print_sorted_cmps(x, y, plot_title, pics_title)

create_pics("data/log_bf.txt", 'Полный перебор', 'brute_force')
create_pics("data/log_bs.txt", 'Бинарный поиск', 'binary_search')
create_pics("data/log_ff.txt", 'Частотный анализ', 'frequency')