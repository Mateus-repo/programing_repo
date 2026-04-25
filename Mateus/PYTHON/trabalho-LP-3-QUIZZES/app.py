from flask import Flask, session, redirect, url_for, request, render_template
app = Flask(__name__)
app.secret_key = 'chave_secreta'  

QUESTIONS = [
    {'id': 1, 'pergunta': 'Qual é o nome do país com a capital Paris?', 'opcoes': ['França', 'Espanha', 'Itália', 'Alemanha'], 'resposta': 'França', 'pontos': 20, 'img_url':"/static/images/pergunta_1.jpg"},
    {'id': 2, 'pergunta': 'Qual é o nome do país com a capital Lisboa?', 'opcoes': ['Brasil', 'Polónia', 'Inglaterra', 'Portugal'], 'resposta': 'Portugal', 'pontos': 20, 'img_url':"/static/images/pergunta_2.jpg"},
    {'id': 3, 'pergunta': 'Qual é a marca de carros que é americana?', 'opcoes': ['Ford', 'BMW', 'Mercedes', 'Porche'], 'resposta': 'Ford', 'pontos': 30, 'img_url':"/static/images/pergunta_3.jpg"},
    {'id': 4, 'pergunta': 'Qual é o número de distritos em Portugal?', 'opcoes': ['18', '20', '22', '24'], 'resposta': '18', 'pontos': 30, 'img_url':"/static/images/pergunta_4.jpg"}
]

@app.route('/')
def home():
    session['current_question'] = 1
    session['answers'] = []
    session.modified=True
    return render_template('index.html')

@app.route('/question/<int:question_id>')
def question(question_id):
    if 'current_question' not in session or 'answers' not in session:
        session['current_question'] = 1
        session['answers'] = []
        session.modified=True
        return redirect(url_for('home'))
    else:
        if question_id > len(QUESTIONS):
            return redirect(url_for('results'))
        session['current_question'] = question_id
        session.modified=True
        return render_template('question.html', perguntas = QUESTIONS, pergunta_atual = session['current_question'])
    
@app.route('/submit_answer/<int:question_id>/<int:answer>')
def submit_answer(question_id, answer):
    session['answers'].append({'question_id': question_id, 'answer': QUESTIONS[question_id - 1]['opcoes'][answer], 'answer_status': 'Pendente'})
    session.modified=True
    return redirect(url_for('question', question_id=question_id + 1))

@app.route('/results')
def results():
    total_points = 0
    for question in QUESTIONS:
        if question['resposta'] == session['answers'][question['id'] - 1]['answer']:
            total_points += question['pontos']
            session['answers'][question['id'] - 1]['answer_status'] = 'Correta'
        else:
            session['answers'][question['id'] - 1]['answer_status'] = 'Errada'
    session.modified=True
    return render_template('results.html', perguntas=QUESTIONS, respostas=session['answers'], pontos_totais=total_points)

if __name__ == '__main__': 
    app.run(debug=True)