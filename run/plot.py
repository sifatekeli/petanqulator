#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy, pandas

def plot_YawDistance_Pitch(df1, fig, a, b, s):
    for i, pitch in enumerate(numpy.arange(a, b, s)):
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
        fig.savefig('out_yaw_distance_{}.png'.format(i), dpi=100, bbox_inches='tight')

def plot_PitchDistance_Yaw(df1, fig, a, b, s):
    for i, yaw in enumerate(numpy.arange(a, b, s)):
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
        fig.savefig('out_pitch_distance_{}.png'.format(i), dpi=100, bbox_inches='tight')

def plot_XZ_Velocity(df1, fig, a, b, s):
    for i, velocity in enumerate(numpy.arange(a, b, s)):
        fig.clf()
        ax = fig.add_subplot(111)
        df2 = df1.loc[df1['velocity'] == velocity]
        ax.plot(df2['xball'], df2['zball'], '.', markersize=1)
        ax.set_xlabel('xball')
        ax.set_ylabel('zball')
        ax.set_xlim([-8, 20])
        ax.set_ylim([-20, 20])
        ax.set_title('velocity = {}'.format(velocity))
        fig.savefig('out_xz_velocity_{}.png'.format(i), dpi=100, bbox_inches='tight')

def plot_XZ_Pitch(df1, fig, a, b, s):
    for i, pitch in enumerate(numpy.arange(a, b, s)):
        fig.clf()
        ax = fig.add_subplot(111)
        df2 = df1.loc[df1['pitch'] == pitch]
        ax.plot(df2['xball'], df2['zball'], '.', markersize=1)
        ax.set_xlabel('xball')
        ax.set_ylabel('zball')
        ax.set_xlim([-8, 20])
        ax.set_ylim([-20, 20])
        ax.set_title('pitch = {}'.format(pitch))
        fig.savefig('out_xz_pitch_{}.png'.format(i), dpi=100, bbox_inches='tight')

df1 = pandas.read_csv('data.csv', sep=' ') 
fig = plt.figure(figsize=(12,8))

plot_YawDistance_Pitch(df1, fig, -10, 81, 5)
plot_PitchDistance_Yaw(df1, fig, -70, 71, 5)
plot_XZ_Velocity(df1, fig, 1.0, 8.1, 0.5)
plot_XZ_Pitch(df1, fig, -10, 81, 5)

