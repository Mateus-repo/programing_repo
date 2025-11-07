import pandas as pd
import os

nome_ficheiro_excel = 'vendas2425.xlsx'

diretorio_script = os.path.dirname(os.path.abspath(__file__))

caminho_completo_ficheiro = os.path.join(diretorio_script, nome_ficheiro_excel)

def mediaExcelColuna(df, coluna):
    df = df.loc[:,coluna]
    df=df.mean()
    return df

def contarDataColuna(df, coluna):
    df = df.loc[:,coluna]
    df=df.count()
    return df

def somarExcelColuna(df, coluna):
    df = df.loc[:,coluna]
    df=df.sum()
    return df

def maxValueExcelColuna(df, coluna):
    df = df.loc[:,coluna]
    df=df.max()
    return df

def somaPerTypeExcelColuna(df, colunaType, coluna):
    tipes = df.groupby(colunaType)[coluna].sum().to_dict()
    return tipes

try:
    # Ler o ficheiro Excel para um DataFrame do pandas
    df_vendas = pd.read_excel(caminho_completo_ficheiro)

    print(f"Ficheiro '{nome_ficheiro_excel}' lido com sucesso!")
    # print("Primeiras 5 linhas do DataFrame:")
    # print(df_vendas.head())
    print(somaPerTypeExcelColuna(df_vendas,"País de Destino", "Vendas"))

except FileNotFoundError:
    print(
        f"Erro: O ficheiro '{nome_ficheiro_excel}' não foi encontrado. Certifique-se de que está na mesma pasta que o script ou forneça o caminho completo.")
except Exception as e:
    print(f"Ocorreu um erro ao ler o ficheiro Excel: {e}")