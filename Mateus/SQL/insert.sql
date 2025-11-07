INSERT INTO clientes (nome, email, telefone) VALUES
('João Silva', 'joao@email.com', '123456789'),
('Maria Santos', 'maria@email.com', '987654321'),
('Pedro Oliveira', 'pedro@email.com', '456789123'),
('Maria Oliveira', 'maria.oliveira@gmail.com', '234506789'),
('Carlos Silva', 'carlos.souza@gmail.com', '345607890');
insert INTO produtos (nome, preco, stock) VALUES
('Notebook', 3500.00, 10),
('Rato', 35.00, 8),
('Monitor', 300.00, 5),
('TV LED', 390.00, 15),
('Smartphone', 1500.00, 20);
INSERT INTO pedidos (id_cliente, data_pedido) VALUES
(1, '2023-12-01'),
(1, '2023-12-05'),
(2, '2023-12-02'),
(2, '2023-12-07'),
(3, '2023-12-03'),
(3, '2023-12-06');
INSERT INTO itens_pedido (id_pedido, id_produto, quantidade, preco_unitario, valor_total) VALUES
(1, 1, 2, 100.00, 200.00),
(1, 3, 1, 100.00, 100.00),
(2, 2, 2, 200.00, 400.00),
(3, 3, 3, 150.00, 450.00);