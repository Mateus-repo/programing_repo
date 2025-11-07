SELECT clientes.nome_cliente, vendas.produto, vendas.valor
FROM clientes
LEFT JOIN vendas ON clientes.id_cliente = vendas.id_cliente;

