# 数理方程小论文-特殊函数在量子力学中的应用

**PB17000002**
**古宜民**

## 1.量子力学

量子力学是描述微观物质行为的物理学理论，能够解释经典物理学无法解释的现象，从根本上改变了人们对物理世界的认识，而其反直觉的行为直到现在对其仍没有统一的理解和诠释。

量子力学的时间演化公设由薛定谔方程描述：
$$
i\hbar\frac\partial{\partial t}|\psi(t)\rangle=H|\psi(t)\rangle
$$
其中$H$为系统哈密顿量算符，$|\psi(t)\rangle$为系统态右矢，$\hbar​$为普朗克常数。

如果要研究量子系统的运动演化，则需要对该薛定谔方程进行求解，尤其是要求能量本征态，则需要解偏微分方程的本征值问题$H|\phi\rangle=E_0|\phi\rangle​$，在求解过程中需要依赖数理方程知识，有时还需要用到特殊函数。

 动量空间波函数为$\Psi(\boldsymbol x,t)=\langle\boldsymbol x|\psi\rangle​$，取哈密顿量$H=\frac{\boldsymbol p^2}{2m}+V(\boldsymbol x)​$，则上式化为薛定谔时间相关波动方程：
$$
i\hbar\frac\part{\part t}\Psi(\boldsymbol x,t)=-\frac{\hbar^2}{2m}\nabla^2\Psi(\boldsymbol x,t)+V(\boldsymbol x)\Psi(\boldsymbol x,t)
$$
若该波函数为能量本征态，则可进行分离变量$\Psi(x,t)=\psi(x)\phi(t)​$，分离后的$\psi(x)​$满足时间无关波动方程：
$$
E\psi=-\frac{\hbar^2}{2m}\nabla^2\psi+V\psi
$$
而$\phi(t)​$为位相因子：
$$
\phi(t)=e^{-iEt/\hbar}
$$
于是，只要解时间无关波动方程即可。

## 2.三维空间中的波函数

由于一般势能V只与径向距离r有关，可使用球坐标系$(r,\theta,\phi)$，并分离变量。球坐标系中的Laplace算子为：
$$
\nabla^2=\frac1{r^2}\frac\part{\part r}(r^2\frac\part{\part r})+\frac1{r^2sin\theta}\frac\part{\part \theta}(sin\theta\frac\part{\part \theta})+\frac1{r^2{sin}^2\theta}(\frac{\part^2}{\part \phi^2})
$$
先对$r$和$(\theta,\phi)$分离变量，设：
$$
\psi(r,\theta,\phi)=R(r)Y(\theta,\phi)
$$
将二式带回薛定谔方程，得：
$$
\{\frac1R\frac d{dr}(r^2\frac{dR}{dr})-\frac{2mr^2}{\hbar^2}[V(r)-E]\}
+\frac1Y\{\frac1{sin\theta}\frac\part{\part\theta}(sin\theta\frac{\part Y}{\part\theta})+\frac1{sin^2\theta}\frac{\part^2}{\part\phi^2}\}=0
$$
此式将径向函数R和角向函数Y分离。于是可设：
$$
\{\frac1R\frac d{dr}(r^2\frac{dR}{dr})-\frac{2mr^2}{\hbar^2}[V(r)-E]\}=\lambda
\\
\frac1Y\{\frac1{sin\theta}\frac\part{\part\theta}(sin\theta\frac{\part Y}{\part\theta})+\frac1{sin^2\theta}\frac{\part^2}{\part\phi^2}\}=-\lambda
$$
若已知$V(r)$，则径向方程可解。为了得出一般解，继续角向函数Y的分离变量：
$$
Y(\theta, \phi)=\Theta(\theta) \Phi(\phi)
$$
带入方程，得：
$$
\left\{\frac{1}{\Theta}\left[\sin \theta \frac{d}{d \theta}\left(\sin \theta \frac{d \Theta}{d \theta}\right)\right]+\lambda\sin \theta^{2}\right\}+\frac{1}{\Phi} \frac{d^{2} \Phi}{d \phi^{2}}=0
$$
同样地，$\theta​$和$\phi​$坐标分离。可设：
$$
\frac{1}{\Theta}\left[\sin \theta \frac{d}{d \theta}\left(\sin \theta \frac{d \Theta}{d \theta}\right)\right]+\lambda\sin \theta^{2}=m^{2}
\\
\frac{1}{\Phi} \frac{d^{2} \Phi}{d \phi^{2}}=-m^{2}
$$
将分离常数设为$m^2​$也是为了后面计算方便。

