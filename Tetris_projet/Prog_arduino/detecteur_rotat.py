from re import I
import numpy as np
import matplotlib.pyplot as plt
from numpy.core.arrayprint import dtype_is_implied

data=np.loadtxt("gyr.txt")
state=np.array(data)
print(data.shape)
plt.figure()
plt.plot(data)

idState=0
sph=12000
spb=5000
snh=-12000
snb=-5000
t=0
etat=0
# flag=True
# xt=1000
# ping=0


# xt=0
flag=True
for x in data:

    if etat==0: 
        if x>=sph:
            etat=1
        elif x<=snh:
            etat=-1
    elif etat==1:
        etat=2
    elif etat==2:
        if x<=spb:
            etat=0
    elif etat==-1:
            etat=-2
    elif etat==-2:
        if x>=snb:
            etat=0


    if etat==0:
        idState = 0
    if etat==1:
        idState = 10000
    if etat==2:
        idState=1000
    if etat==-1:
        idState = -10000
    if etat==-2:
        idState=-1000



    # state[t]=0
    # diff=x-xt
    # xt=x

    # if x>10000 :
    #     if diff>0 and flag:
    #         state[t]=20000
    #         flag=False
    # elif x<-10000:
    #     if diff<0:
    #         state[t]=-20000



    

    # if x>=sp:
    #     testp=True
    # else:
    #     testp= False
    # if x<=sn:
    #     testn=True 
    # else:
    #     testn= False
    # if x<xt:
    #     testx= True
    # else:
    #     testx=False
    
    # if idState==0 and ping ==0:
    #     if testp:
    #         idState=10000
    #         ping=1
    #     elif testn:
    #         idState=-10000
    #         ping=-1
    # elif idState==10000 :
    #     if not testp and ping==1:
    #         ping=0
    #     idState=0
        
    # if idState==0 and ping==0:
    #     if testp:
    #         idState=10000
    #         ping=1
    #     elif testn:
    #         idState=-10000
    #         ping=-1
    # elif idState==-10000 and ping==-1:
    #     if not testn and ping==-1:
    #         ping=0
    #     idState=0

    # if idState==0:
    #     if testp:
    #         idState=10000
    #     elif testn:
    #         idState=-10000
    # elif idState==10000:
    #     if testx:
    #         idState=5000
    # elif idState==5000:
    #     if not testp:
    #         idState=0
    # if idState==0:
    #     if testp:
    #         idState=10000
    # elif idState==10000:
    #     if testx:
    #         idState=5000
    # elif idState==5000:
    #     if  not testp:
    #         idState=0
    # elif idState==-10000:
    #     if not testx:
    #          idState=-5000
    # elif idState==-5000:
    #     if not testn:
    #         idState= 0
    # xt=x  
    # if (idState==10000 or idState==-10000) and flag:
    #     print(t,x)
    #     flag = False  
    # elif idState==0:
    #     flag=True    
    state[t]=idState
    t=t+1 
       
plt.plot(state)
plt.show()