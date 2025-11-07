#ex4

frutas = list(["maçã", "banana", "laranja", "abacaxi", "uva", "morango"])
frutas_longas = []
n = len(frutas)
i = 0
while i in range (n):
    if len(frutas[i]) >= 5:
        frutas_longas.append(frutas[i])
    i+=1
print("As frutas que tinham mais de 5 letras são: ", frutas_longas)
