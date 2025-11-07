import pymysql
import config

conexao = config.conexaoDB
cursor = conexao.cursor()

# Usa uma base inicial (necessário antes de criar outra)
cursor.execute("USE testepy")

database = "gestao_produtos"

# Criação e utilização da nova base
cursor.execute(f"CREATE DATABASE IF NOT EXISTS {database}")
cursor.execute(f"USE {database}")

# Criação da tabela
sql = """
CREATE TABLE IF NOT EXISTS produtos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(255) NOT NULL,
    descricao TEXT,
    preco DECIMAL(10, 2) NOT NULL,
    stock INT NOT NULL DEFAULT 0
);
"""
cursor.execute(sql)
conexao.commit()

# Inserção de dados
sql = """
INSERT INTO produtos (nome, descricao, preco, stock)
VALUES
('Portátil Ultra', 'Portátil de alto desempenho com 16GB RAM e 512GB SSD.', 1299.99, 15),
('Monitor 4K', 'Monitor de 27 polegadas com resolução 4K.', 349.50, 30),
('Rato Ergonómico', 'Rato sem fios, design ergonómico.', 25.99, 100),
('Teclado Mecânico', 'Teclado com switches mecânicos e retroiluminação RGB.', 89.00, 5),
('Webcam HD', 'Webcam com resolução 1080p.', 45.75, 50);
"""
cursor.execute(sql)
conexao.commit()

print("Base de dados e tabela criadas com sucesso!")
