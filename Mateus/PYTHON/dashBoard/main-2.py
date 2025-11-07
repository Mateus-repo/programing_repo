# main-2.py (atualizado: sem StdDev; percentis como 25/50/75; título da tabela de moda mantido)
import os
import streamlit as st
import pandas as pd
import numpy as np
import plotly.express as px

# ----------------- CONFIG -----------------
st.set_page_config(page_title="Dashboard Vendas Carros (EDA & Profit)", layout="wide")
st.title("📈 Dashboard — Aquisição, Limpeza, EDA e Tabelas de Profit")

# ----------------- AQUISIÇÃO DO DADO (SEM MENSAGEM DA LEITURA) -----------------
default_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "dataSets", "dataSet_Default.csv")

@st.cache_data
def carregar_csv_de_path(caminho):
    try:
        return pd.read_csv(caminho, low_memory=False)
    except Exception as e:
        st.error(f"Erro ao ler CSV do caminho {caminho}: {e}")
        return pd.DataFrame()

if os.path.exists(default_path):
    df = carregar_csv_de_path(default_path)
else:
    st.error("Nenhum ficheiro encontrado. Coloca o CSV em: " + default_path)
    st.stop()

if df is None or df.empty:
    st.warning("Dataset vazio depois da leitura. Verifica o ficheiro CSV.")
    st.stop()

# ----------------- LIMPEZA E TIPOS -----------------
df.columns = [c.strip() for c in df.columns]

colunas_esperadas = [
    "Model", "Year", "Region", "Color", "Fuel_Type", "Transmission",
    "Engine_Size_L", "Mileage_KM", "Price_USD", "Sales_Volume", "Sales_Classification"
]
missing_expected = [c for c in colunas_esperadas if c not in df.columns]
if missing_expected:
    st.warning("Atenção: as seguintes colunas esperadas não foram encontradas: " + ", ".join(missing_expected))

# Converter numéricos de forma robusta
for c in ["Engine_Size_L", "Mileage_KM", "Price_USD", "Sales_Volume"]:
    if c in df.columns:
        df[c] = pd.to_numeric(df[c], errors="coerce")

# Preencher categorias com 'Unknown'
for c in ["Model","Year","Region","Color","Fuel_Type","Transmission","Sales_Classification"]:
    if c in df.columns:
        df[c] = df[c].fillna("Unknown")

# Converter Year se existir
if "Year" in df.columns:
    df["Year"] = pd.to_numeric(df["Year"], errors="coerce").astype("Int64")

# Criar Revenue e Estimated_Profit (colunas base)
if all(col in df.columns for col in ["Price_USD", "Sales_Volume"]):
    df["Revenue"] = df["Price_USD"].fillna(0) * df["Sales_Volume"].fillna(0)
else:
    df["Revenue"] = 0.0

if "Estimated_Profit" not in df.columns:
    df["Estimated_Profit"] = 0.0

# ----------------- SESSION STATE: inicializar chaves (apenas se não existirem) -----------------
if "selected_regions" not in st.session_state:
    st.session_state["selected_regions"] = []
if "selected_models" not in st.session_state:
    st.session_state["selected_models"] = []
if "selected_years" not in st.session_state:
    st.session_state["selected_years"] = []
if "margin_pct" not in st.session_state:
    st.session_state["margin_pct"] = 20.0  # valor default

# ----------------- SIDEBAR: filtros -----------------
st.sidebar.header("Filtros Globais (deixa vazio para mostrar todos)")

region_opts = sorted(df["Region"].dropna().unique()) if "Region" in df.columns else []
model_opts = sorted(df["Model"].dropna().unique()) if "Model" in df.columns else []
year_opts = sorted([y for y in df["Year"].dropna().unique()]) if "Year" in df.columns else []

selected_regions = st.sidebar.multiselect("Região (vazio = todas)", options=region_opts, key="selected_regions")
selected_models = st.sidebar.multiselect("Modelos (vazio = todos)", options=model_opts, key="selected_models")
if year_opts:
    selected_years = st.sidebar.multiselect("Ano (vazio = todos)", options=year_opts, key="selected_years")
else:
    selected_years = []

# Slider margem com key
margin_pct = st.sidebar.slider("Margem de lucro estimada (%)", 0.0, 100.0, key="margin_pct", step=0.5)
margin = margin_pct / 100.0

# Reset filtros: callback para evitar conflito com widgets
def reset_filters():
    st.session_state["selected_regions"] = []
    st.session_state["selected_models"] = []
    st.session_state["selected_years"] = []
    st.session_state["margin_pct"] = 20.0

st.sidebar.button("Reset filtros", on_click=reset_filters)

# ----------------- APLICAR FILTROS (vazio = todas) -----------------
mask = pd.Series(True, index=df.index)

if selected_regions:
    mask &= df["Region"].isin(selected_regions)
if selected_models:
    mask &= df["Model"].isin(selected_models)
if selected_years:
    mask &= df["Year"].isin(selected_years)

df_filtered = df.loc[mask].copy()
df_filtered["Estimated_Profit"] = df_filtered["Revenue"] * margin

if df_filtered.empty:
    st.warning("Nenhum registo após aplicar filtros. Deixa os filtros vazios para ver todos os dados.")

