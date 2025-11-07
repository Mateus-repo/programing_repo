#ex1

list = input( 'escreva a lista de numeros: ' )
list = list.split(' ')

for i in list:
    if int(i) % 2 == 0:
        print(i)

