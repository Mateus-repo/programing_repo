create table Programadores (
	id_programador INT auto_increment PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
	pais_orginal VARCHAR(100) NOT NULL
);
create table Jogos (
	id_game INT auto_increment PRIMARY KEY,
    titulo VARCHAR(100) NOT NULL,
    data_de_lancamento Varchar(10) NOT NULL,
    genero varchar(100) NOT NULL,
    id_programador INT,
    FOREIGN KEY (id_programador) REFERENCES Programadores(id_programador)
);
create table Utilizadores (
	id_user INT auto_increment PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    email VARCHAR(255) NOT NULL
);
create table Avaliacoes (
	id_game INT,
    FOREIGN KEY (id_game) REFERENCES Jogos(id_game),
    id_user INT,
    FOREIGN KEY (id_user) REFERENCES Utilizadores(id_user),
    data_de_avaliacao Varchar(10) NOT NULL,
    nota VARCHAR(2) NOT NULL,
    coment varchar(255) NOT NULL
);