
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

