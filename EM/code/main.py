#!/usr/bin/env python3

'''
My Simple Simple Electromagnetic Simulation Engine
start on Sat May 26 20:29:34 CST 2018
'''

import math
import numpy as np
import copy
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from moviepy.video.io.bindings import mplfig_to_npimage
import moviepy.editor as mpy
import random
import datetime

from func import *

# miu0 = 4 * math.pi * 1e-7
# epsilon0 = 8.85e-12
# e = 1.602e-19
# me = 9.31e-31

# rlimit = 1e9
# 向量类，三个分量
# class vec:
    # def __init__(self, x=0, y=0, z=0):
        # self.x = x
        # self.y = y
        # self.z = z
    # def __add__(self, other):
        # self.x += other.x
        # self.y += other.y
        # self.z += other.z
        # return self
    # def __radd__(self, other):
        # if other == 0:
            # return self
        # return self.__add_(other)
    # def __sub__(self, other):
        # self.x -= other.x
        # self.y -= other.y
        # self.z -= other.z
        # return self
    # def __mul__(self, other):
        # t = self
        # self.x = t.y * other.z - t.z * other.y
        # self.y = t.z * other.x - t.x * other.z
        # self.z = t.x * other.y - t.y * other.x
    # def __str__(self):
        # return '%3g, %3g, %3g' % (self.x, self.y, self.z)
#数乘和点乘
# def mul_num(num, v):
    # return vec(v.x * num, v.y * num, v.z * num)
# def mul_dot(vec1, vec2):
    # return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z
# def dist(pos1, pos2):
    # return math.sqrt((pos1.x - pos2.x)**2 + (pos1.y - pos2.y)**2 + (pos1.z - pos2.z)**2)

#场类，电场、磁场、重力场等
#警告：未对高斯定理、环路定理检验！！
#警告：用国际单位制！
# class field:
    # #func: vec(x, y, z), t -> vec(Ex, Ey, Ez)
    # def __init__(self, func):
        # self.func = func
# class particle:
    # #pos and vel is class vec
    # #fixed:is the particle can't be moved?
    # def __init__(self, pos=vec(0, 0, 0), vel=vec(0, 0, 0), q=0, m=0, fixed=0, dead=0):
        # self.pos = pos
        # self.vel = vel
        # self.q = q
        # self.m = m
        # self.fixed = fixed
        # self.dead=dead
    # def __str__(self):
        # return 'pos: %3g, %3g, %3g\nvel: %3g, %3g, %3g\nq: %3g, m: %3g' % (self.pos.x, self.pos.y, self.pos.z, self.vel.x, self.vel.y, self.vel.z, self.q, self.m)
# #store items in space
# #item in particle_list is always updated
# particle_list = []
# static_B_list = []
# static_E_list = []
# #重力加速度
# g = vec(0, 0, -9.8)
# #获得一点电、磁场，背景静态场+粒子动态场，可能与时间有关
# def get_field_B(pos, t, enablebp):
    # B = vec(0, 0, 0)
    # for item in static_B_list:
        # B = B + item.func(pos, t)
    # for item in particle_list:
        # if item.dead == 0:
            # #如果考虑粒子间相互作用以及对电场贡献，则全部活粒子进行运算
            # #如果不考虑，则只计算固定粒子的贡献
            # if enablebp == 1 or (enablebp == 0 and item.fixed == 1):
                # #如果距离过小认为是一个粒子，在自己处没有贡献，不予考虑
                # if dist(pos, item.pos) > 1e-10:
                    # B = B + mul_num(miu0 / (4 * math.pi) * item.q / (dist(pos, item.pos) ** 3), item.vel * (pos - item.pos))
        # return B
# def get_field_E(pos, t, enablebp):
    # E = vec(0, 0, 0)
    # for item in static_E_list:
        # E = E + item.func(pos, t)
    # for item in particle_list:
        # if item.dead == 0:
            # if enablebp == 1 or (enablebp == 0 and item.fixed == 1):
                # if dist(pos, item.pos) > 1e-8:
                    # E = E + mul_num(1 / (epsilon0 * 4 * math.pi) * item.q / (dist(pos, item.pos) ** 3), pos - item.pos)
        # return E
# def add_particle(p):
    # particle_list.append(p)
    # #返回数组的index
    # return len(particle_list) - 1
# def remove_particle(i):
    # particle_list.remove(i)
