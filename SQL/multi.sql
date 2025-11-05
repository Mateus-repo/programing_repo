Select p.id, p.cliente_id, p.data, p.produto, p.quantidade, (p.preco * 0.9) AS preco
from pedidos p

