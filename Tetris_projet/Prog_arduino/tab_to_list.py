 # # #

with open("accx1.txt", "r") as tf:
    lines = tf.readlines()
 
    for line in lines:
     print(line)

def convert_list(lines):
    for index, item in enumerate(lines):
        lines[index] = float(item)
    return lines

lines = convert_list(lines)

print (lines)

print(lines[2]+lines[1])
