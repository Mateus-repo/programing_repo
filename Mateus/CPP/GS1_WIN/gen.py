import csv
import random
import string
from datetime import datetime, timedelta
from faker import Faker

# Inicia o faker em pt_PT (endereços portugueses)
fake = Faker('pt_PT')

# Listas de amostra – expanda à vontade!
COMPANIES = [
    'Empresa do José', 'Empresa do João', 'Empresa Alfa', 'Global Tech',
    'Padaria Central', 'Química Duarte', 'Móveis Raiz', 'Têxtil Lusa'
]

PRODUCTS = [
    'Pão', 'Madeira', 'Computador', 'Impressora', 'Cadeira',
    'Farinha', ' Azeite', 'Vinho', 'Sabonete', 'Camisola'
]

COUNTRIES = ['Portugal', 'Espanha', 'Alemanha', 'Itália', 'França', 'China', 'Brasil']

UNITS = ['g', 'kg', 'L', 'mL', 'un']

def random_weight():
    """Gera peso líquido aleatório, ex: '10333 kg', '250 g'"""
    # escolhe se é grama ou quilograma aleatoriamente
    unit = random.choice(UNITS)
    if unit in ['kg', 'L']:
        val = round(random.uniform(0.1, 500), 2)
    elif unit in ['g', 'mL']:
        val = random.randint(1, 20000)
    else:  # unidades soltas
        val = random.randint(1, 1000)
    return f"{val} {unit}"

def random_batch():
    """Gera batch number aleatório de 5 dígitos"""
    return random.randint(10000, 99999)

def random_sn(length=12):
    """Gera serial number alfanumérico"""
    chars = string.ascii_uppercase + string.digits
    return ''.join(random.choice(chars) for _ in range(length))

def random_expiration_date():
    """Gera data de validade futura ou 'NODATE'"""
    if random.random() < 0.2:
        return 'NODATE'
    # data entre hoje +30 e hoje +3650 dias (~10 anos)
    dt = datetime.today() + timedelta(days=random.randint(30, 3650))
    return dt.strftime('%d/%m/%Y')

def random_gtin14():
    """Gera GTIN-14 como string de 14 dígitos"""
    return ''.join(random.choice(string.digits) for _ in range(14))

def main(output_file='output.csv', n_records=15000):
    header = [
        'Label Number',
        'Company Name',
        'Company Address',
        'Product Description',
        'Net weight',
        'Batch Number',
        'Country of origin',
        'SN - Serial Number',
        'Expiration Date',
        'GTIN-14'
    ]

    with open(output_file, mode='w', newline='', encoding='utf-8') as f:
        writer = csv.writer(f, delimiter=';')
        writer.writerow(header)

        for i in range(1, n_records + 1):
            company = random.choice(COMPANIES)
            # Gera endereço aleatório ou usa endereço fixo pela empresa:
            address = fake.address().replace("\n", ", ")
            product = random.choice(PRODUCTS)
            weight = random_weight()
            batch = random_batch()
            country = random.choice(COUNTRIES)
            sn = random_sn(12)
            exp_date = random_expiration_date()
            gtin = random_gtin14()

            row = [
                i,
                company,
                address,
                product,
                weight,
                batch,
                country,
                sn,
                exp_date,
                gtin
            ]
            writer.writerow(row)

    print(f"Arquivo '{output_file}' gerado com {n_records} registros.")

if __name__ == '__main__':
    # Exemplo de uso: python script.py
    main()
