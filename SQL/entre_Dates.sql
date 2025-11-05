SELECT sum(v.quantidade) "Vendas em janeiro"
from vendas v
where v.data_venda >= "2023-01-01" and v.data_venda <= "2023-01-31"