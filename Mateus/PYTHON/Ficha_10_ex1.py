import pandas as pd
import os

def mediaExcelColuna(df, coluna):
    df = df.loc[:,coluna]
    df=df.mean()
    return df

def somaPerTypeExcelColuna(df, colunaType, coluna):
    tipes = df.groupby(colunaType)[coluna].sum().to_dict()
    return tipes

nome_ficheiro_excel = 'vendas2425.xlsx'

diretorio_script = os.path.dirname(os.path.abspath(__file__))

caminho_completo_ficheiro = os.path.join(diretorio_script, nome_ficheiro_excel)

try:
    # Ler o ficheiro Excel para um DataFrame do pandas
    df_vendas = pd.read_excel(caminho_completo_ficheiro)
    df_2025 = df_vendas[df_vendas["País de Destino"] == 'Brasil']
    df_vendas = df_2025.sort_values(by=['Vendas'], ascending=False)
    print(f"Ficheiro '{nome_ficheiro_excel}' lido com sucesso!")
    # print("Primeiras 5 linhas do DataFrame:")
    print(df_vendas.head(1))
    # print(df_2025)
    # print(df_vendas[['Nome da Empresa', 'Data do Pedido', 'Cidade de Destino','País de Destino', 'Ano']])
    # print("A média de 2025 é ", mediaExcelColuna(df_2025, "Vendas"), ".")

except FileNotFoundError:
    print(
        f"Erro: O ficheiro '{nome_ficheiro_excel}' não foi encontrado. Certifique-se de que está na mesma pasta que o script ou forneça o caminho completo.")
except Exception as e:
    print(f"Ocorreu um erro ao ler o ficheiro Excel: {e}")
