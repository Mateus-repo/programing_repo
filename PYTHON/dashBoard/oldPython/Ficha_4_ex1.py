#ex1

def area( larg, comp ):
    are = larg * comp
    return are

larg = int( input( ' largura? : ' ))
comp = int( input( ' comprimento? : ' ))

print(' área do terreno: %d ' % area( larg, comp ))