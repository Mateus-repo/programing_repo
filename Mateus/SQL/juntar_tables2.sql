SELECT c.nome AS clientes, p.nome AS produtos, r.id_pedido AS pedidos, i.preco_unitario,i.quantidade,i.valor_total
FROM clientes c, produtos p, itens_pedido i, pedidos r
WHERE r.id_cliente = c.id_cliente
AND i.id_produto = p.id_produto
AND i.id_pedido = r.id_pedido

