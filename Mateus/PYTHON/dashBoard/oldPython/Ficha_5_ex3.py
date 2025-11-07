#ex3
import string

def lookfor (letraTemp, fraseTemp):
    n = int(len(fraseTemp))
    apperanceLetra = [0, 0, 0]# [0] = vezes que o E estava presente, [1] posição onde apareceu E pela primeira vez, [2] posição onde apareceu E pela ultima vez
    for i in range(n):
        lowerTemp=letraTemp.lower()
        upperTemp=letraTemp.upper()
        if lowerTemp == fraseTemp[i] or upperTemp == fraseTemp[i]:
            if(apperanceLetra[1] == 0):
                apperanceLetra[1] = i
            apperanceLetra[2] = i
            apperanceLetra[0] += 1
    return apperanceLetra[0], apperanceLetra[1], apperanceLetra[2]

apperanceE = [0,0,0]
letra = chr(69) # Em ascii 69 = E
frase = str(input('Digite uma frase: '))
apperanceE[0], apperanceE[1], apperanceE[2] = lookfor(letra, frase)
print('A letra \"%c\" apareceu %d vezes, a primeira vez que apareceu foi na posição %d e a ultima vez foi na posição %d' %(letra, apperanceE[0], apperanceE[1], apperanceE[2]))