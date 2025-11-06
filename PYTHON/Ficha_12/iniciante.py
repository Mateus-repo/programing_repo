import mysql.connector
from config import DB_CONFIG


def listar_todos_produtos():
    """
    Estabelece a conexão com a base de dados e lista todos os produtos.
    """
    print("--- Nível Iniciante: Listar Todos os Produtos ---")

    try:
        # 1. Estabelecer a ligação
        conexao = mysql.connector.connect(**DB_CONFIG)

        # 2. Criar um cursor
        cursor = conexao.cursor()

        # 3. Definir a query SQL
        query = "SELECT id, nome, preco, stock FROM produtos WHERE preco > 100.00"

        # 4. Executar a query
        cursor.execute(query)

        # 5. Obter os resultados
        resultados = cursor.fetchall()

        # 6. Apresentar os resultados
        if resultados:
            print(f"Total de {len(resultados)} produtos encontrados:")
            print("{:<5} {:<20} {:<10} {:<5}".format("ID", "NOME", "PREÇO", "STOCK"))
            print("-" * 40)
            for (id_prod, nome, preco, stock) in resultados:
                print("{:<5} {:<20} {:<10.2f} {:<5}".format(id_prod, nome, preco, stock))
        else:
            print("Nenhum produto encontrado.")

    except mysql.connector.Error as erro:
        print(f"Erro ao ligar à base de dados ou executar query: {erro}")

    finally:
        # 7. Fechar o cursor e a conexão
        if 'cursor' in locals() and cursor:
            cursor.close()
        if 'conexao' in locals() and conexao.is_connected():
            conexao.close()
            print("\nLigação MySQL fechada.")


# 👇 Esta parte tem que estar fora da função
if __name__ == "__main__":
    listar_todos_produtos()
