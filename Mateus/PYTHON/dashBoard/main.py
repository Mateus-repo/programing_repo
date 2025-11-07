import pandas as pd  # pip install pandas openpyxl
import plotly.express as px  # pip install plotly-express
import streamlit as st  # pip install streamlit
import os

nome_ficheiro_excel = 'dataSets/dataSet_Default.csv'

# Obter a pasta onde está o ficheiro .py
diretorio_script = os.path.dirname(os.path.abspath(__file__))

# Construir o caminho completo para o ficheiro CSV
caminho_completo_ficheiro = os.path.join(diretorio_script, nome_ficheiro_excel)

df = pd.read_excel(
    io=caminho_completo_ficheiro,
    engine="openpyxl",
    sheet_name="Data",
    skiprows=3,
    usecols="B:R",
    nrows=1000,
)

df["hour"] = pd.to_datetime(df["Time"], format="%H:%M:%S").dt.hour

st.write(df)
# ---- SIDEBAR ----
st.sidebar.header("Please Filter Here:")
region = st.sidebar.multiselect(
    "Select the Region:",
    options=df["Region"].unique(),
    default=df["Region"].unique()
)

model = st.sidebar.multiselect(
    "Select the Customer Type:",
    options=df["Model"].unique(),
    default=df["Model"].unique(),
)

year = st.sidebar.multiselect(
    "Select the Year:",
    options=df["Year"].unique(),
    default=df["Year"].unique()
)

color = st.sidebar.multiselect(
    "Select the Color:",
    options=df["Color"].unique(),
    default=df["Year"].unique()
)

fuel_type = st.sidebar.multiselect(
    "Select the Fuel Type:",
    options=df["Fuel_Type"].unique(),
    default=df["Fuel_Type"].unique()
)

transmission = st.sidebar.multiselect(
    "Select the Transmission:",
    options=df["Transmission"].unique(),
    default=df["Transmission"].unique()
)

engine_size= st.sidebar.multiselect(
    "Select the Engine Size in Liters:",
    options=df["Engine_Size_L"].unique(),
    default=df["Engine_Size_L"].unique()
)

mileage_km = st.sidebar.multiselect(
    "Select the Mileage Km:",
    options=df["Mileage_KM"].unique(),
    default=df["Mileage_KM"].unique()
)

price = st.sidebar.multiselect(
    "Select the Price USD:",
    options=df["Price_USD"].unique(),
    default=df["Price_USD"].unique()
)


df_selection = df.query(
    "City == @city & Customer_type ==@customer_type & Gender == @gender"
    "Region == @region & Year == @year & Model ==@model & Fuel_Type == @fuel_type & Transmission == @transmission & Engine_Size_L == @engine_size & Mileage_KM == @mileage_km & Price_USD == @price_USD"

)

# Check if the dataframe is empty:
if df_selection.empty:
    st.warning("No data available based on the current filter settings!")
    st.stop() # This will halt the app from further execution.
# ---- MAINPAGE ----
st.title(":bar_chart: Data Dashboard")
st.markdown("##")

# TOP KPI's
total_sales = int(df_selection["Sales_Volume"].sum())
average_sales_per_model = round(df_selection["Sales_Volume"].mean(), 1)
average_total_sales_per_car = round(df_selection["Total"].mean(), 2)

left_column, middle_column, right_column = st.columns(3)
with left_column:
    st.subheader("Total Vendas:")
    st.subheader(f"€ {total_sales:,}")
    st.subheader(" Total Profit:")
    st.subheader(f"€ {total_sales:,}")
with middle_column:
    st.subheader("Média de numero de vendas:")
    st.subheader(f"{average_sales_per_model}")
with right_column:
    st.subheader("Média de profit por modelo:")
    st.subheader(f"€ {average_total_sales_per_car}")

st.markdown("""---""")

# SALES BY PRODUCT LINE [BAR CHART]
sales_by_product_line = df_selection.groupby(by=["Model"])[["Total"]].sum().sort_values(by="Total")
fig_product_sales = px.bar(
    sales_by_product_line,
    x="Total",
    y=sales_by_product_line.index,
    orientation="h",
    title="<b>Sales by Product Line</b>",
    color_discrete_sequence=["#0083B8"] * len(sales_by_product_line),
    template="plotly_white",
)
fig_product_sales.update_layout(
    plot_bgcolor="rgba(0,0,0,0)",
    xaxis=(dict(showgrid=False))
)

# SALES BY HOUR [BAR CHART]
sales_by_hour = df_selection.groupby(by=["hour"])[["Total"]].sum()
fig_hourly_sales = px.bar(
    sales_by_hour,
    x=sales_by_hour.index,
y="Total",
    title="<b>Sales by hour</b>",
    color_discrete_sequence=["#0083B8"] * len(sales_by_hour),
    template="plotly_white",
)
fig_hourly_sales.update_layout(
    xaxis=dict(tickmode="linear"),
    plot_bgcolor="rgba(0,0,0,0)",
    yaxis=(dict(showgrid=False)),
)

left_column, right_column = st.columns(2)
left_column.plotly_chart(fig_hourly_sales, use_container_width=True)
right_column.plotly_chart(fig_product_sales, use_container_width=True)

# ---- HIDE STREAMLIT STYLE ----
hide_st_style = """
            <style>
            #MainMenu {visibility: hidden;}
            footer {visibility: hidden;}
            header {visibility: hidden;}
            </style>
            """
st.markdown(hide_st_style, unsafe_allow_html=True)
