import mysql.connector
from config import DB_CONFIG

def changePriceByID(produto_id, novo_preco):
    try:
        conexao = mysql.connector.connect(**DB_CONFIG)
        cursor = conexao.cursor()
        sql = "UPDATE produtos SET preco = %s WHERE id = %s"
        valores = (novo_preco, produto_id)
        cursor.execute(sql, valores)
        conexao.commit()

        if cursor.rowcount > 0:
            print(f"\nPreço do produto ID {produto_id} atualizado para {novo_preco:.2f} €.")
        else:
            print(f"\nProduto com ID {produto_id} não encontrado.")
    except mysql.connector.Error as erro:
        print(f"\nERRO ao atualizar preço: {erro}")
    finally:
        if 'cursor' in locals():
            cursor.close()
        if 'conexao' in locals() and conexao.is_connected():
            conexao.close()
