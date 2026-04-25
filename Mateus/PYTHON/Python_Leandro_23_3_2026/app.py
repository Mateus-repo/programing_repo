from flask import Flask, session, redirect, url_for, request, render_template
from time import time
app = Flask(__name__)
app.secret_key = '12345'  # Substitua por uma chave secreta real

@app.template_filter('average')
def average_filter(lst):
    if not lst:
        return 0
    return sum(lst) / len(lst)

@app.route('/')
def index(): 
    if'listaA' not in session:
        session['listaA'] = []
        session['contadorA'] = 0
        session['tempoMedioA'] = []
    if'listaB' not in session:
        session['listaB'] = []
        session['contadorB'] = 0
        session['tempoMedioB'] = []
    if'listaC' not in session:
        session['listaC'] = []
        session['contadorC'] = 0
        session['tempoMedioC'] = []

    return render_template('index.html')
@app.route('/monitor')
def monitor():
    return render_template('monitor.html', listaA=session.get('listaA', []), listaB=session.get('listaB', []), listaC=session.get('listaC', [])
                           , tempoMedioA=session.get('tempoMedioA', []), tempoMedioB=session.get('tempoMedioB', []), tempoMedioC=session.get('tempoMedioC', []))
@app.route('/senhas')
def senhas():
    return render_template('senhas.html')
@app.route('/alterar_lista', methods=['POST'])
def alterar_lista():
    servicoSenha = request.json.get('servicoSenha')
    servicoAtendimento = request.json.get('servicoAtendimento')
    if servicoSenha is not None:
        listaTemp = session.get('lista' + servicoSenha, [])
        session['contador' + servicoSenha] += 1
        novaSenha = {
            'numSenha': session['contador' + servicoSenha],
            'tempoSenha': time()
        }
        listaTemp.append(novaSenha)
        session['lista' + servicoSenha] = listaTemp
    if servicoAtendimento is not None:
        listaTemp = session.get('lista' + servicoAtendimento, [])
        if listaTemp:
            senha_atendida = listaTemp.pop(0)
            session['tempoMedio' + servicoAtendimento].append(time() - senha_atendida['tempoSenha'])
        session['lista' + servicoAtendimento] = listaTemp

    session.modified = True
    return {'status': 'sucesso', 'listaA': session['listaA'], 'listaB': session['listaB'], 'listaC': session['listaC']}
if __name__ == '__main__':    app.run(debug=True)