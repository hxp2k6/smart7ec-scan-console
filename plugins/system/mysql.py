#coding:utf-8

import MySQLdb

# 测试脚本输出信息
def info():
	msg = {
		# 测试用例名称
		"name" : "MySQL Service Attack",
		# 测试用例针对应用版本
		"version" : "all",
		# 测试用例描述
		"desc" : '''
			用于测试 MYSQL 弱口令。
		''',
		# 解决建议
		"proposed": '''
			修改口令，或停用该服务。
		''',
		# 测试用例开发者
		"author" : "Smarttang",
		# 测试用例应用范围
		"type" : "service",
		# 测试用例产出风险危害等级 high,medium,low
		"severity" : "high",
		# 测试用例开发时间
		"create_date" : "2016-2-17",
		# 测试用例最后更新时间
		"update_date" : "2016-2-17",
		# 漏洞输出模版(多个模版按照序号排列)
		"vul_template_1": "[*] MySQL Weak passwords Host: %s Username: %s Password: %s",
		# 扫描漏洞结果
		"vul_res": []
	}
	return msg

# 漏洞测试(不存储结果，直接输出，返回状态给主程序)
def verify_print(host,port):
	_info = info()

	# 字典爆破测试
	for username in open("dic/mysql_user.dic","r"):
		for password in open("dic/mysql_pass.dic","r"):
			_username = username.strip()
			_password = password.strip()

			db = None
			try:
				db = MySQLdb.connect(host=host, user=_username, passwd=_password, port=3306)
				print _info['vul_template_1'] % (host,_username,_password)
				_info['vul_res'].append([host,_username,_password])
			except:
				pass
			finally:
				if db:
					db.close()

	return len(_info['vul_res'])

# 漏洞测试(存储测试结果，上传到安全平台)
def verify_save(host,port):
	pass
