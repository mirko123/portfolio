-- phpMyAdmin SQL Dump
-- version 4.6.5.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time:  7 юли 2017 в 17:14
-- Версия на сървъра: 10.1.21-MariaDB
-- PHP Version: 7.1.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `web`
--

-- --------------------------------------------------------

--
-- Структура на таблица `ids`
--

CREATE TABLE `ids` (
  `id` int(11) NOT NULL,
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `lecture` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `credits` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Схема на данните от таблица `ids`
--

INSERT INTO `ids` (`id`, `name`, `lecture`, `credits`) VALUES
(3, 'Логическо Програмиране', 'sss', 10),
(4, 'ddddsad', 'sss', 23),
(9, 'ddddsad', 'xxx', 4),
(10, 'test', 'sss', 3),
(13, 'дадаасдасд', 'eee', 515),
(14, 'dasdasdas', 'eee', 15),
(15, 'WEB', 'ddz', 1000),
(16, 'CPPPPPP', 'nov', 1000),
(17, 'NEEEEEE', 'nov', 100),
(18, 'WEB', 'test', 10),
(19, 'WEB2', 'test', 1000);

-- --------------------------------------------------------

--
-- Структура на таблица `lectures`
--

CREATE TABLE `lectures` (
  `id` int(6) UNSIGNED NOT NULL,
  `username` varchar(30) NOT NULL,
  `department` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `email` varchar(50) DEFAULT NULL,
  `password` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Схема на данните от таблица `lectures`
--

INSERT INTO `lectures` (`id`, `username`, `department`, `email`, `password`) VALUES
(1, 'prep4', '', 'prep4', 'f10e2821bbbea527ea02200352313bc059445190'),
(2, 'prep5', '', 'prep5', '741617a9f4acbbf62d0bc512569b5c99adcbdc3e'),
(3, 'ddz', 'Информационни технологии', 'ddz', '7f8a799581d1eed13647dd7670eae72da6744022'),
(4, 'sss', 'Компютърна информатика', 'sss', 'bf9661defa3daecacfde5bde0214c4a439351d4d'),
(5, 'xxx', '', 'xxx', 'b60d121b438a380c343d5ec3c2037564b82ffef3'),
(8, 'eee', '', 'eee', '637a81ed8e8217bb01c15c67c39b43b0ab4e20f1'),
(10, 'nov', 'Информационни технологии', 'nov', '33bea6ef7ea3955224ef24bcb9129f1d039b6a0d'),
(11, 'test', 'Информационни технологии', 'test', 'a94a8fe5ccb19ba61c4c0873d391e987982fbbd3');

-- --------------------------------------------------------

--
-- Структура на таблица `time_distribution`
--

CREATE TABLE `time_distribution` (
  `id` int(11) NOT NULL,
  `start` int(11) DEFAULT NULL,
  `finish` int(11) DEFAULT NULL,
  `room` int(11) DEFAULT NULL,
  `id_id` int(11) DEFAULT NULL,
  `type` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `day` int(11) DEFAULT NULL,
  `discription` varchar(250) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT 'Няма Описание'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Схема на данните от таблица `time_distribution`
--

INSERT INTO `time_distribution` (`id`, `start`, `finish`, `room`, `id_id`, `type`, `day`, `discription`) VALUES
(5, 1, 3, 325, 13, 'Упражнение', 1, 'Няма описание'),
(6, 12, 23, 323, 13, 'Лекция', 1, 'Няма описание'),
(7, 13, 15, 324, 13, 'Лекция', 2, 'Няма описание'),
(8, 20, 22, 325, 13, 'Лекция', 2, 'Няма описание'),
(20, 11, 13, 23, 4, 'Лекция', 1, 'Няма описание'),
(21, 13, 15, 31, 3, 'Лекция', 1, 'Няма описание'),
(22, 12, 14, 325, 15, 'Лекция', 1, 'Няма описание'),
(24, 15, 20, 123, 16, 'Упражнение', 2, 'Kvot takovata'),
(26, 10, 11, 123, 17, 'Лекция', 2, ''),
(27, 12, 13, 123, 17, 'Лекция', 2, 'Има описание'),
(28, 18, 19, 123, 16, 'Лекция', 2, ''),
(31, 10, 15, 314, 18, 'Лекция', 3, ''),
(32, 19, 20, 325, 19, 'Лекция', 3, '');

-- --------------------------------------------------------

--
-- Структура на таблица `users`
--

CREATE TABLE `users` (
  `id` int(10) UNSIGNED NOT NULL,
  `username` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `password` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `speciality` varchar(20) COLLATE utf8mb4_unicode_ci DEFAULT 'SI',
  `course` int(11) DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Схема на данните от таблица `users`
--

INSERT INTO `users` (`id`, `username`, `email`, `password`, `speciality`, `course`) VALUES
(62, 'mirko', 'asd', 'f10e2821bbbea527ea02200352313bc059445190', 'SI', 4),
(63, 'lek', 'lek', 'aa5f6d73039cf60151a0290ccdbef4f8645b5f84', 'SI', 1),
(65, 'lek1', 'lek1', 'ab2c845a0d16321320c353bf262eee65451a211a', 'SI', 1),
(66, 'pato', 'pato', '269cb45d944e48836d6e92d5f74ea339807882af', 'SI', 1),
(67, 'prep', 'prep', '2916a72bc301eb3cb0d07ace92f345047a7a0696', 'SI', 1),
(68, 'prep3', 'prep3', '91e2823d988ac9637113b5444fd4f7f3eecabb23', 'SI', 1),
(69, 'aaa', 'aaa', '7e240de74fb1ed08fa08d38063f6a6a91462a815', 'SI', 1),
(70, 'ddd', 'ddd', '9c969ddf454079e3d439973bbab63ea6233e4087', 'SI', 1),
(71, 'vvv', 'vvv', 'dbe6cae2f52b55095b513c15321b934146828d76', 'SI', 1),
(72, 'fff', 'ffff', 'f6949a8c7d5b90b4a698660bbfb9431503fbb995', 'SI', 1),
(74, 'new', 'new', 'c2a6b03f190dfb2b4aa91f8af8d477a9bc3401dc', 'SI', 1),
(75, 'test1', 'test1', 'b444ac06613fc8d63795be9ad0beaf55011936ac', 'SI', 3);

-- --------------------------------------------------------

--
-- Структура на таблица `user_ids`
--

CREATE TABLE `user_ids` (
  `username` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `id` int(11) NOT NULL,
  `priority` int(11) NOT NULL DEFAULT '0',
  `id_id` int(11) NOT NULL DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Схема на данните от таблица `user_ids`
--

INSERT INTO `user_ids` (`username`, `id`, `priority`, `id_id`) VALUES
('aaa', 32, 15, 3),
('mirko', 33, 1, 13),
('mirko', 34, 0, 14),
('mirko', 35, 2, 15),
('mirko', 36, 3, 10),
('mirko', 37, 3, 16),
('mirko', 38, 3, 17),
('pato', 39, 1, 15),
('pato', 40, 1, 16),
('pato', 42, 1, 17),
('new', 43, 1, 16),
('test1', 44, 1, 18),
('test1', 45, 2, 19);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `ids`
--
ALTER TABLE `ids`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `name` (`name`,`lecture`);

--
-- Indexes for table `lectures`
--
ALTER TABLE `lectures`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `UC_unic_username` (`username`);

--
-- Indexes for table `time_distribution`
--
ALTER TABLE `time_distribution`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `start` (`start`,`finish`,`room`),
  ADD KEY `foreign_cascade_del_id_time` (`id_id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `username` (`username`);

--
-- Indexes for table `user_ids`
--
ALTER TABLE `user_ids`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `UC_unic_id` (`username`,`id_id`),
  ADD KEY `foreign_cascade_del_id` (`id_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `ids`
--
ALTER TABLE `ids`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;
--
-- AUTO_INCREMENT for table `lectures`
--
ALTER TABLE `lectures`
  MODIFY `id` int(6) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
--
-- AUTO_INCREMENT for table `time_distribution`
--
ALTER TABLE `time_distribution`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=33;
--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=76;
--
-- AUTO_INCREMENT for table `user_ids`
--
ALTER TABLE `user_ids`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=46;
--
-- Ограничения за дъмпнати таблици
--

--
-- Ограничения за таблица `time_distribution`
--
ALTER TABLE `time_distribution`
  ADD CONSTRAINT `foreign_cascade_del_id_time` FOREIGN KEY (`id_id`) REFERENCES `ids` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения за таблица `user_ids`
--
ALTER TABLE `user_ids`
  ADD CONSTRAINT `foreign_cascade_del_id` FOREIGN KEY (`id_id`) REFERENCES `ids` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
