CREATE DATABASE `guatoj`;

CREATE TABLE `department`
(
    `dept_name` VARCHAR(30) NOT NULL,
    `dept_major` VARCHAR(20) NOT NULL,

    CONSTRAINT `dept_primary` PRIMARY KEY(`dept_name`, `dept_major`)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;

CREATE TABLE `user`
(
    `user_login_count` VARCHAR(20) NOT NULL,
    `user_login_passwd` VARCHAR(30) NOT NULL,
    `user_name` VARCHAR(10) DEFAULT '',
    `user_level` TINYINT DEFAULT 0,
    `user_student_id` VARCHAR(25) DEFAULT '',
    `dept_name` VARCHAR(30) NOT NULL,
    `dept_major` VARCHAR(20) NOT NULL,
    
    CONSTRAINT `user_primary` PRIMARY KEY(`user_login_count`),
    CONSTRAINT `user_fk1` FOREIGN KEY(`dept_name`, `dept_major`) REFERENCES `department`(`dept_name`, `dept_major`)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;

CREATE TABLE `question`
(
    `qst_id` INT NOT NULL,
    `qst_description_path` VARCHAR(50) NOT NULL,
    `qst_input_path` VARCHAR(50) NOT NULL,
    `qst_output_path` VARCHAR(50) NOT NULL,

    CONSTRAINT qst_primary PRIMARY KEY(`qst_id`)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;

CREATE TABLE `submit`
(
    `user_login_count` VARCHAR(20) NOT NULL,
    `submit_time` DATETIME NOT NULL,
    `qst_id` INT NOT NULL,
    `submit_status` TINYINT NOT NULL,
    `submit_path` VARCHAR(50) NOT NULL,

    CONSTRAINT submit_primary PRIMARY KEY(`user_login_count`, `submit_time`),
    CONSTRAINT submit_fk1 FOREIGN KEY(`user_login_count`) REFERENCES `user`(`user_login_count`),
    CONSTRAINT submit_fk2 FOREIGN KEY(`qst_id`) REFERENCES `question`(`qst_id`)
) ENGINE = InnoDB DEFAULT CHARSET = utf8;

CREATE TABLE `course`
(
    `course_id` TINYINT NOT NULL AUTO_INCREMENT,
    `user_login_count` VARCHAR(20) NOT NULL,
    `dept_name` VARCHAR(30) NOT NULL,
    `dept_major` VARCHAR(20) NOT NULL,
    `course_name` VARCHAR(30) NOT NULL,

    CONSTRAINT course_primary PRIMARY KEY(`course_id`),
    CONSTRAINT course_fk1 FOREIGN KEY(`user_login_count`) REFERENCES `user`(`user_login_count`),
    CONSTRAINT course_fk2 FOREIGN KEY(`dept_name`, `dept_major`) REFERENCES `department`(`dept_name`, `dept_major`)
) ENGINE = InnoDB DEFAULT CHARSET = utf8