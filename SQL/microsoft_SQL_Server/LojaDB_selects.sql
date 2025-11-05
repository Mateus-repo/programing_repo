Use LojaDB
select c.nome as "Nome do cliente", c.email, p.nome as "Nome do produto", 
pe.id_pedido As "Id do pedido", pe.data_pedido as "Quando foi pedido"
from clientes c, produtos p, pedidos pe
where c.id_cliente = pe.id_cliente
and pe.id_produto = p.id_produto
Order by pe.data_pedido
GO