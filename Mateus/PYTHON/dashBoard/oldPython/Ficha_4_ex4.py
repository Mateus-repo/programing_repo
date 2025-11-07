#ex4
from os.path import split
def ordenar_palavras(text):
    palavras = ""
    # split() separa palavras por espaço
    #sorted (palavras, key=str.lower) garante que a ordenação não seja afetada por letras maisculos/minuscuas
    palavras = text.split(" ")
    text = sorted(palavras, key=str.lower)
    return texto
texto = str(input( 'Escreva palavras: ' ))
texto = ordenar_palavras(texto)
print('Palavras Ordenadas: %s' % texto)


