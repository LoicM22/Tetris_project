import numpy as np
import matplotlib.pyplot as plt
from pylab import *

#l = [1]
#print (np.median(np.array(l)))

#l = [3,1,2]
#print (np.median(np.array(l)))

#l = [1,2,500,100,3,4,12,52,103]
#print (np.median(np.array(l)))
k = 0
with open("accypt.txt", "r") as tf:
    lines = tf.readlines()
 
    for line in lines:
     print(line)

def convert_list(lines):
    for index, item in enumerate(lines):
        lines[index] = float(item)
    return lines

temps=list(range(len(lines)))

for k in range (len(lines)) :
    temps [k] = k*200

lines = convert_list(lines)
#print (temps)
#print (lines)
#print(lines[2]+lines[1])
#print(np.median(np.array(lines)))
plt.figure()
plt.plot(temps,lines)

title("Variation de l'accélération en allant en pause en fonction du temps")


temps2=list(range(len(lines)-4))

for k in range (len(lines)-4) :
    temps2 [k] = k*200
N =len(lines)
a = 0
lines2 = list (range(5))
linesM = list (range(N-4))
for i in range (N-4):
    a=i
    for j in range (2):
        lines2[j]= lines[a]
        a=a+1
    linesM[i]=np.median(np.array(lines2))
plt.figure()
plt.plot (temps2,linesM)
title("Variation de l'accélération avec filtre median")
plt.figure()
plt.plot(np.array(lines[0:-2])-np.array(lines[1:-1]))
plt.show()
