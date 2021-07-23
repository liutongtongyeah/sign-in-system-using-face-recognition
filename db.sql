-- MySQL dump 10.13  Distrib 5.7.9, for Win32 (AMD64)
--
-- Host: localhost    Database: sign_in
-- ------------------------------------------------------
-- Server version	5.7.12-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `attendance`
--

DROP TABLE IF EXISTS `attendance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `attendance` (
  `sno` varchar(8) NOT NULL,
  `cno` varchar(8) NOT NULL,
  `tno` varchar(8) NOT NULL,
  `sign1` int(11) DEFAULT NULL,
  PRIMARY KEY (`sno`,`cno`,`tno`),
  KEY `a-t_idx` (`tno`),
  KEY `a-c_idx` (`cno`),
  CONSTRAINT `a-c` FOREIGN KEY (`cno`) REFERENCES `course` (`cno`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `a-s` FOREIGN KEY (`sno`) REFERENCES `student` (`sno`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `a-t` FOREIGN KEY (`tno`) REFERENCES `teacher` (`tno`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `attendance`
--

LOCK TABLES `attendance` WRITE;
/*!40000 ALTER TABLE `attendance` DISABLE KEYS */;
INSERT INTO `attendance` VALUES ('13120101','08305001','01000202',NULL),('13120101','08305002','01000201',NULL),('13120102','08305001','01000202',NULL),('13120102','08305002','01000201',NULL),('13120103','08305001','01000202',NULL),('13120103','08305003','01000101',NULL),('13120104','08305001','01000202',NULL),('13120104','08305004','01000202',NULL),('13120105','08305001','01000202',NULL),('13120105','08305003','01000101',NULL),('13120106','08302001','01000103',NULL),('13120106','08305001','01000202',NULL);
/*!40000 ALTER TABLE `attendance` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `course`
--

DROP TABLE IF EXISTS `course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `course` (
  `cno` varchar(8) NOT NULL,
  `cname` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`cno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `course`
--

LOCK TABLES `course` WRITE;
/*!40000 ALTER TABLE `course` DISABLE KEYS */;
INSERT INTO `course` VALUES ('08301001','分子物理学'),('08302001','通信学'),('08305001','离散数学'),('08305002','数原理据库'),('08305003','数据结构'),('08305004','系统结构');
/*!40000 ALTER TABLE `course` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `open`
--

DROP TABLE IF EXISTS `open`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `open` (
  `cno` varchar(8) NOT NULL,
  `tno` varchar(8) NOT NULL,
  PRIMARY KEY (`cno`,`tno`),
  KEY `o-t_idx` (`tno`),
  CONSTRAINT `o-c` FOREIGN KEY (`cno`) REFERENCES `course` (`cno`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `o-t` FOREIGN KEY (`tno`) REFERENCES `teacher` (`tno`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `open`
--

LOCK TABLES `open` WRITE;
/*!40000 ALTER TABLE `open` DISABLE KEYS */;
INSERT INTO `open` VALUES ('08305003','01000101'),('08305001','01000102'),('08305004','01000102'),('08302001','01000103'),('08301001','01000201'),('08305002','01000201'),('08305001','01000202'),('08305002','01000202');
/*!40000 ALTER TABLE `open` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student`
--

DROP TABLE IF EXISTS `student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `student` (
  `sno` varchar(8) NOT NULL,
  `sname` varchar(45) DEFAULT NULL,
  `sex` varchar(2) DEFAULT NULL,
  `photo` varchar(90) DEFAULT NULL,
  PRIMARY KEY (`sno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student`
--

LOCK TABLES `student` WRITE;
/*!40000 ALTER TABLE `student` DISABLE KEYS */;
INSERT INTO `student` VALUES ('13120101','陈佩娴','女','D:\\photo\\光照归一化2\\1\\陈佩娴.jpg'),('13120102','赖传滨','男','D:\\photo\\光照归一化2\\2\\赖传滨.jpg'),('13120103','刘彤彤','女','D:\\photo\\光照归一化2\\3\\刘彤彤.jpg'),('13120104','陶婧琳','女','D:\\photo\\光照归一化2\\4\\陶婧琳.jpg'),('13120105','童麟','男','D:\\photo\\光照归一化2\\5\\童麟.jpg'),('13120106','徐世兴','男','D:\\photo\\光照归一化2\\6\\徐世兴.jpg');
/*!40000 ALTER TABLE `student` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `teacher`
--

DROP TABLE IF EXISTS `teacher`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `teacher` (
  `tno` varchar(8) NOT NULL,
  `tname` varchar(45) DEFAULT NULL,
  `sex` varchar(2) DEFAULT NULL,
  `username` varchar(45) DEFAULT NULL,
  `pwd` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`tno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `teacher`
--

LOCK TABLES `teacher` WRITE;
/*!40000 ALTER TABLE `teacher` DISABLE KEYS */;
INSERT INTO `teacher` VALUES ('01000101','陈迪茂','男','chen','123'),('01000102','马小红','女','ma','123'),('01000103','吴宝钢','男','wu','123'),('01000201','张心颖','女','zhang','123'),('01000202','liu','女','liu','123');
/*!40000 ALTER TABLE `teacher` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'sign_in'
--

--
-- Dumping routines for database 'sign_in'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-06-11  6:19:08
