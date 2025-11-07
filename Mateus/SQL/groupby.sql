select c.nome As Nome, count(p.cliente_id) 	AS "Numero de pedidos"
FROM pedidos p, clientes c
where c.id = p.cliente_id
group by c.id