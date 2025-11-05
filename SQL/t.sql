INSERT INTO programadores (nome, pais_original) VALUES
('Valve', 'Estados Unidos'),
('CD Projekt Red','Polónia'),
('Naughty Dog', 'Estados Unidos');
INSERT INTO jogos (titulo, data_de_lancamento, genero, id_programador) VALUES
('Half-Life 2', '2004-11-16', 'FPS', 1),
('The Witcher 3', '2015-05-19','RPG', 2),
('The Last of Us', '2013-06-14', 'Aventura', 3);
INSERT INTO utilizadores (nome, email) VALUES
('João Souza','joao.souza@gmail.com'),
('Maria Oliveira','maria.oliveira@gmail.com'),
('Carlos Mendes','carlos.mendes@gmail.com');
INSERT INTO avaliacoes (id_game, id_user,  data_de_avaliacao, nota, coment) VALUES
(1, 1, '2024-01-15', 9,'Ótima jogabilidade, gráficos incríveis!'),
(2, 2, '2024-01-16', 10,'Melhor RPG que já joguei. História fantástica.'),
(3, 3, '2024-01-17', 8,'Excelente narrativa, mas o combate é um pouco limitado.');