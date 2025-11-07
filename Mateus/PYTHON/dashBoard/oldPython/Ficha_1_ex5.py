#ex5
num = input( "Digite um número: " )
if len(num)>3:
    print( "O dígito das dezenas é: %s" % ( num[len(num)-2] ))
else:
    print("O dígito das dezenas é: 0")