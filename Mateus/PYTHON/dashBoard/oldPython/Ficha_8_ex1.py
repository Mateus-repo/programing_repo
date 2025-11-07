#ex1
sum = 0
frase = input("Digite uma frase: ")
def whateverDif(fraseTemp, whatever):
    sumTemp = 0
    for i in frase:
        if i != whatever:
            sumTemp += 1
    return sumTemp
sum = whateverDif(frase, " ")
print("Carateres: ", sum)
frase = frase.split(' ')
sum = whateverDif(frase, "")
print("Palavras: ", sum)
