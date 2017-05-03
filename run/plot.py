#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy, pandas

df1 = pandas.read_csv('data.csv', sep=' ') 
fig = plt.figure(figsize=(12,8))

# pitch
for i, pitch in enumerate(range(-80,81,5)):
    fig.clf()
    ax = fig.add_subplot(111)
    df2 = df1.loc[df1['pitch'] == pitch]
    grouped = df2.groupby(['velocity'])
    for key, group in grouped:
        group.plot('yaw', 'distance', label=key, ax=ax)
    ax.set_ylabel('distance to jack')
    ax.set_ylim([0, 30])
    ax.set_title('pitch = {}'.format(pitch))
    plt.legend(loc='upper right')
    fig.savefig('out_pitch_{}.png'.format(i), dpi=100, bbox_inches='tight')

# yaw
for i, yaw in enumerate(range(0,61,5)):
    fig.clf()
    ax = fig.add_subplot(111)
    df2 = df1.loc[df1['yaw'] == yaw]
    grouped = df2.groupby(['velocity'])
    for key, group in grouped:
        group.plot('pitch', 'distance', label=key, ax=ax)
    ax.set_ylabel('distance to jack')
    ax.set_ylim([0, 30])
    ax.set_title('yaw = {}'.format(yaw))
    plt.legend(loc='upper right')
    fig.savefig('out_yaw_{}.png'.format(i), dpi=100, bbox_inches='tight')

