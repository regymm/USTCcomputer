cimport cython
import math

miu0 = 4 * math.pi * 1e-7
epsilon0 = 8.85e-12
e = 1.602e-19
me = 9.31e-31

rlimit = 9e9

#store items in space
#item in particle_list is always updated
particle_list = []
static_B_list = []
static_E_list = []

# 向量类，三个分量
cdef class vec:
    cdef public double x, y, z
    def __cinit__(self,x = 0, y = 0, z = 0):  
       self.x = x
       self.y = y
       self.z = z
    def __dealloc__(self):  
       del(self)
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

#重力加速度
g = vec(0, 0, -9.8)

#数乘和点乘
def mul_num(double num, vec v):
    return vec(v.x * num, v.y * num, v.z * num)
def mul_dot(vec vec1, vec vec2):
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z
def dist(vec pos1, vec pos2):
    return math.sqrt((pos1.x - pos2.x)**2 + (pos1.y - pos2.y)**2 + (pos1.z - pos2.z)**2)

#场类，电场、磁场、重力场等
#警告：未对高斯定理、环路定理检验！！
#警告：用国际单位制！
cdef class field:
    cdef public func
    #func: vec(x, y, z), t -> vec(Ex, Ey, Ez)
    def __cinit__(self, func):
        self.func = func

cdef class particle:
    cdef public double q, m
    cdef public int fixed, dead
    cdef public vec pos, vel
    #pos and vel is class vec
    #fixed:is the particle can't be moved?
    def __cinit__(self, vec pos=vec(0, 0, 0), vec vel=vec(0, 0, 0), double q=0, double m=0, int fixed=0, int dead=0):
        self.pos = pos
        self.vel = vel
        self.q = q
        self.m = m
        self.fixed = fixed
        self.dead=dead
    def __str__(self):
        return 'pos: %3g, %3g, %3g\nvel: %3g, %3g, %3g\nq: %3g, m: %3g' % (self.pos.x, self.pos.y, self.pos.z, self.vel.x, self.vel.y, self.vel.z, self.q, self.m)

#获得一点电、磁场，背景静态场+粒子动态场，可能与时间有关
def get_field_B(vec pos, double t, int enablebp):
    B = vec(0, 0, 0)
    for item in static_B_list:
        B = B + item.func(pos, t)
    for item in particle_list:
        if item.dead == 0:
            #如果考虑粒子间相互作用以及对电场贡献，则全部活粒子进行运算
            #如果不考虑，则只计算固定粒子的贡献
            if enablebp == 1 or (enablebp == 0 and item.fixed == 1):
                #如果距离过小认为是一个粒子，在自己处没有贡献，不予考虑
                if dist(pos, item.pos) > 1e-10:
                    B = B + mul_num(miu0 / (4 * math.pi) * item.q / (dist(pos, item.pos) ** 3), item.vel * (pos - item.pos))
        return B
def get_field_E(vec pos, double t, int enablebp):
    E = vec(0, 0, 0)
    for item in static_E_list:
        E = E + item.func(pos, t)
    for item in particle_list:
        if item.dead == 0:
            if enablebp == 1 or (enablebp == 0 and item.fixed == 1):
                if dist(pos, item.pos) > 1e-8:
                    E = E + mul_num(1 / (epsilon0 * 4 * math.pi) * item.q / (dist(pos, item.pos) ** 3), pos - item.pos)
        return E

def add_particle(particle p):
    particle_list.append(p)
    #返回数组的index
    return len(particle_list) - 1

#主函数，当前时间、时间间隔，可选择不考虑B
#enablebp: 开启粒子互相作用和产生的电磁场
def update_main(double t, double dt, int enableE=1, int enableB=1, int enableg=1, int enablebp=1):
    #先算好场强，保证所有粒子同时不分先后被update
    if enableE == 1:
        particle_E_list = []
        for item in particle_list:
            particle_E_list.append(get_field_E(item.pos, t, enablebp))
    if enableB == 1:
        particle_B_list = []
        for item in particle_list:
            particle_B_list.append(get_field_B(item.pos, t, enablebp))
    for i in range(len(particle_list)):
        #if out of range, make it dead 
        if dist(particle_list[i].pos, vec()) > rlimit:
            particle_list[i].dead = 1
        #如果不是固定粒子则update
        if particle_list[i].fixed != 1 and particle_list[i].dead == 0:
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
