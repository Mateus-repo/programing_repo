INSERT INTO clientes (nome, email) VALUES
('Maria Silva', 'maria@exemplo.com'),
('João Oliveira', 'joao@exemplo.com'),
('Ana Silva', 'ana@exemplo.com');
insert INTO produtos (nome, preco, stock) VALUES
('Camisola', 49.90, 100),
('Ténis', 159.90, 50),
('Boné', 29.90, 150),
('Calção', 9.90, 20);
INSERT INTO pedidos (id_cliente, data_pedido, status) VALUES
(1, '2024-12-10', 'Em Processamento'),
(2, '2024-12-11', 'Concluído'),
(3, '2024-12-12', 'Em Processamento');
INSERT INTO itens_pedidos (id_cliente, id_produto, quantidade, preco_unitario) VALUES
(1, 1, 2, 49.90), 
(1, 3, 1, 29.90), 
(2, 2, 1, 159.90),
(2, 4, 3, 9.90); 
insert into pagamentos (id_pedido, valor, data_pagamento, metodo_pagamento) VALUES
(1, 129.70, '2024-12-10', 'Cartão de Crédito'),
(2, 159.90, '2024-12-11', 'Dinheiro');