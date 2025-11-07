#ex2
sum = 0
frase = input('Digite uma frase: ')
for i in frase.lower():
    if  i == 'a' or i == 'e' or i == 'i' or i == 'o' or i == 'u':
        sum += 1
print(sum)