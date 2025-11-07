import pandas as pd
import os

nome_ficheiro_excel = 'vendas2425.xlsx'

diretorio_script = os.path.dirname(os.path.abspath(__file__))
caminho_completo_ficheiro = os.path.join(diretorio_script, nome_ficheiro_excel)

try:
    df_vendas = pd.read_excel(caminho_completo_ficheiro)

    print(f"Ficheiro '{nome_ficheiro_excel}' lido com sucesso!\n")

    vendas_por_empresa = df_vendas.groupby('Nome da Empresa')['Vendas'].sum().sort_values(ascending=False)

    total_geral = vendas_por_empresa.sum()

    percentagens = (vendas_por_empresa / total_geral * 100).round(2)

    resultado = pd.DataFrame({
        'Empresa': vendas_por_empresa.index,
        'Valor Total (€)': vendas_por_empresa.values,
        'Percentagem (%)': percentagens.values
    })

    print(f"\nTotal Geral de Vendas: {total_geral:,.2f} €\n")

    for idx, row in resultado.iterrows():
        print(f"{row['Empresa']:<30} {row['Valor Total (€)']:>15,.2f} {row['Percentagem (%)']:>17.2f}%")


except FileNotFoundError:
    print(f"Erro: O ficheiro '{nome_ficheiro_excel}' não foi encontrado.")
    print(f"Caminho procurado: {caminho_completo_ficheiro}")
