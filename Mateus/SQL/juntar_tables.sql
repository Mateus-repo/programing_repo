SELECT c.nome AS clientes, p.nome AS produtos, r.id_pedido AS pedidos
FROM clientes c, produtos p, itens_pedido i, pedidos r
WHERE c.id_cliente = r.id_cliente
AND p.id_produto = i.id_produto
AND r.id_pedido = i.id_pedido