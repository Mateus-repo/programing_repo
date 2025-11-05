SELECT (sum(v.preco_unitario) / count(v.preco_unitario))  as "Media de preço"
from vendas v