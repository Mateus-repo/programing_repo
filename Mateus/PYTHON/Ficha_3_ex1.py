resp = "S"
num = [0,0,0]
while resp != 'N':
    num[0] = int(input("Insira um numero: "))
    num[1]+=num[0]
    num[2]+=1
    resp = str(input('Quer continuar? [S/N] : ')).upper().strip()[0]
num[0]=(num[1]/num[2])
print('Inseriu %d números e a média é %.2f' %(num[2] , num[0]))