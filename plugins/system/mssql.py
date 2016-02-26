#coding:utf-8

import pymssql

# 测试脚本输出信息
def info():
	msg = {
		# 测试用例名称
		"name" : "MSSQL Service Attack",
		# 测试用例针对应用版本
		"version" : "all",
		# 测试用例描述
		"desc" : '''
			用于测试 MSSQL 弱口令。
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
		"vul_template_1": "[*] MSSQL Weak passwords Host: %s Username: %s Password: %s",
		# 扫描漏洞结果
		"vul_res": []
	}
	return msg

# 漏洞测试(不存储结果，直接输出，返回状态给主程序)
def verify_print(host,port):
	_info = info()

	for username in open("dic/ftp_user.dic"):
		for password in open("dic/ftp_pass.dic"):
			_username=username.strip()
			_password=password.strip()
			conn = None

			try:
				conn=pymssql.connect(host=host,user=_username,password=_password,database="*")
				print _info['vul_template_1'] % (host,_username,_password)
				_info['vul_res'].append([host,_username,_password])
				conn.close()
			except:
				pass

	return len(_info['vul_res'])

# 漏洞测试(存储测试结果，上传到安全平台)
def verify_save(host,port):
	pass
