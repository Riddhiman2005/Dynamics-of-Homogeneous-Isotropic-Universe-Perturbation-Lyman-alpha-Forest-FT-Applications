import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d

omega_m=0.3
omega_lambda=0.7
omega_r=8.2E-5
x=[]
y=[]

for z in range(0,10000,10):
    H=70*np.sqrt(omega_m*(1+z)**3 + omega_r*(1+z)**4 + omega_lambda)
    x.append(1+z)
    y.append(H)

fig=plt.figure()
ax=fig.add_subplot(1,1,1)
ax.plot(x,y)
ax.set_xscale('log')
ax.set_yscale('log')
plt.show()
