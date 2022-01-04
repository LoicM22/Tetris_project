from re import I
import numpy as np
import matplotlib.pyplot as plt
from numpy.core.arrayprint import dtype_is_implied

data=np.loadtxt("accypt.txt")
state=np.array(data)
print(data.shape)
plt.figure()
plt.plot(data)

idState=0
sp=3
sn=-3
t=0
flag=True
for x in data:
    if x>=sp:
        testp=True
    else:
        testp= False
    if x<=sn:
        testn=True 
    else:
        testn= False

    if idState==0:
        if testp:
            idState=1
        elif testn:
            idState=3
    elif idState==1:
        if testn:
            idState=2
    elif idState==2:
         if not testn:
            idState=0
    if idState==0:
        if testp:
            idState=1
    elif idState==1:
        if testn:
            idState=2
    elif idState==2:
         if not testn:
            idState=0
    elif idState==3:
        if testp:
            idState=4
    elif idState==4:
        if not testp:
            idState= 0

    if (idState==1 or idState==3) and flag:
        print(t,x)
        flag = False  
    elif idState==0:
        flag=True    

    state[t]=idState
    t=t+1         
plt.plot(state)
plt.show()
