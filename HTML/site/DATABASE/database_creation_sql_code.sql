CREATE DATABASE pcNovo;
USE pcNovo;
CREATE TABLE Clientes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    senha VARCHAR(255) NOT NULL,
    data_nascimento DATE,
    role ENUM('admin', 'cliente') DEFAULT 'cliente',
    imagem_perfil LONGBLOB
);
CREATE TABLE Produtos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(255) NOT NULL,
    descricao TEXT,
	specs TEXT,
    preco DECIMAL(10, 2) NOT NULL,
    imagem LONGBLOB
);