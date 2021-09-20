/*
 Navicat Premium Data Transfer

 Source Server         : MYSQL
 Source Server Type    : MySQL
 Source Server Version : 100132
 Source Host           : 127.0.0.1:3306
 Source Schema         : rocket_lapan

 Target Server Type    : MySQL
 Target Server Version : 100132
 File Encoding         : 65001

 Date: 20/09/2021 23:06:51
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for data_logger
-- ----------------------------
DROP TABLE IF EXISTS `data_logger`;
CREATE TABLE `data_logger`  (
  `id` bigint(11) NOT NULL AUTO_INCREMENT,
  `compas_x` int(11) NULL DEFAULT NULL,
  `compas_y` int(11) NULL DEFAULT NULL,
  `compas_z` int(11) NULL DEFAULT NULL,
  `azimuth` int(11) NULL DEFAULT NULL,
  `bearing` int(11) NULL DEFAULT NULL,
  `directional` varchar(5) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `temperature` float NULL DEFAULT NULL,
  `pressure` float NULL DEFAULT NULL,
  `altitude` float NULL DEFAULT NULL,
  `gps_latitude` float NULL DEFAULT NULL,
  `gps_longitude` float NULL DEFAULT NULL,
  `gps_age` int(11) NULL DEFAULT NULL,
  `gps_altitude` float NULL DEFAULT NULL,
  `gps_sat_value` float NULL DEFAULT NULL,
  `gps_course` float NULL DEFAULT NULL,
  `gps_speed` float NULL DEFAULT NULL,
  `rssi` float NULL DEFAULT NULL,
  `ctime` timestamp(0) NULL DEFAULT CURRENT_TIMESTAMP(0),
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Compact;

SET FOREIGN_KEY_CHECKS = 1;
