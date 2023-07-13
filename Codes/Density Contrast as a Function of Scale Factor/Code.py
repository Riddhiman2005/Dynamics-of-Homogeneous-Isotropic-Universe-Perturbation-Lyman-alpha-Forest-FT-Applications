import numpy as np 
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d 
from scipy.integrate import quad

a_list=np.linspace(0.00001,1,10000)
delta_list=[]
delta_list1=[]
H_0 = 67.74
omega_m=0.3
omega_lambda = 1-omega_m
for i in a_list:
	x=(i**2)*(H_0**2)*(omega_m/(i**3) + omega_lambda)
        
	intg,err = quad(lambda a: 1/((a**2)*(H_0**2)*(omega_m/(a**3)+omega_lambda))**(3.0/2),0,i)
	delta = np.sqrt(x)/i * intg
	delta_list.append(delta)


for i in a_list:
	x=(i**2)*(H_0**2)*(omega_m/(i**3))
        
	intg,err = quad(lambda a: 1/((a**2)*(H_0**2)*(omega_m/(a**3)))**(3.0/2),0,i)
	delta = np.sqrt(x)/i * intg
	delta_list1.append(delta)

fig=plt.figure()
ax=fig.add_subplot(111)
ax.plot(a_list,delta_list, label="0.3,0.7")
ax.plot(a_list,delta_list1,label="0.3,0")
ax.set_xlabel('Scale factor')
ax.set_ylabel('Density contrast')
ax.set_title('Density contrast as a function of scale factor')
ax.legend()
plt.show()
