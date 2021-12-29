import serial

ser = serial.Serial('/dev/ttyACM0',115200)
f = open('gyr.txt','a')
n=0
while n< 500:
    f.write(ser.readline().decode('utf-8'))
    print(n)
    n=n+1
f.close()
# f = open('accypt2.txt','a')

