select p.cliente_id AS Cliente, p.id AS "Id Pedido", p.data, p.produto, p.quantidade, p.preco
from pedidos p, clientes c
where c.nome = "João Silva"
and p.cliente_id = c.id