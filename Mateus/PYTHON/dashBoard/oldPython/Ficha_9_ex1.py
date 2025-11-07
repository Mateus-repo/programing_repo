#ex 1

def addToDictionaryKey( lista ):
    dicionarioTemp = { }
    for i in range(0, len( lista )):
        if( lista[ i ] not in dicionarioTemp ):
            dicionarioTemp[ lista[ i ]] = 1
        else:
            dicionarioTemp[ lista[ i ]] += 1
    return dicionarioTemp

esq = input( ' Escolha o tipo de input:  1 - terminal;  2 - arquivo: ' )

if( esq == '1' ):
    listaDeWords = input('escreva a lista de palavras: ').split(' ')

elif( esq == '2' ):
    f = open("text.txt", 'r')
    listaDeWords = f.read().split(' ')
    f.close()

else:
    print( 'erro' )

dicionario = addToDictionaryKey( listaDeWords )

for i in dicionario:
    if(dicionario[i] >= 2):
        print(i, dicionario[i])