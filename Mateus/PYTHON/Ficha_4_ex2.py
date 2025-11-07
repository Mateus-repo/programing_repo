#ex2

def ivertido( numero ):
        res = str( numero )[::-1]
        return res

numero = int( input( 'Digite o numero: ' ))
print( ivertido( numero ))