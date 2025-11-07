#ex3
listaDeWords = ['a', 'b', '1', 'c', 'b', 'a', 'd', 'c', 'joao', 'joão']
dicionario = {}
def addToDictionaryKey(lista):
    dicionarioTemp = {}
    for i in range(0,len(lista)):
        if(lista[i] not in dicionarioTemp):
            dicionarioTemp[lista[i]] = 1
        else:
            dicionarioTemp[lista[i]] +=1
    return dicionarioTemp
dicionario = addToDictionaryKey(listaDeWords)
for i in dicionario:
    if(dicionario[i] >= 2):
        print(i, dicionario[i])
print()
print(dicionario)