#ex3
ver = 5
hor = 5
for j in range( 1,ver +1):
    if j == 1 or j == ver:
        for x in range (0, hor):
            print('*', end="")
    else:
        spaces = hor - 2
        print("*", end="")
        for nig in range (spaces):
            print(" ", end="")
        print("*", end="")
    print('')

