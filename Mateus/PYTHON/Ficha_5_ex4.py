#ex4

def fazalgo( stringTemp ):
    n = int(len(stringTemp))
    temp = [0] * n
    for j in range(n):
        temp[j] = stringTemp[j]
    for i in range(n):
        if i % 2 == 0:
            temp[i]=stringTemp[i].lower()
        else:
            temp[i]=stringTemp[i].upper()
    stringTemp = "".join(temp)
    return stringTemp
string = str(input( 'Introduza uma palavra ou frase: ' ))
devolve = fazalgo( string )
print( devolve )
