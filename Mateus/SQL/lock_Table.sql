
--
-- Table structure for table `tipo`
--

DROP TABLE IF EXISTS `tipo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tipo` (
  `numtipo` int NOT NULL,
  `desig_tipo` varchar(50) NOT NULL,
  PRIMARY KEY (`numtipo`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tipo`
--

LOCK TABLES `tipo` WRITE;
/*!40000 ALTER TABLE `tipo` DISABLE KEYS */;
INSERT INTO `tipo` VALUES (1,'informática'),(2,'decoração'),(3,'generalista'),(4,'desporto'),(5,'escolar'),(6,'culinária'),(7,'automóvel'),(8,'saúde');
/*!40000 ALTER TABLE `tipo` ENABLE KEYS */;
UNLOCK TABLES;



--
-- Table structure for table `revista`
--

DROP TABLE IF EXISTS `revista`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `revista` (
  `numrevista` int NOT NULL,
  `nome` varchar(100) NOT NULL,
  `numtipo` int NOT NULL,
  `preco` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`numrevista`),
  KEY `numtipo` (`numtipo`),
  CONSTRAINT `revista_ibfk_1` FOREIGN KEY (`numtipo`) REFERENCES `tipo` (`numtipo`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `revista`
--

LOCK TABLES `revista` WRITE;
/*!40000 ALTER TABLE `revista` DISABLE KEYS */;
INSERT INTO `revista` VALUES (1,'001 Ordemparaler',5,1.10),(2,'Base de Dados',1,1.50),(3,'Modelos Relacionais',3,0.90),(4,'Gestão Doméstica',2,1.00),(5,'Saúde & Medicina',8,2.00),(6,'Aprenda a descobrir',6,2.20),(7,'Autotractor',7,1.60),(8,'Dê cabo do PC',1,1.70),(9,'SQL: uma aventura',1,1.20),(10,'Comer e beber melhor',6,1.40),(11,'Sempre a correr',4,0.80),(12,'Outros e outras',3,1.80);
/*!40000 ALTER TABLE `revista` ENABLE KEYS */;
UNLOCK TABLES;



DROP TABLE IF EXISTS `edicao`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `edicao` (
  `id_edicao` int NOT NULL AUTO_INCREMENT,
  `numedicao` int NOT NULL,
  `data` date NOT NULL,
  `numrevista` int NOT NULL,
  PRIMARY KEY (`id_edicao`),
  KEY `numrevista` (`numrevista`),
  CONSTRAINT `edicao_ibfk_1` FOREIGN KEY (`numrevista`) REFERENCES `revista` (`numrevista`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `edicao`
--

LOCK TABLES `edicao` WRITE;
/*!40000 ALTER TABLE `edicao` DISABLE KEYS */;
INSERT INTO `edicao` VALUES (1,1,'2013-01-01',1),(2,2,'2013-01-30',4),(3,3,'2013-02-02',1),(4,4,'2013-03-01',2),(5,5,'2013-03-02',5),(6,6,'2013-04-12',8),(7,7,'2013-07-01',6),(8,8,'2013-08-02',5),(9,9,'2013-03-02',8),(10,8,'2013-04-02',8);
/*!40000 ALTER TABLE `edicao` ENABLE KEYS */;
UNLOCK TABLES;



--
-- Table structure for table `tema`
--

DROP TABLE IF EXISTS `tema`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tema` (
  `numtema` int NOT NULL,
  `desig_tema` varchar(100) NOT NULL,
  PRIMARY KEY (`numtema`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tema`
--

LOCK TABLES `tema` WRITE;
/*!40000 ALTER TABLE `tema` DISABLE KEYS */;
INSERT INTO `tema` VALUES (1,'Internet'),(2,'Comemoração dos 25 anos da escola'),(3,'Normalização'),(4,'Testes de Software'),(5,'Higiene e saúde dos bebés'),(6,'Os melhores tractores'),(7,'Dê cabo do disco rígido'),(8,'Receitas rápidas ou não'),(9,'Backup'),(10,'Atletismo lento');
/*!40000 ALTER TABLE `tema` ENABLE KEYS */;
UNLOCK TABLES;


--
-- Table structure for table `titulo`
--

DROP TABLE IF EXISTS `titulo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `titulo` (
  `numtitulo` int NOT NULL AUTO_INCREMENT,
  `desig_titulo` varchar(200) NOT NULL,
  `paginicio` int NOT NULL,
  `pagfim` int NOT NULL,
  `numedicao` int NOT NULL,
  `numtema` int NOT NULL,
  PRIMARY KEY (`numtitulo`),
  KEY `numedicao` (`numedicao`),
  KEY `numtema` (`numtema`),
  CONSTRAINT `titulo_ibfk_1` FOREIGN KEY (`numedicao`) REFERENCES `edicao` (`id_edicao`),
  CONSTRAINT `titulo_ibfk_2` FOREIGN KEY (`numtema`) REFERENCES `tema` (`numtema`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `titulo`
--

LOCK TABLES `titulo` WRITE;
/*!40000 ALTER TABLE `titulo` DISABLE KEYS */;
INSERT INTO `titulo` VALUES (1,'As BD',5,7,2,3),(2,'Escrever bom português',2,4,2,1),(3,'Fraldas descartáveis',6,7,3,5),(4,'Software Microsoft',5,7,4,4),(5,'As eleições legislativas',7,10,3,4),(6,'O melhor leitão',15,19,6,8),(7,'Comprar um disco novo',22,24,7,7),(8,'Tractor: ferrari',5,9,8,6),(9,'Net a mais',15,19,6,1),(10,'Corra no sofá',4,5,4,10);
/*!40000 ALTER TABLE `titulo` ENABLE KEYS */;
UNLOCK TABLES;
