stringVogals = str(input('Escreva uma palavra: '))
vogals=['A','E','I','O','U', 'a', 'e', 'i', 'o', 'u']
i=int(len(stringVogals))
numVogals=0
while i!=0:
    for j in range(len(vogals)):
        if stringVogals[i-1]==vogals[j]:
            numVogals+=1
    i-=1
print('A palavra tem %d vogais' % numVogals)
