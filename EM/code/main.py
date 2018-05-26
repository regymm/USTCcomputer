#!/usr/bin/env python3

'''
My Simple Simple Electromagnetic Simulation Engine
start on Sat May 26 20:29:34 CST 2018
'''

import math
import numpy as np

miu0 = 4 * math.pi * 1e-7
epsilon0 = 8.85e-12

# xlimit = 100
# ylimit = 100
# zlimit = 100
#向量类，三个分量
class vec:
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z
    def __add__(self, other):
        self.x += other.x
        self.y += other.y
        self.z += other.z
        return self
    def __radd__(self, other):
        if other == 0:
            return self
        return self.__add_(other)
    def __sub__(self, other):
        self.x -= other.x
        self.y -= other.y
        self.z -= other.z
        return self
    def __mul__(self, other):
        t = self
        self.x = t.y * other.z - t.z * other.y
        self.y = t.z * other.x - t.x * other.z
        self.z = t.x * other.y - t.y * other.x
    def __str__(self):
        return '%3g, %3g, %3g' % (self.x, self.y, self.z)
#数乘和点乘
def mul_num(num, v):
    return vec(v.x * num, v.y * num, v.z * num)
def mul_dot(vec1, vec2):
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z
def dist(pos1, pos2):
    return math.sqrt((pos1.x - pos2.x)**2 + (pos1.y - pos2.y)**2 + (pos1.z - pos2.z)**2)

#场类，电场、磁场、重力场等
#警告：未对高斯定理、环路定理检验！！
#警告：用国际单位制！
class field:
    #func: vec(x, y, z), t -> vec(Ex, Ey, Ez)
    def __init__(self, func):
        self.func = func
class particle:
    #pos and vel is class vec
    #fixed:is the particle can't be moved?
    def __init__(self, pos=vec(), vel=vec(), q=0, m=0, fixed=0):
        self.pos = pos
        self.vel = vel
        self.q = q
        self.m = m
        self.fixed = fixed
#store items in space
#item in particle_list is always updated
particle_list = []
static_B_list = []
static_E_list = []
#重力加速度
g = vec(0, 0, -9.8)
#获得一点电、磁场，背景静态场+粒子动态场，可能与时间有关
def get_field_B(pos, t):
    B = vec(0, 0, 0)
    for item in static_B_list:
        B = B + item.func(pos, t)
    for item in particle_list:
        #如果距离过小认为是一个粒子，不予考虑
        if dist(pos, item.pos) > 1e-8:
            B = B + mul_num(miu0 / (4 * math.pi) * item.q / (dist(pos, item.pos) ** 3), item.vel * (pos - item.pos))
    return B
def get_field_E(pos, t):
    E = vec(0, 0, 0)
    for item in static_E_list:
        E = E + item.func(pos, t)
    for item in particle_list:
        if dist(pos, item.pos) > 1e-8:
            E = E + mul_num(1 / (epsilon0 * 4 * math.pi) * item.q / (dist(pos, item.pos) ** 3), pos - item.pos)
    return E
def add_particle(p):
    particle_list.append(p)
    #返回数组的index
    return len(particle_list) - 1
# def remove_particle(i):
    # particle_list.remove(i)
#主函数，当前时间、时间间隔，可选择不考虑B
def update_main(t, dt, enableE=1, enableB=1, enableg=1):
    #先算好场强，保证所有粒子同时不分先后被update
    if enableE == 1:
        particle_E_list = []
        for item in particle_list:
            particle_E_list.append(get_field_E(item.pos, t))
    if enableB == 1:
        particle_B_list = []
        for item in particle_list:
            particle_B_list.append(get_field_B(item.pos, t))
    for i in range(len(particle_list)):
        #如果不是固定粒子则update
        if particle_list[i].fixed != 1:
            #update pos
            #dx = vdt
            particle_list[i].pos += mul_num(dt, item.vel)
            #update vel
            acc = vec()
            if enableg == 1:
                acc += g
            if enableE == 1:
                acc += mul_num(particle_list[i].q / particle_list[i].m, particle_E_list[i])
            if enableB == 1:
                acc += mul_num(particle_list[i].q / particle_list[i].m, particle_list[i].vel * particle_B_list[i])
            particle_list[i].vel += mul_num(dt, acc)

if __name__ == '__main__':
    time = 0
    timeend = 1
    dt = .005
    q1 = particle(vec(0, 0, 0), vec(0, 0, 0), q=1, m=1, fixed=1)
    q2 = particle(vec(1, 0, 0), vec(0, 0, 0), q=.2, m=1, fixed=0)
    h1 = add_particle(q1)
    h2 = add_particle(q2)
    q2arr = []
    while time < timeend:
        update_main(time, dt, enableg=0, enableB=0)
        q2arr.append(particle_list[h2].pos)
        time += dt
    for i in q2arr:
        print(i)

















