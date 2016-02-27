#coding:utf-8

import re
import commands

# 测试脚本输出信息
def info():
	msg = {
		# 测试用例名称
		"name" : "Home directory permissions",
		# 测试用例针对应用版本
		"version" : "all",
		# 测试用例描述
		"desc" : '''
			测试home目录的权限。
		''',
		# 解决建议
		"proposed": '''
			修改目录权限，或删除停用该用户。
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
		"vul_template_1": "[*] Found username: %s ,compet: %s ,home_directory: %s !!",
		# 扫描漏洞结果
		"vul_res": []
	}
	return msg

# 漏洞测试(不存储结果，直接输出，返回状态给主程序)
def verify_print(host,port):
	_info = info()

	status = 0

	obj_pw=open("/etc/passwd","r")
	for line in obj_pw:
		try:
			directory_name=line.strip("\n").split(":")[-2]
			user_name=line.strip("\n").split(":")[0]
			_text=commands.getstatusoutput(str(directory_name))
			if re.match("^ls",_text):
				pass
			else:
				directory_compet=_text.split(" ")[0]
				if not re.match("^drwxr-x---",directory_compet):
					print _info['vul_template_1'] % (user_name,directory_compet,directory_name)
					status = 1
		except:
			pass
	obj_pw.close()

	return status

# 漏洞测试(存储测试结果，上传到安全平台)
def verify_save(host,port):
	pass
