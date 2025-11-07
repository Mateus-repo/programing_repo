#ex2
from array import array

espacos = 0
size = 5 #em linhas

def LastArrayToZeros (tamanho):
    return [0]*(tamanho+2)
last = LastArrayToZeros(size)
tempLast = LastArrayToZeros(size)
for i in range(1, size+1):
    espacos = size - i
    for space in range(0, espacos):
        print(" ", end="")
    if (i == 1):
        print(1)
        last[1] = 1
        continue
    for j in range(0, i):
        this = last[j] + last[j+1]
        print(this, end=" ")
        tempLast[j+1]=this
    print()
    last = tempLast
    tempLast = LastArrayToZeros(size)