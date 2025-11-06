inputNum = 1
pares = 0
impares = 0
while inputNum!=0:
    inputNum=int(input('Insira um numero: '))
    if inputNum%2==0 and inputNum!=0:
        pares +=1
    elif inputNum!=0:
            impares +=1
print('Foram introduzidos %d numeros pares e %d numeros impares' %(pares,impares))