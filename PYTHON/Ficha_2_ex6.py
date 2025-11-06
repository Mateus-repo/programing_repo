#ex6
numIn = int( input( 'Introduza o número inicial: ' ))
numFin = int( input( 'Introduza o número final: ' ))

for num in range( numIn, numFin ):
    if( num % 2 == 0 ):
        print( num )