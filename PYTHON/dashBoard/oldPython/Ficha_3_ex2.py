alunosnota = [0,0,0,0,0]
i=1
while i!=6:
    alunosnota[i-1]= int(input('Insira a nota do aluno %d: ' %(i)))
    if alunosnota[i-1] >20 or alunosnota[i-1] < 0:
        i-=1
        print('Essa nota não é valida. Por favor, insira uma nota entre 0 e 20')
    i=i+1
media = sum(alunosnota)/len(alunosnota)
print('A média das notas da disciplina é de %.2f' %(media))