import pymysql
DB_CONFIG = {

'host' : 'localhost',

'port' : 3306,

'user' : 'root',

'password' : 'D2#B15',

'database' : "gestao_produtos"

}

conexaoDB = pymysql.connect(

    host=DB_CONFIG['host'],

    port=DB_CONFIG['port'],

    user=DB_CONFIG['user'],

    password=DB_CONFIG['password'],

    database=DB_CONFIG['database']
)