def MDC(num1, num2):
    num1 = int(num1)
    num2 = int(num2)
    if num1 == num2:
        return num1
    elif num1 > num2:
        maior = num1
        menor = num2
    else:
        maior = num2
        menor = num1
    div = menor
    while True:
        print(f"Div = {div}")
        if maior % div == 0:
            return div
        if div == menor:
            div /= 2
        else:
            div -= 1
        div = int(div)
print(MDC(12, 18))

