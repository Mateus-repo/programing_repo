import time
senha = ""
tentativas = 3
while senha == "":
    senhaTemp = str(input("Digite sua senha: "))
    if len(senhaTemp) <= 6 and len(senhaTemp) >= 3:
        senha = senhaTemp
    else:
        tentativas-=1
        print('%d tentativas restantes. Máximo de 6 caracteres e mínimo de 3' % tentativas)
    if(tentativas == 0):
        print('Máximo de tentativas usadas, bloqueio ao acesso por 1 minuto')
        time.sleep(60)
        print('Acesso revogado')
        tentativas=3