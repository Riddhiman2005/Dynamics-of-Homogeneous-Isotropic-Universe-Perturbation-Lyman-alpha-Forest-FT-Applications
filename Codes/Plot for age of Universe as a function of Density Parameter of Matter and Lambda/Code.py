import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from scipy.integrate import quad

x_init=np.linspace(0.1,0.5,80)    #Array for values of omega_m
y_init=np.linspace(0.5,0.9,80)    #Array for values of omega_lambda
x=[]
y=[]
z=[]



for i in x_init:
    for j in y_init:
        intg,err=quad(lambda a:(1/(np.sqrt((i/a)+a**2*j))),0,1)
        age=intg/67.74*1000
        x.append(i)
        y.append(j)
        z.append(age)

x1,y1=np.meshgrid(x_init,y_init)
z=np.array(z)
print(len(z))
z_new=np.reshape(z,(len(x_init),len(y_init)))
CS = plt.contour(x1,y1,z_new,30)
plt.clabel(CS, inline=1,fontsize=10)
plt.xlabel('Density parameter of matter')
plt.ylabel('Density parameter of lambda')
plt.title('Plot for age of universe as a function of density parameter of matter and lambda')
plt.show()
