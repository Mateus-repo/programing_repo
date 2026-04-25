def MMC(num1, num2):
    num1 = int(num1)
    num2 = int(num2)
    if num1 > num2:
        maior = num1
        menor = num2
    elif num1 < num2:
        maior = num2
        menor = num1
    else:
        return num1
    i=1
    while True:
        multiplo = maior * i
        if multiplo % menor == 0:
            return multiplo
        i += 1

print(MMC(18658, 32567567))