# ----------------- PRINCIPAIS MÉTRICAS -----------------
st.header("Principais Métricas")
col1, col2, col3 = st.columns(3)
total_units = int(df_filtered["Sales_Volume"].sum()) if "Sales_Volume" in df_filtered.columns else 0
total_revenue = float(df_filtered["Revenue"].sum()) if "Revenue" in df_filtered.columns else 0.0
total_profit_est = float(df_filtered["Estimated_Profit"].sum()) if "Estimated_Profit" in df_filtered.columns else 0.0

col1.metric("Total Vendas (unidades)", f"{total_units:,}")
col2.metric("Receita Total (USD)", f"${total_revenue:,.2f}")
col3.metric(f"Profit Estimado ({margin_pct:.1f}%)", f"${total_profit_est:,.2f}")

st.markdown("---")

# ----------------- TABELAS REQUERIDAS -----------------
st.header("Tabelas solicitadas")

# A) Total de vendas e profit por Modelo
st.subheader("A) Total de vendas e profit por Modelo")
if "Model" in df_filtered.columns and "Sales_Volume" in df_filtered.columns:
    table_by_model = (
        df_filtered.groupby("Model", as_index=False)
        .agg(Total_Units=("Sales_Volume", "sum"),
             Total_Revenue=("Revenue", "sum"),
             Estimated_Profit=("Estimated_Profit", "sum"))
        .sort_values("Total_Units", ascending=False)
    )
    st.dataframe(table_by_model.style.format({"Total_Revenue": "${:,.2f}", "Estimated_Profit": "${:,.2f}"}))
else:
    st.write("Colunas Model ou Sales_Volume em falta; não é possível construir esta tabela.")

# B) Profit por Região
st.subheader("B) Profit por Região")
if "Region" in df_filtered.columns and "Revenue" in df_filtered.columns:
    table_by_region = (
        df_filtered.groupby("Region", as_index=False)
        .agg(Total_Units=("Sales_Volume", "sum"),
             Total_Revenue=("Revenue", "sum"),
             Estimated_Profit=("Estimated_Profit", "sum"))
        .sort_values("Total_Revenue", ascending=False)
    )
    st.dataframe(table_by_region.style.format({"Total_Revenue": "${:,.2f}", "Estimated_Profit": "${:,.2f}"}))
else:
    st.write("Colunas Region ou Revenue em falta; não é possível construir esta tabela.")

# C) Moda por Região (Model, Fuel_Type, Transmission) — título restaurado conforme pedido
st.subheader("C) Moda por Região (Model, Fuel_Type, Transmission)")

def most_common(series):
    try:
        s = series.dropna()
        if s.empty:
            return np.nan
        return s.value_counts().idxmax()
    except Exception:
        return np.nan

if "Region" in df_filtered.columns:
    group = df_filtered.groupby("Region")
    rows = []
    for name, g in group:
        rows.append({
            "Region": name,
            "Most_Common_Model": most_common(g["Model"]) if "Model" in g else np.nan,
            "Most_Common_Fuel_Type": most_common(g["Fuel_Type"]) if "Fuel_Type" in g else np.nan,
            "Most_Common_Transmission": most_common(g["Transmission"]) if "Transmission" in g else np.nan,
            "Region_Total_Units": int(g["Sales_Volume"].sum()) if "Sales_Volume" in g else 0
        })
    table_modes = pd.DataFrame(rows).sort_values("Region_Total_Units", ascending=False)
    st.dataframe(table_modes)
else:
    st.write("Coluna Region em falta; não é possível construir esta tabela.")

# ----------------- EDA RÁPIDA (estatísticas descritivas sem 'count' e sem StdDev) -----------------
st.markdown("---")
st.header("Exploração rápida")

with st.expander("Ver primeiras linhas (amostra)"):
    st.dataframe(df_filtered.head(50))

with st.expander("Estatísticas descritivas (numéricas) — sem 'count' e sem 'StdDev'"):
    numeric = df_filtered.select_dtypes(include=[np.number])
    if not numeric.empty:
        desc = numeric.describe().T  # index = coluna, cols = count, mean, std, min, 25%, 50%, 75%, max
        # Selecionar colunas desejadas (remover count e std)
        cols_order = [c for c in ["mean", "min", "25%", "50%", "75%", "max"] if c in desc.columns]
        desc_subset = desc[cols_order].copy()
        # Renomear para rótulos mais claros — percentis mantidos como 25%/50%/75%
        rename_map = {
            "mean": "Average",
            "min": "Minimum",
            "25%": "25%",
            "50%": "50%",
            "75%": "75%",
            "max": "Maximum"
        }
        desc_subset = desc_subset.rename(columns={k: rename_map.get(k, k) for k in desc_subset.columns})
        st.dataframe(desc_subset.style.format("{:,.2f}"))
    else:
        st.write("Sem colunas numéricas.")

# ----------------- EXPORT: apenas tabelas resumo -----------------
st.markdown("---")
st.header("Exportar tabelas resumo")
if "table_by_model" in locals():
    st.download_button("Download tabela por modelo (CSV)", data=table_by_model.to_csv(index=False).encode("utf-8"), file_name="table_by_model.csv", mime="text/csv")
if "table_by_region" in locals():
    st.download_button("Download tabela por região (CSV)", data=table_by_region.to_csv(index=False).encode("utf-8"), file_name="table_by_region.csv", mime="text/csv")
if "table_modes" in locals():
    st.download_button("Download moda por região (CSV)", data=table_modes.to_csv(index=False).encode("utf-8"), file_name="table_modes_by_region.csv", mime="text/csv")
