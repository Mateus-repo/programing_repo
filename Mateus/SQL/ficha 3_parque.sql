CREATE DATABASE IF NOT EXISTS `parque` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE `parque`;



CREATE TABLE `cliente` (
  `nif` int NOT NULL,
  `nome` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`nif`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;



INSERT INTO `cliente` (`nif`, `nome`) VALUES
(1231, 'João Silva'),
(1232, 'Miguel Tavares'),
(1233, 'Maria Abrantes'),
(1234, 'Teresa Carvalho'),
(1235, 'Manuel Pereira'),
(1236, 'Bernardo Sousa'),
(1237, 'Carlos Pinto'),
(1238, 'Raquel Martins'),
(1239, 'Filipe Monteiro');



CREATE TABLE `carro` (
  `matricula` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `marca` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `nif` int NOT NULL,
  PRIMARY KEY (`matricula`),
  KEY `nif_fk_idx` (`nif`),
  CONSTRAINT `nif_fk` FOREIGN KEY (`nif`) REFERENCES `cliente` (`nif`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;



INSERT INTO `carro` (`matricula`, `marca`, `nif`) VALUES
('11-45-MA', 'Ford', 1233),
('12-TC-16', 'Lancia', 1234),
('13-73-BS', 'Toyota', 1236),
('27-FM-62', 'Volkswagen', 1239),
('34-JS-65', 'Mercedes', 1231),
('43-MT-12', 'Fiat', 1232),
('54-MT-97', 'Fiat', 1232),
('58-TC-85', 'Peugeot', 1234),
('84-RM-65', 'Citroen', 1238),
('BS-87-16', 'Nissan', 1236),
('CP-53-73', 'Ferrari', 1237),
('JS-12-34', 'Honda', 1231),
('MA-83-28', 'Ford', 1233),
('MP-11-11', 'Lancia', 1235),
('MT-43-32', 'Volvo', 1232),
('TC-59-99', 'Peugeot', 1234);



CREATE TABLE `lugar` (
  `numero` int NOT NULL AUTO_INCREMENT,
  `andar` int DEFAULT NULL,
  PRIMARY KEY (`numero`),
  UNIQUE KEY `numero` (`numero`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

INSERT INTO `lugar` (`numero`, `andar`) VALUES
(1, 1),
(2, 1),
(3, 1),
(4, 1),
(5, 1),
(6, 1),
(7, 2),
(8, 2),
(9, 2),
(10, 2),
(11, 2),
(12, 3),
(13, 3),
(14, 3),
(15, 4),
(16, 4);



CREATE TABLE `estacionamento` (
  `ref` bigint NOT NULL AUTO_INCREMENT,
  `data` date DEFAULT NULL,
  `horae` time DEFAULT NULL,
  `horas` time DEFAULT NULL,
  `numero` int NOT NULL,
  `matricula` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`ref`),
  UNIQUE KEY `ref` (`ref`),
  KEY `numero_fk_idx` (`numero`),
  KEY `matricula_fk_idx` (`matricula`),
  CONSTRAINT `matricula_fk` FOREIGN KEY (`matricula`) REFERENCES `carro` (`matricula`),
  CONSTRAINT `numero_fk` FOREIGN KEY (`numero`) REFERENCES `lugar` (`numero`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;


INSERT INTO `estacionamento` (`ref`, `data`, `horae`, `horas`, `numero`, `matricula`) VALUES
(1, '2010-01-01', '10:00:00', '12:41:00', 1, '27-FM-62'),
(2, '2010-01-01', '15:34:00', '18:45:00', 2, '27-FM-62'),
(3, '2010-01-01', '10:19:00', '22:42:00', 3, 'JS-12-34'),
(4, '2010-01-01', '11:37:00', '18:15:00', 4, 'CP-53-73'),
(5, '2010-01-01', '07:32:00', '09:41:00', 5, 'TC-59-99'),
(6, '2010-01-02', '10:45:00', '15:43:00', 1, '84-RM-65'),
(7, '2010-01-02', '10:14:00', '12:36:00', 2, 'BS-87-16'),
(8, '2010-01-02', '09:49:00', '12:58:00', 3, '12-TC-16'),
(9, '2010-01-02', '11:51:00', '14:34:00', 4, '58-TC-85'),
(10, '2010-01-02', '10:33:00', '12:35:00', 5, 'MA-83-28'),
(11, '2010-01-02', '11:14:00', '16:34:00', 8, 'MT-43-32'),
(12, '2010-01-02', '17:44:00', '18:54:00', 12, '43-MT-12'),
(13, '2010-01-02', '10:22:00', '14:43:00', 13, '54-MT-97'),
(14, '2010-01-03', '09:01:00', '14:37:00', 1, '27-FM-62'),
(15, '2010-01-03', '13:45:00', '21:11:00', 2, '84-RM-65'),
(16, '2010-01-03', '08:23:00', '15:55:00', 6, 'CP-53-73'),
(17, '2010-01-03', '11:53:00', '14:11:00', 7, 'MP-11-11'),
(18, '2010-01-03', '06:46:00', '08:26:00', 8, '12-TC-16'),
(19, '2010-01-03', '09:39:00', '17:15:00', 10, 'MA-83-28'),
(20, '2010-01-03', '07:25:00', '08:12:00', 11, '43-MT-12'),
(21, '2010-01-03', '09:16:00', '11:21:00', 12, '43-MT-12'),
(22, '2010-01-03', '11:21:00', '13:42:00', 13, '34-JS-65'),
(23, '2010-01-03', '14:47:00', '18:12:00', 14, '34-JS-65');

