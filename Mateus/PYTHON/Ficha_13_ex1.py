import pymysql

DB_CONFIG = {
    'host': 'localhost',
    'port': 3306,
    'user': 'root',
    'password': 'D2#B15',
    'database': "ecommerce_db"
}

conexaoDB = pymysql.connect(
    host=DB_CONFIG['host'],
    port=DB_CONFIG['port'],
    user=DB_CONFIG['user'],
    password=DB_CONFIG['password'],
    database=DB_CONFIG['database'],
    cursorclass=pymysql.cursors.DictCursor
)

def execute_query(connection, query, fetch=False):
    with connection.cursor() as cursor:
        cursor.execute(query)
        if fetch:
            result = cursor.fetchall()
            return result
        connection.commit()


def get_receita_total(connection):
    query = """
        SELECT
            SUM(total) AS receita_total
        FROM Encomendas
        WHERE status = 'Entregue';
    """
    result = execute_query(connection, query, fetch=True)
    return result[0]['receita_total'] if result and result[0]['receita_total'] is not None else 0.00


def get_count_produtos(connection, statusEntrega):
    query = f"""
        SELECT COUNT(*) AS total_produtos
        FROM Encomendas
        WHERE status = '{statusEntrega}';
    """
    result = execute_query(connection, query, fetch=True)
    return result[0]['total_produtos'] if result and result[0]['total_produtos'] is not None else 0.00


def get_preco_medio_produtos(connection):
    total_receita = get_receita_total(connection)
    total_produtos = get_count_produtos(connection, "Entregue")
    if total_produtos == 0:
        return 0.00
    return total_receita / total_produtos

def get_cidades_clientes_ativos(connection):
    query = """
        SELECT
            c.cidade,
            COUNT(DISTINCT c.cliente_id) AS clientes_com_multiplas_encomendas
        FROM Clientes c
        JOIN Encomendas e ON c.cliente_id = e.cliente_id
        GROUP BY c.cidade
        HAVING COUNT(e.encomenda_id) > 1;
    """
    result = execute_query(connection, query, fetch=True)
    return result

def get_produto_mais_vendido(connection):
    query = """
        SELECT
            p.nome AS produto,
            SUM(i.quantidade) AS total_vendida
        FROM Itens_Encomenda i
        JOIN Produtos p ON i.produto_id = p.produto_id
        GROUP BY p.produto_id, p.nome
        ORDER BY total_vendida DESC
        LIMIT 1;
    """
    result = execute_query(connection, query, fetch=True)
    return result[0] if result else None

def get_clientes_high_value(connection):
    query = """
        SELECT
            c.nome AS cliente,
            COUNT(e.encomenda_id) AS total_encomendas,
            SUM(e.total) AS receita_total
        FROM Clientes c
        JOIN Encomendas e ON c.cliente_id = e.cliente_id
        GROUP BY c.cliente_id, c.nome
        HAVING SUM(e.total) > 500.00
        ORDER BY receita_total DESC;
    """
    result = execute_query(connection, query, fetch=True)
    return result

def get_tendencia_mensal(connection):
    query = """
        SELECT
            YEAR(data_encomenda) AS ano,
            MONTH(data_encomenda) AS mes,
            SUM(total) AS receita_total
        FROM Encomendas
        WHERE status = 'Entregue'
        GROUP BY YEAR(data_encomenda), MONTH(data_encomenda)
        ORDER BY ano, mes;
    """
    result = execute_query(connection, query, fetch=True)
    return result

tiposStatus = ["Entregue", "Pendente", "Enviado", "Processando", "Cancelado"]

print("=== Estatísticas gerais")
print("Receita total:", get_receita_total(conexaoDB))
print("Preço médio produtos entregues:", get_preco_medio_produtos(conexaoDB))

for each in tiposStatus:
    print(f"Quantidade de produtos {each}: {get_count_produtos(conexaoDB, each)}")

print("\nClientes por cidade com múltiplas encomendas")
for row in get_cidades_clientes_ativos(conexaoDB):
    print(f"{row['cidade']}: {row['clientes_com_multiplas_encomendas']} clientes")

print("\nProduto mais vendido ===")
produto = get_produto_mais_vendido(conexaoDB)
if produto:
    print(f"{produto['produto']} - {produto['total_vendida']} unidades vendidas")

print("\nClientes high value (receita > 500€)")
for row in get_clientes_high_value(conexaoDB):
    print(f"{row['cliente']}: {row['total_encomendas']} encomendas - {row['receita_total']}€")

print("\nTendência de vendas mensais")
for row in get_tendencia_mensal(conexaoDB):
    print(f"{row['ano']}-{str(row['mes']).zfill(2)}: {row['receita_total']}€")