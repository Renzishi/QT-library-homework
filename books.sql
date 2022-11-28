CREATE DATABASE bookstore;
USE bookstore;
CREATE TABLE `admin` (
  `aid` int(11) NOT NULL AUTO_INCREMENT,
  `account` varchar(20) NOT NULL,
  `name` varchar(20) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `email` varchar(255) DEFAULT NULL,
  `type` int(2) DEFAULT '0',
  `max_land_num` int(11) DEFAULT 5,
  `max_land_day` int(11) DEFAULT 90,
  `credit` int(11) DEFAULT 100,
  `addr` varchar(255) DEFAULT '/def.png',
  PRIMARY KEY (`aid`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb3;

INSERT INTO `admin` VALUES ('1', 'root', 'administer', MD5("root"), '123456.@a.com', '1', '4', '120', '100', '1.png');
INSERT INTO `admin` VALUES ('2', 'user', 'User-a', MD5("user"), 'abcde.@a.com', '0', '4', '90', '100', 'def.png');
INSERT INTO `admin` VALUES ('3', '123', 'User-tt', MD5("123"), 'abcde.@a.com', '2', '5', '60', '60', 'def.png');

CREATE TABLE `book` (
  `bid` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `autho` varchar(50)  DEFAULT NULL,
  `stock` int(11) NOT NULL,
  `type` varchar(50) DEFAULT NULL,
  `press` varchar(50) DEFAULT NULL,
  `address` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`bid`)
) ENGINE=InnoDB AUTO_INCREMENT=100 DEFAULT CHARSET=utf8mb3;

INSERT INTO `book` VALUES ('1', '活着', '余华', '5', '小说', '作家出版社', '1.png');
INSERT INTO `book` VALUES ('2', '城南旧事', '林海音', '7', '小说', '中国青年出版社', '2.png');
INSERT INTO `book` VALUES ('3', '西游记', '吴承恩', '17', '名著', '人民文学出版社', '3.png');
INSERT INTO `book` VALUES ('4', '高等数学第二版', '孙建国', '5', '教材', '高等教育出版社', '4.png');
INSERT INTO `book` VALUES ('5', 'Java', 'none', '5', '教材', '高等教育出版社', '5.png');

CREATE TABLE `history` (
  `hid` int(11) NOT NULL AUTO_INCREMENT,
  `bid` int(11) DEFAULT NULL,
  `name` varchar(50) NOT NULL,
  `autho` varchar(50)  DEFAULT NULL,
  `aid` int(11) DEFAULT NULL,
  `isReturn` int(2) DEFAULT NULL,
  `beginDate` DATE DEFAULT NULL,
  `deadLine` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`hid`)
) ENGINE=InnoDB AUTO_INCREMENT=100 DEFAULT CHARSET=utf8mb3;

INSERT INTO `history` VALUES ('1', '2', '城南旧事', '林海音', '1', '1', '2022-01-01', '2022-03-01');
INSERT INTO `history` VALUES ('2', '5', 'Java', 'none', '1', '0', '2022-06-30', '2022-10-30');
INSERT INTO `history` VALUES ('3', '2', '城南旧事', '林海音', '2', '1', '2022-05-30', '2022-06-30');
INSERT INTO `history` VALUES ('4', '3', '西游记', '吴承恩', '2', '0', '2022-03-30', '2022-06-30');