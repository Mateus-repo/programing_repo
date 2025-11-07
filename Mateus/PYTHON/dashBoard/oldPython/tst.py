import pandas as pd


# dataframe

df = pd.DataFrame({'Produto': ['Ratos', 'Teclados', 'Monitores HP', 'Windows 11', 'Monitores HP',

'Monitores ASUS', 'Windows 10', 'Windows 11', 'Office 2021','Office 2021', 'Monitores HP'],

'Categoria': ['HW', 'HW', 'HW', 'SW', 'HW',

'HW', 'SW', 'SW', 'SW', 'SW','HW'],

'Quantidade': [8, 5, 3, 4, 5, 9, 11, 8, 4,7,11],

})


#Exemplo 1: Total quantidades de cada produto

pivot = df.pivot_table(index=['Produto'],

values=['Quantidade'],

aggfunc='sum')

print(pivot)

#Exemplo 2: Total quantidade de cada categoria

pivot = df.pivot_table(index=['Categoria'],

values=['Quantidade'],

aggfunc='sum')

print(pivot)


#Exemplo 3: Total quantidade de cada produto e categoria

pivot = df.pivot_table(index=['Produto','Categoria'],

values=['Quantidade'],

aggfunc='sum')

print(pivot)


#Exemplo 4: Média, minimo e máximo por categoria

pivot = df.pivot_table(index=['Categoria'],

values=['Quantidade'],

aggfunc={'mean', 'min','max'})

print(pivot)