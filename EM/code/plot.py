#!/usr/bin/env python3

import math
# import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from moviepy.video.io.bindings import mplfig_to_npimage
import moviepy.editor as mpy
import datetime
import copy

from calc import *

particle_list_data = []

def read_a_particle(fin):
    s = fin.readline()
    if s == '':
        return None
    s = s.split(' ')
    p = particle(vec(), vec(), 0, 0, 0, 0)
    p.pos.x = float(s[0])
    p.pos.y = float(s[1])
    p.pos.z = float(s[2])
    p.vel.x = float(s[3])
    p.vel.y = float(s[4])
    p.vel.z = float(s[5])
    p.q = float(s[6])
    p.m = float(s[7])
    p.fixed = int(s[8])
    p.dead = int(s[9])
    return p
def read_a_particle_list(fin, N):
    pl = [0 for i in range(N)]
    for i in range(N):
        p = read_a_particle(fin)
        if p == None:
            return None
        pl[i] = p
    return pl

starttime = datetime.datetime.now()

fn = 'data.txt'
fin = open(fn, 'r')
dt = float(fin.readline())
N = int(fin.readline())
print(dt, N)
# print(read_a_particle_list(fin, N))
pl = read_a_particle_list(fin, N)
while pl != None:
    # particle_list_data.append(copy.deepcopy(pl))
    particle_list_data.append(pl)
    pl = read_a_particle_list(fin, N)
datanum = len(particle_list_data)
timestart = 0
timeend = datanum * dt
print(timeend)
fin.close()
print('read finished')

xmax = -9e9
xmin = 9e9
ymax = -9e9
ymin = 9e9
zmax = -9e9
zmin = 9e9
for pl in particle_list_data:
    for item in pl:
        xmax = max(xmax, item.pos.x)
        xmin = min(xmin, item.pos.x)
        ymax = max(ymax, item.pos.y)
        ymin = min(ymin, item.pos.y)
        zmax = max(zmax, item.pos.z)
        zmin = min(zmin, item.pos.z)

#未使用减少输出，输出每个点，
#第一个测试，圆周运动，真实时间7.78e4s，画图、视频总时间45s，数据137M，约3e6个数据
#模拟时间0.478秒（不输出文件，pypy3）,15.46秒（不输出文件，python3），6.33秒（输出文件,pypy3）,23.2秒（输出文件，python3）
#误差：247m --> 275m, 1.00m/s -> 0.95m/s
#浮点数：1e-15
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
ax.set_xlim(xmin, xmax)
ax.set_ylim(ymin, ymax)
ax.set_zlim(zmin, zmax)
#test 1
'''
#fixed q1
q1 = particle_list_data[0][0]
ax.scatter(q1.pos.x, q1.pos.y, q1.pos.z, color='green', lw=2)
maindot = ax.scatter(particle_list_data[0][1].pos.x, particle_list_data[0][1].pos.y, particle_list_data[0][1].pos.z, color='yellow', lw=.2)
#GIF or mp4 total time
duration=30
'''
#test 2
ax.scatter(0, 0, 0, color='green', lw=2)
xarr = [particle_list_data[i][0].pos.x for i in range(len(particle_list_data))]
yarr = [particle_list_data[i][0].pos.y for i in range(len(particle_list_data))]
zarr = [particle_list_data[i][0].pos.z for i in range(len(particle_list_data))]
ax.plot(xarr, yarr, zarr, color='g', lw=.4)
maindot = ax.scatter(particle_list_data[0][0].pos.x, particle_list_data[0][0].pos.y, particle_list_data[0][0].pos.z, color='yellow', lw=.2)
# plt.show()
duration = 4
#make and save GIF or mp4
def make_frame_mpl(t):
    ii = int(t * timeend / (duration * dt))
    #test 1
    '''
    global maindot
    global tit
    maindot.remove()
    maindot = ax.scatter(particle_list_data[ii][1].pos.x, particle_list_data[ii][1].pos.y, particle_list_data[ii][1].pos.z, color='red', lw=.2, \
            label='time = %2g, dist = %2g, vel = %2g' % (t * timeend / duration, dist(particle_list_data[ii][1].pos), dist(particle_list_data[ii][1].vel)))
    ax.legend()
    '''
    #test 2
    global maindot
    maindot.remove()
    maindot = ax.scatter(particle_list_data[ii][0].pos.x, particle_list_data[ii][0].pos.y, particle_list_data[ii][0].pos.z, color='red', lw=.2, \
            label='time = %2g, vel = %2g' % (t * timeend / duration, dist(particle_list_data[ii][0].vel)))
    ax.legend()

    return mplfig_to_npimage(fig)
animation = mpy.VideoClip(make_frame_mpl, duration=duration)
# animation.write_gif("test.gif", fps=10)
animation.write_videofile("test.mp4", fps=24)

endtime = datetime.datetime.now()
print('done.')
print('time: ', endtime - starttime)
