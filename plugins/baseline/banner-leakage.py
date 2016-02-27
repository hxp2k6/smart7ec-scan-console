#coding:utf-8

import re,os

# 测试脚本输出信息
def info():
	msg = {
		# 测试用例名称
		"name" : "Banner leakage",
		# 测试用例针对应用版本
		"version" : "all",
		# 测试用例描述
		"desc" : '''
			测试是否存在系统信息泄露的问题。
		''',
		# 解决建议
		"proposed": '''
			修改指纹信息。
		''',
		# 测试用例开发者
		"author" : "Smarttang",
		# 测试用例应用范围
		"type" : "config",
		# 测试用例产出风险危害等级 high,medium,low
		"severity" : "high",
		# 测试用例开发时间
		"create_date" : "2016-2-27",
		# 测试用例最后更新时间
		"update_date" : "2016-2-27",
		# 漏洞输出模版(多个模版按照序号排列)
		"vul_template_1": "[*] Found %s: %s !!",
		# 扫描漏洞结果
		"vul_res": []
	}
	return msg

# 漏洞测试(不存储结果，直接输出，返回状态给主程序)
def verify_print(host,port):
	_info = info()

	check_dict = {
		'issus': [
			"/etc/issue",
			"/etc/issue.net.bak"
		]
	}

	status = 0
	sorce = 10
	tmp_list=[]
	try:
		if os.path.exists("/etc/rc.d/rc.local"):
			obj_r=open("/etc/rc.d/rc.local","r")
			for line in obj_r:
				if re.match("^echo",line):
					sorce=sorce-1
					tmp_list.append(line)
			if sorce<10:
				print _info['vul_template_1'] % ("Banner",str(tmp_list))
				status = 1
			obj_r.close()

		for check_item in check_dict['issue']:
			if os.path.exists(check_item):
				print _info['vul_template_1'] % ("Issue",check_item)
				status = 1
	except:
		pass

	return status

# 漏洞测试(存储测试结果，上传到安全平台)
def verify_save(host,port):
	pass
