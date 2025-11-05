SELECT * 
FROM clientes
LEFT JOIN vendas ON clientes.id_cliente = vendas.id_cliente 
UNION
SELECT *
FROM clientes
RIGHT JOIN vendas ON clientes.id_cliente = vendas.id_cliente