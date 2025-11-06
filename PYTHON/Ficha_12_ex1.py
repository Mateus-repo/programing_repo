#ex1
import pymysql

conexao=pymysql.connect(

host='localhost',

port=3306,

user='root',

password='D2#B15',

)


cursor = conexao.cursor()


# Usar a base de dados

cursor.execute("USE testepy")

cursor = conexao.cursor()


# Atualizar o email de um utilizador específico

sql = "UPDATE utilizadores SET email = %s WHERE id = %s"


# Exemplo: atualizar o utilizador com id = 2

novo_email = "bruno.costa@novoemail.com"

id_utilizador = 2


cursor.execute(sql, (novo_email, id_utilizador))

conexao.commit()


print(f"{cursor.rowcount} utilizador(es) atualizado(s) com sucesso!")

cursor.execute("SELECT id, nome, email, data_criacao FROM utilizadores")


utilizadores = cursor.fetchall()

print("=== Lista de Utilizadores ===")

for u in utilizadores:

    print(f"ID: {u[0]} | Nome: {u[1]} | Email: {u[2]} | Criado em: {u[3]}")


cursor.close()

conexao.close()