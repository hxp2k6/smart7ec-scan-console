#coding:utf-8

import ftplib

# 测试脚本输出信息
def info():
	msg = {
		# 测试用例名称
		"name" : "FTP Service Attack",
		# 测试用例针对应用版本
		"version" : "all",
		# 测试用例描述
		"desc" : '''
			用于测试 FTP 弱口令。
		''',
		# 解决建议
		"proposed": '''
			1、检查ftp配置，确保禁止非口令授权模式关闭。
			2、检查ftp帐号密码设置，是否合理。
			3、如果不需要该服务，则禁止该服务。
		''',
		# 测试用例开发者
		"author" : "Smarttang",
		# 测试用例应用范围
		"type" : "service",
		# 测试用例产出风险危害等级 high,medium,low
		"severity" : "high",
		# 测试用例开发时间
		"create_date" : "2016-2-13",
		# 测试用例最后更新时间
		"update_date" : "2016-2-13",
		# 漏洞输出模版(多个模版按照序号排列)
		"vul_template_1": "[*] FTP Weak passwords Host: %s Username: %s Password: %s",
		"vul_template_2": "[*] FTP Anonymous Logon Successful Host: %s !!",
		# 扫描漏洞结果
		"vul_res": []
	}
	return msg

# 漏洞测试(不存储结果，直接输出，返回状态给主程序)
def verify_print(host,port):
	_info = info()

	# 先测试匿名登陆
	try:
		ftp=ftplib.FTP()
		ftp.connect(host,port,5)
		ftp.login()
		ftp.quit()
		print _info['vul_template_2'] % host
		_info['vul_res'].append([host,"Anonymous","Anonymous"])
	except ftplib.all_errors:
		pass

	# 字典爆破测试
	for username in open("dic/ftp_user.dic"):
		for password in open("dic/ftp_pass.dic"):
			_username=username.strip()
			_password=password.strip()
			
			try:
				ftp=ftplib.FTP()
				ftp.connect(host,port,5)
				ftp.login(_username,_password)
				ftp.quit()
				print _info['vul_template_2'] % host
				_info['vul_res'].append([host,_username,_password])
			except ftplib.all_errors:
				pass

	return len(_info['vul_res'])

# 漏洞测试(存储测试结果，上传到安全平台)
def verify_save(host,port):
	pass
