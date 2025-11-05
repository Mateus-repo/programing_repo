#ex2

nome = input( 'Introduza o seu nome completo: ' )
temp = nome.split( )

i = 0
for i in range(len(temp)):
    if 'pereira' == temp[i].lower():
        print('true')