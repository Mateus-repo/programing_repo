SELECT sum(v.quantidade) "Vendas em janeiro"
from vendas v
where v.data_venda like "%01%"