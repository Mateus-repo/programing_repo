#ex3
def potencia( base, expoente ):
    while( expoente >0 ):
        res =+ base * base
        expoente =- 1
    return ( res )

base = int( input( ' base?: ' ))
expoente = int( input( ' expoente?: ' ))

print( potencia( base, expoente ))