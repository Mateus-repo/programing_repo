

CREATE TABLE `cliente` (
  `ref` int NOT NULL,
  `nome` varchar(256) NOT NULL,
  `cidade` varchar(256) NOT NULL,
  `pais` varchar(256) NOT NULL,
  PRIMARY KEY (`ref`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `cliente` VALUES (100,'Joao','Porto','Portugal'),(101,'Carlos','Lisboa','Portugal'),(102,'Maria','Porto','Portugal'),(103,'Fritz','Munique','Alemanha'),(104,'Teresa','Coimbra','Portugal'),(105,'John','Londres','Inglaterra');



CREATE TABLE `tipoquarto` (
  `id` int NOT NULL,
  `designacao` varchar(256) NOT NULL,
  `lotacao` int NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `tipoquarto` VALUES (1,'Single',1),(2,'Duplo',2),(3,'Suite',4),(4,'Suite Presidencial',4);



CREATE TABLE `quarto` (
  `num` int NOT NULL,
  `andar` int NOT NULL,
  `idtipo` int DEFAULT NULL,
  PRIMARY KEY (`num`),
  KEY `fk_id_tipo_idx` (`idtipo`),
  CONSTRAINT `fk_id_tipo` FOREIGN KEY (`idtipo`) REFERENCES `tipoquarto` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


INSERT INTO `quarto` VALUES (11,1,1),(12,1,1),(13,1,1),(14,1,2),(15,1,2),(21,2,1),(22,2,1),(23,2,2),(24,2,2),(31,3,3),(32,3,3),(33,3,4);



CREATE TABLE `reserva` (
  `id_reserva` int NOT NULL AUTO_INCREMENT,
  `num_quarto` int NOT NULL,
  `ref_cliente` int NOT NULL,
  `data_e` date NOT NULL,
  `data_s` date NOT NULL,
  `regime` char(2) NOT NULL,
  `numeropessoas` int NOT NULL,
  PRIMARY KEY (`id_reserva`),
  KEY `fk_ref_cliente_idx` (`ref_cliente`),
  KEY `fk_num_quarto_idx` (`num_quarto`),
  CONSTRAINT `fk_num_quarto` FOREIGN KEY (`num_quarto`) REFERENCES `quarto` (`num`),
  CONSTRAINT `fk_ref_cliente` FOREIGN KEY (`ref_cliente`) REFERENCES `cliente` (`ref`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


INSERT INTO `reserva` VALUES (1,21,100,'2023-01-02','2023-01-03','PA',1),(2,22,101,'2023-01-14','2023-01-17','MP',1),(3,24,102,'2023-01-08','2023-01-12','PC',2),(4,31,103,'2023-01-04','2023-01-05','MP',2),(5,33,104,'2023-01-18','2023-01-19','MP',3),(6,11,101,'2023-01-02','2023-01-07','PC',1),(7,14,105,'2023-01-09','2023-01-11','PA',2),(8,31,101,'2023-02-05','2023-02-15','PA',3),(9,21,102,'2023-01-20','2023-01-25','MP',1),(10,22,103,'2023-02-20','2023-02-22','PC',1);



