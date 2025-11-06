#ex3
talunos = 0
tmasc = 0
percentFem = 0
percentMasc = 0

talunos = int( input( "Introduza o total de alunos da escola: " ))
tmasc = int( input( "Introduza o total de alunos do sexo masculino: " ))

percentMasc = int(100 * tmasc / talunos)
percentFem = int(100 - percentMasc)

print( "Percentagem de alunos do sexo masculino: %d" % ( percentMasc ))
print( "Percentagem de alunos do sexo feminino: %d" % ( percentFem ))