# #主函数，当前时间、时间间隔，可选择不考虑B
# #enablebp: 开启粒子互相作用和产生的电磁场
# def update_main(t, dt, enableE=1, enableB=1, enableg=1, enablebp=1):
    # #先算好场强，保证所有粒子同时不分先后被update
    # if enableE == 1:
        # particle_E_list = []
        # for item in particle_list:
            # particle_E_list.append(get_field_E(item.pos, t, enablebp))
    # if enableB == 1:
        # particle_B_list = []
        # for item in particle_list:
            # particle_B_list.append(get_field_B(item.pos, t, enablebp))
    # for i in range(len(particle_list)):
        # #if out of range, make it dead 
        # if dist(particle_list[i].pos, vec()) > rlimit:
            # particle_list[i].dead = 1
        # #如果不是固定粒子则update
        # if particle_list[i].fixed != 1 and particle_list[i].dead == 0:
            # #update pos
            # #dx = vdt
            # particle_list[i].pos += mul_num(dt, item.vel)
            # #update vel
            # acc = vec()
            # if enableg == 1:
                # acc += g
            # if enableE == 1:
                # acc += mul_num(particle_list[i].q / particle_list[i].m, particle_E_list[i])
            # if enableB == 1:
                # acc += mul_num(particle_list[i].q / particle_list[i].m, particle_list[i].vel * particle_B_list[i])
            # particle_list[i].vel += mul_num(dt, acc)

if __name__ == '__main__':
    time = 0
    timeend = 10 * 2 * math.pi * e ** 2 / (4 * math.pi * epsilon0 * me)
    print(timeend)
    dt = .05
    #GIF or mp4 total time
    duration=5
    q1 = particle(vec(0, 0, 0), vec(0, 0, 0), q=-1 * e, m=0, fixed=1)
    q2 = particle(vec(100 + e ** 2 / (4 * math.pi * epsilon0 * me), 0, 0), vec(0, .707, .707), q=1 * e, m=1 * me, fixed=0)
    h1 = add_particle(q1)
    h2 = add_particle(q2)
    print(q1)
    print(q2)
    q2arr = []
    print(particle())
    print(vec())
    starttime = datetime.datetime.now()
    while time < timeend:
        # print('--')
        # q2arr.append(particle(vec(particle_list[h2].pos.x, particle_list[h2].pos.y, particle_list[h2].pos.z), vec(), 0, 0, 0, 0))
        q2arr.append(particle(vec(), vec(), 0, 0, 0, 0))
        # q2arr[-1].pos.x = particle_list[h2].pos.x
        q2arr[-1].pos.x = particle_list[h2].pos.x
        q2arr[-1].pos.y = particle_list[h2].pos.y
        q2arr[-1].pos.z = particle_list[h2].pos.z
        # print(q2arr[-1].pos)
        # print(particle_list[h2])
        update_main(time, dt, enableg=0, enableB=0, enablebp=1)
        time += dt
        # print(particle_list[h2])
    endtime = datetime.datetime.now()
    print('simulation done.')
    print('time: ', endtime - starttime)
    # for i in q2arr:
        # print(i)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    ax.scatter(q1.pos.x, q1.pos.y, q1.pos.z, color='green', lw=2)
    maindot = ax.scatter(q2arr[0].pos.x, q2arr[0].pos.y, q2arr[0].pos.z, color='yellow', lw=.2)
    #make and save GIF
    def make_frame_mpl(t):
        global maindot
        ii = int(t * timeend / (duration * dt))
        maindot.remove()
        maindot = ax.scatter(q2arr[ii].pos.x, q2arr[ii].pos.y, q2arr[ii].pos.z, color='red', lw=.2)
        # ax.scatter(random.randint(-2, 2), random.randint(-2, 2), random.randint(-2, 2), color='cyan', lw=.2)
        # ax.set_title(str(t))
        # maindot.set_xdata(q2arr[int(t / dt)].pos.x)
        return mplfig_to_npimage(fig)
    animation = mpy.VideoClip(make_frame_mpl, duration=duration)
    animation.write_gif("test.gif", fps=10)
    #plot to screen
    # for item in q2arr[1:15000:100]:
        # ax.scatter(item.x, item.y, item.z, color='cyan', lw=.2)
    for item in q2arr[::500]:
        # print(item)
        ax.scatter(item.pos.x, item.pos.y, item.pos.z, color='red', lw=.2)
    plt.show()

    


















