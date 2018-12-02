USE guatoj;
INSERT INTO `department` VALUES('非在校学生', '无');
INSERT INTO `department` VALUES('计算机科学与工程学院', '软件工程');
INSERT INTO `department` VALUES('计算机科学与工程学院', '物联网工程');
INSERT INTO `department` VALUES('计算机科学与工程学院', '计算机网络');
INSERT INTO `department` VALUES('计算机科学与工程学院', '计算机应用');
INSERT INTO `department` VALUES('传媒与艺术设计学院', '视觉传达设计');
INSERT INTO `department` VALUES('传媒与艺术设计学院', '数字媒体技术');
INSERT INTO `department` VALUES('传媒与艺术设计学院', '动漫制作技术');
INSERT INTO `department` VALUES('传媒与艺术设计学院', '建筑室内设计');
INSERT INTO `department` VALUES('机械工程学院', '机械电子工程');
INSERT INTO `department` VALUES('机械工程学院', '材料成型及其控制工程');
INSERT INTO `department` VALUES('机械工程学院', '飞行器制造工程');
INSERT INTO `department` VALUES('机械工程学院', '机械设计制造及其自动化');
INSERT INTO `department` VALUES('机械工程学院', '机电一体化技术');
INSERT INTO `department` VALUES('机械工程学院', '机械制造与自动化');
INSERT INTO `department` VALUES('电子信息与自动化学院', '通信工程');
INSERT INTO `department` VALUES('电子信息与自动化学院', '电子信息工程');
INSERT INTO `department` VALUES('电子信息与自动化学院', '自动化');
INSERT INTO `department` VALUES('电子信息与自动化学院', '测控技术与仪器');
INSERT INTO `department` VALUES('电子信息与自动化学院', '飞行器质量与可靠性');
INSERT INTO `department` VALUES('电子信息与自动化学院', '无人机应用技术');
INSERT INTO `department` VALUES('电子信息与自动化学院', '通信技术');
INSERT INTO `department` VALUES('电子信息与自动化学院', '电子信息工程技术');

INSERT INTO `user` VALUES('linkcheng', 'linkcheng', '程杰仕', 3, '2015070030337', '计算机科学与工程学院', '软件工程');
INSERT INTO `user` VALUES('wenhaoqiu', 'wenhaoqiu', '仇文豪', 3, '2015070030422', '计算机科学与工程学院', '软件工程');
INSERT INTO `user` VALUES('panxisu', 'panxisu', '苏攀西', 3, '2015070030438', '计算机科学与工程学院', '软件工程');
INSERT INTO `user` VALUES('mengyuanwu', 'mengyuanwu', '吴梦圆', 3, '2015070030315', '非在校学生', '无');

INSERT INTO `question`(`qst_description_path`, `qst_input_path`, `qst_output_path`) VALUES('/Users/jieshi/DataBase/1/description.txt', '/Users/jieshi/DataBase/1/input/', '/Users/jieshi/DataBase/1/output/');
INSERT INTO `question`(`qst_description_path`, `qst_input_path`, `qst_output_path`) VALUES('/Users/jieshi/DataBase/2/description.txt', '/Users/jieshi/DataBase/2/input/', '/Users/jieshi/DataBase/2/output/');

INSERT INTO `submit` VALUES('linkcheng', '2018-06-08 11:14:20', 1, 0, '/Users/jieshi/DataBase/linkcheng1.c');
INSERT INTO `submit` VALUES('linkcheng', '2018-06-19 19:08:22', 2, 0, '/Users/jieshi/DataBase/linkcheng2.c');

INSERT INTO `course`(`user_login_count`, `dept_name`, `dept_major`, `course_name`) VALUES('linkcheng', '计算机科学与工程学院', '软件工程', '计算机导论');



