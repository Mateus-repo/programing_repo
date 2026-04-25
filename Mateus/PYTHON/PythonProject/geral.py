def numPrimos(num):
    num = int(num)
    if num <= 1:
        return False
    if num == 2 or num % 2 != 0:
        div = 2
        while div <= (num/2):
            if num % div == 0:
                return False
            div += 1
        return True
    return False



def potencia(base, expoente):
    base = int(base)
    expoente = int(expoente)
    return base ** expoente

def MMC(num1, num2):
    num1 = int(num1)
    num2 = int(num2)
    if num1 > num2: maior = num1; menor = num2
    if num2 > num1: maior = num2; menor = num1
    i=1
    while True:
        multiplo = maior * i
        if multiplo % menor == 0:
            return multiplo
        i += 1

def MDC(num1, num2):
    num1 = int(num1)
    num2 = int(num2)
    if num1 > num2: maior = num1; menor = num2
    if num2 > num1: maior = num2; menor = num1
    div = menor
    while True:
        if maior % div == 0:
            return div
        if div == menor:
            div /= 2
        else:
            div -= 1
        div = int(div)

print(numPrimos(97))
print(potencia(2,13))
print(MMC(6,8))
print(MDC(12,18))
