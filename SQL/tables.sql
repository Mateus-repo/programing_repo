create table clientes (
	id_cliente INT Primary Key Not null auto_increment,
	nome varchar(50) Not null,
    email varchar(50),
    telefone varchar(20)
);
create table produtos (
	id_produto INT Primary Key Not null auto_increment,
	nome varchar(50) Not null,
	preco decimal(10,2) NOT NULL,
    stock INT NOT NULL
);
create table pedidos (
	id_pedido INT Primary Key Not null auto_increment,
	id_cliente INT NOT NULL,
    FOREIGN KEY (id_cliente) REFERENCES clientes(id_cliente),
    data_pedido DATE NOT NULL
);
create table itens_pedido (
	id_item_pedido INT Primary Key Not null auto_increment,
	id_pedido INT NOT NULL,
    FOREIGN KEY (id_pedido) REFERENCES pedidos(id_pedido),
    id_produto INT NOT NULL,
    FOREIGN KEY (id_produto) REFERENCES produtos(id_produto),
    quantidade INT NOT NULL,
    preco_unitario decimal(10,2) not null,
    valor_total decimal(10,2) not null
);