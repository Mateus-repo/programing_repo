#ex5
from selectors import SelectSelector
from traceback import print_tb
from unittest import case
import statistics

def analisar_media(list):
    temp=statistics.mean(list)
    print(temp)

def analisar_maior(list):
    n = len(list)
    for i in range(n - 1):
        for j in range(n - i - 1):
            if int(list[j]) < int(list[j + 1]):
                list[j], list[j + 1] = list[j + 1], list[j]
    print( list )

def analisar_menor(list):
    n = len(list)
    for i in range(n - 1):
        for j in range(n - i - 1):
            if int(list[j]) > int(list[j + 1]):
                list[j], list[j + 1] = list[j + 1], list[j]
    print( list )

def analisar_soma(list):
    n = len(list)
    soma = 0
    for i in range(n):
        soma += int(list[i])
    print( soma )

def analisar_lista(list):
    n = len(list)
    if n == 0:
        return -1
    else:
        j=1
        while j !=0:
            analisis = int(input('\nQuer analisar a lista como (clique no número correspondente)?\n Quer analisar a média?.[1]\n Quer analisar o maior?.[2]\n Quer analisar o menor?.[3]\n Quer analisar a soma?..[4]\n Quer sair?.............[5]\n'))
            match analisis:
                case 1:
                    print('A média é: ')
                    analisar_media(list)
                case 2:
                    print('O maior é:')
                    analisar_maior(list)
                case 3:
                    print('O menor é: ')
                    analisar_menor(list)
                case 4:
                    print('A soma dá: ')
                    analisar_soma(list)
                case 5:
                    print('A terminar processo!')
                    return 0
                case _:
                    print('Opção desconhecida! Tente de novo.')
            j += 1
    return 0

lista = list(map(int, input("Escreva numeros: ").split()))
analisar_lista(lista)
