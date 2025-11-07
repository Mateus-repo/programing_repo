#ex5
m = int( input( 'Introduza o número inicial (menor):' ))
M = int( input( 'Introduza o número inicial (maior):' ))

for i in range( M - m + 1 ):
    if( i % 2 == 0 ):
        print( i + m )