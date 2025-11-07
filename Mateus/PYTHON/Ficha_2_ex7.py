#ex7
size = 7
mid = size / 2
mid=round(mid)
for num3 in range (1,size+1):
    espacos = 0
    ast = 0
    if(mid>=num3):
        espacos = mid - num3
        ast = 1 + 2 * (num3 - 1)
    else:
        espacos = 1 * (num3 - mid)
        ast = 1 + 2 * (num3 - 1) - 4 * (num3 - mid)
    for num4 in range(1, size +1):
        if(espacos - num4 >= 0):
            print(' ', end="")
    for num5 in range(1, size + 1):
        if (ast - num5 >= 0):
            print('*', end="")
    print()