$\Phi(\phi)​$坐标方程极为简单，解为：
$$
\Phi(\phi)=A e^{i m \phi}+B e^{-i m \phi}
$$
而为了使其保持简洁，令m可取到负数，且将常数因子吸收到$\Theta$中，得：
$$
\Phi(\phi)=e^{i m \phi}
$$
加以周期性边界条件$\Phi(\phi+2 \pi)=\Phi(\phi)$，则$e^{2\pi i m}=1$必须成立，则m必须为整数：
$$
m=0, \pm 1, \pm 2, \dots
$$
再考虑$\Theta(\theta)$：
$$
\sin \theta \frac{d}{d \theta}\left(\sin \theta \frac{d \Theta}{d \theta}\right)+\left[\lambda \sin \theta^{2}-m^{2}\right] \Theta=0
$$
其恰为$x=cos\theta$时的m阶伴随勒让德方程，只有当特征值$\lambda=l(l+1)$且$l$为非负整数时才可能存在边界$\pm1$处有界的解，而波函数明显应该满足在该处有界的条件。也正是因此，第二类伴随勒让德函数虽然数学上是该方程的解 但在物理上不能够存在。于是解为：
$$
\Theta(\theta)=A P_{l}^{m}(\cos \theta)
$$
而由于$|m|>l$时$P_l^m$为0，则要求$m$只可取从$-l$到$l$的$2l-1$个值。于是，
$$
l=0,1,2, \ldots ; \quad m=-l,-l+1, \ldots,-1,0,1, \ldots, l-1, l
$$
到此已经解得了径向势场中的波函数。最后一步便是概率守恒要求的归一化：$\langle\psi|\psi\rangle=1$，即$\int|\psi(\boldsymbol x,t)|dV=1$，本题中即为：
$$
\int|R|^{2} r^{2} d r \int|Y|^{2} \sin \theta d \theta d \phi=1
$$
不妨角向和径向分别归一化：
$$
\int_{0}^{\infty}|R|^{2} r^{2} d r=1
\\
\int_{0}^{2 \pi} \int_{0}^{\pi}|Y|^{2} \sin \theta d \theta d \phi=1
$$
归一化后的角向函数$Y(\theta,\phi)​$即为球谐函数(spherical harmonics)：
$$
Y_{l}^{m}(\theta, \phi)=\epsilon \sqrt{\frac{(2 l-1)(l-|m|) !}{4 \pi(l+|m|) !}} e^{i m \phi} P_{l}^{m}(\cos \theta)
$$
而由进一步量子力学推到，可知$l$和$m$与总轨道角动量$\boldsymbol L^2$和轨道角动量z方向分量$L_z$本征态有关：
$$
\boldsymbol L^2|l,m\rangle=l(l+1)\hbar^2|l,m\rangle
\\
L_z|l,m\rangle=m \hbar|l,m\rangle
$$
而原子在沿z方向均匀磁场中的能量$E=\boldsymbol B \boldsymbol \mu=B_z \mu_z$，其中磁矩$\mu_z=-g_l \mu_B m$与$m$成正比。所以$l$和$m​$称为轨道角量子数和磁量子数。

## 3.氢原子 

#### 参考文献：

[1] 季孝达，薛兴恒，陆英，宋立功.数学物理方程（第二版）

[2] David J.Griffiths. Introduction to Quantum Mechanics

[3]  J.J. Sakurai. Modern Quantum Mechanics, Second Edition