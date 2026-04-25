# Importar o módulo random que contém funções para gerar números aleatórios
import random
import subprocess
import os

MIN_DEFAULT = 1
MAX_DEFAULT = 100

def clearScreen():
    comando = 'cls' if os.name == 'nt' else 'clear'
    subprocess.run(comando, shell=True)

def getPlayerNum():
    num = -1
    while True:
        try:
            num = int(input(f"Introduz o teu numero de player (tem de maior ou igual a 0): "))
            if(num >=0):
                break
        except ValueError:
            print("O input têm de ser um número inteiro!!")
            print()
    clearScreen()
    return num

def mostrarTop5(players_temp):
    clearScreen()
    # Filtrar apenas jogadores que jogaram (tentativas > 0)
    jogadores_validos = [(num, tentativas) for num, tentativas in players_temp.items() if tentativas > 0]
    
    if not jogadores_validos:
        print("Não havia jogadores registados!")
        return
    print("=== TOP 5 MELHORES JOGADORES ===")
    print()
    # Ordenar por número de tentativas (menor para maior)
    top_jogadores = sorted(jogadores_validos, key=lambda x: x[1])
    
    # Mostrar apenas os 5 primeiros (ou menos se não houver 5)
    for i, (player_num, tentativas) in enumerate(top_jogadores[:5], 1):
        print(f"{i}º lugar - Player #{player_num}: {tentativas} tentativas")
        
    print()

def correrJogo(players_temp):
    clearScreen()
    player_number = getPlayerNum()
    tentativa_counter = 0
    numero_aleatorio = random.randint(MIN_DEFAULT, MAX_DEFAULT)
    min = MIN_DEFAULT
    max = MAX_DEFAULT
    palpite = -1
    jogoAcabou = False
    while jogoAcabou == False:
        # Pedir ao utilizador para inserir um palpite
        # A função input() recolhe texto do utilizador
        # A função int() converte o texto para número inteiro
        tentativa_counter += 1
        while True:
            try:
                print(f"Player #{player_number}")
                print(f"Tentativa nº: {tentativa_counter}")
                palpite = int(input(f"Introduz o teu palpite entre {min} e {max} : "))
                break
            except ValueError:
                print("O input têm de ser um número inteiro!!")
                print()
        # Verificar se o palpite está correto
        # Usar estrutura condicional if/else para comparar os números
        clearScreen()
        if palpite == numero_aleatorio:
            print(f"Parabéns! Acertaste! O número era {numero_aleatorio}.")
            input("Pressione [Enter] para continuar...\n")
            jogoAcabou = True
            if player_number not in players_temp or players_temp[player_number] > tentativa_counter:
                players_temp[player_number] = tentativa_counter
                print(f"Novo recorde para o Player #{player_number}!")
            clearScreen()
        elif palpite < numero_aleatorio:
            print("Não acertaste, o numero e maior. Tenta novamente!")
            if palpite > min:
                min = palpite
        elif palpite > numero_aleatorio:
            print("Não acertaste, o numero e menor. Tenta novamente!")
            if palpite < max:
                max = palpite
        else:
            print("Número fora do limite!!")
            tentativa_counter -= 1
        
        print()
    return players_temp
# Gerar um número aleatório entre 1 e 100 (inclusive)
# A função randint(a, b) retorna um número inteiro aleatório N tal que a <= N <= b
players = {}
querjogar = ""

# Mostrar mensagem de boas-vindas ao jogo
clearScreen()
print("=== Jogo de Adivinhação ===")
print("Foi gerado um número entre 1 e 100.")
print("Tenta adivinhar qual é!")
print()

while querjogar != "n":
    player_number = -1
    try:
        querjogar = input("Quer jogar? [Y] - Sim | [N] - Não | [T] - Mostrar top 5 : ").lower()
        
        if not querjogar.isalpha():
            raise ValueError("Entrada inválida! Digite apenas letras.")
        
        if len(querjogar) != 1:
            raise ValueError("Digite apenas um caractere!")
        
        if querjogar not in ['y', 'n', 't']:
            raise ValueError("Digite apenas Y, N ou T!")
        
    except ValueError as e:
        print(f"Erro: {e}")
        print("Tente novamente.\n")
    
    clearScreen()
    if querjogar == "y": 
        players = correrJogo(players)
    if querjogar == "t":
        mostrarTop5(players)
mostrarTop5(players)