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

 Date: 25/09/2021 09:45:56
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
  `gps_latitude` double NULL DEFAULT NULL,
  `gps_longitude` double NULL DEFAULT NULL,
  `gps_age` int(11) NULL DEFAULT NULL,
  `gps_altitude` float NULL DEFAULT NULL,
  `gps_sat_value` float NULL DEFAULT NULL,
  `gps_course` float NULL DEFAULT NULL,
  `gps_speed` float NULL DEFAULT NULL,
  `rssi` float NULL DEFAULT NULL,
  `ctime` timestamp(0) NULL DEFAULT CURRENT_TIMESTAMP(0),
  `profile_id` int(2) NULL DEFAULT 1,
  `photo_id` bigint(20) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 57632 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Table structure for data_photo
-- ----------------------------
DROP TABLE IF EXISTS `data_photo`;
CREATE TABLE `data_photo`  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `photo` longtext CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL,
  `ctime` timestamp(0) NULL DEFAULT CURRENT_TIMESTAMP(0),
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 43054 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Table structure for data_profile
-- ----------------------------
DROP TABLE IF EXISTS `data_profile`;
CREATE TABLE `data_profile`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `profile_name` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `is_active` int(2) NULL DEFAULT 0,
  `is_delete` int(2) NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 6 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Compact;

SET FOREIGN_KEY_CHECKS = 1;
