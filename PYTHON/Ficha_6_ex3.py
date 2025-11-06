
print( 'escreva a lista de notas: ')

a = []
i = 1
op = 's'
while i != 0:
    if (op == 's'):
        a.append(int(input()))
    else:
        break
    op = input('quer continuar(s/n)? ')
print(a)
print(sum(a) / len(a))