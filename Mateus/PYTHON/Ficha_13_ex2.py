import pymysql

DB_CONFIG = {
    'host': 'localhost',
    'port': 3306,
    'user': 'root',
    'password': 'D2#B15',
    'database': "ecommerce_db"
}

# Cria a conexão
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

# Executar
print(get_receita_total(conexaoDB))
