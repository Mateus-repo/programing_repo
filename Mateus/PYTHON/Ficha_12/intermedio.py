import mysql.connector
from config import DB_CONFIG


def conectar():
    """Tenta estabelecer e retornar a ligação MySQL."""
    try:
        conexao = mysql.connector.connect(**DB_CONFIG)
        return conexao
    except mysql.connector.Error as erro:
        print(f"ERRO DE LIGAÇÃO: {erro}")
        return None


def adicionar_produto(nome, descricao, preco, stock):
    """Adiciona um novo produto à base de dados."""
    conexao = conectar()
    if not conexao:
        return

    cursor = conexao.cursor()
    sql = "INSERT INTO produtos (nome, descricao, preco, stock) VALUES (%s, %s, %s, %s)"
    valores = (nome, descricao, preco, stock)

    try:
        cursor.execute(sql, valores)
        conexao.commit()
        print(f"\nProduto '{nome}' adicionado com sucesso. ID: {cursor.lastrowid}")
    except mysql.connector.Error as erro:
        print(f"\nERRO ao adicionar produto: {erro}")
    finally:
        cursor.close()
        conexao.close()


def atualizar_stock(produto_id, novo_stock):
    """Atualiza o stock de um produto específico."""
    conexao = conectar()
    if not conexao:
        return

    cursor = conexao.cursor()
    sql = "UPDATE produtos SET stock = %s WHERE id = %s"
    valores = (novo_stock, produto_id)

    try:
        cursor.execute(sql, valores)
        conexao.commit()
        if cursor.rowcount > 0:
            print(f"\nStock do produto ID {produto_id} atualizado para {novo_stock}.")
        else:
            print(f"\nProduto com ID {produto_id} não encontrado.")
    except mysql.connector.Error as erro:
        print(f"\nERRO ao atualizar stock: {erro}")
    finally:
        cursor.close()
        conexao.close()


def listar_produtos_baixo_stock(limite_stock):
    """Lista produtos com stock abaixo de um limite definido, usando parâmetros."""
    conexao = conectar()
    if not conexao:
        return

    cursor = conexao.cursor()
    sql = "SELECT nome, stock FROM produtos WHERE stock < %s ORDER BY stock ASC"

    try:
        cursor.execute(sql, (limite_stock,))
        resultados = cursor.fetchall()

        print(f"\n--- Produtos com Stock Abaixo de {limite_stock} ---")
        if resultados:
            for nome, stock in resultados:
                print(f"- {nome}: {stock} unidades")
        else:
            print("Todos os produtos têm stock suficiente.")
    except mysql.connector.Error as erro:
        print(f"\nERRO ao listar produtos: {erro}")
    finally:
        cursor.close()
        conexao.close()


def eliminar_produto(produto_id):
    """Elimina um produto da base de dados."""
    conexao = conectar()
    if not conexao:
        return

    cursor = conexao.cursor()
    sql = "DELETE FROM produtos WHERE id = %s"

    try:
        cursor.execute(sql, (produto_id,))
        conexao.commit()
        if cursor.rowcount > 0:
            print(f"\nProduto com ID {produto_id} eliminado com sucesso.")
        else:
            print(f"\nProduto com ID {produto_id} não encontrado para eliminação.")
    except mysql.connector.Error as erro:
        print(f"\nERRO ao eliminar produto: {erro}")
    finally:
        cursor.close()
        conexao.close()


if __name__ == "__main__":
    # Exemplo de utilização das funções:

    # 1. Adicionar um novo produto
    adicionar_produto("Impressora Laser", "Impressora monocromática de alta velocidade.", 199.99, 20)

    # 2. Atualizar o stock de um produto existente (assumindo que o ID 4 é o Teclado Mecânico)
    atualizar_stock(produto_id=4, novo_stock=10)

    # 3. Listar produtos com stock baixo (abaixo de 12 unidades)
    listar_produtos_baixo_stock(limite_stock=12)

    # 4. Eliminar um produto (vamos tentar eliminar o que adicionámos, assumindo que foi o último)
    eliminar_produto(produto_id=5)

    # Para verificar as alterações, o utilizador pode executar o iniciante.py novamente.
    print("\n--- Fim do Script ---")
    print("Execute 'iniciante.py' para ver o estado atual da base de dados.")
