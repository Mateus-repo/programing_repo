#ex2
import os
happening = True
lista = []
placeholder = {"nome" : "", "satisfaction" : "", "sugestion" : ""}

def checkSORN(temp):
    match temp.lower():
        case "sim" | "claro" | "si" | "incrivel" | "incrível":
            temp = "s"
        case "não" | "nao" | "na" | "nunca" | "horrivel" | "horrível":
            temp = "n"
    return temp

while happening:
    tempSatis = ""
    placeholderTemp = placeholder.copy()
    placeholderTemp["nome"] = input("Qual o seu nome?: ")

    while tempSatis.lower() != "s" and tempSatis.lower() != "n":
        tempSatis = input("Está satisfeito com a biblioteca? (s/n): ")
        tempSatis=checkSORN(tempSatis)

    placeholderTemp["satisfaction"] = tempSatis
    sugestionQuestion = ""

    while sugestionQuestion.lower() != "s" and sugestionQuestion.lower() != "n":
        sugestionQuestion = input("Quer sugerir alguma coisa? (s/n): ")
        sugestionQuestion=checkSORN(sugestionQuestion)

    if(sugestionQuestion.lower() == "s"):
        placeholderTemp["sugestion"] = input("Qual seria a sua sugestão?: ")

    continuar = ""
    while continuar.lower() != "s" and continuar.lower() != "n":
        continuar = input("Quer adicionar mais uma pessoa? (s/n): ")
        continuar=checkSORN(continuar)

    lista.append(placeholderTemp)
    if(continuar == "n"):
        happening = False

print()
print(lista)
if not open("listaPeople.txt", 'w'):
    f = open("listaPeople.txt", 'x')
else:
    os.remove("listaPeople.txt")
    f = open("listaPeople.txt", 'x')
f = open("listaPeople.txt", 'w')
f.write(str(lista))
f.close()