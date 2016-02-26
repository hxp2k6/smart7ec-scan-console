#coding:utf-8

import urllib2,re

# 测试脚本输出信息
def info():
	msg = {
		# 测试用例名称
		"name" : "Http Service Banner",
		# 测试用例针对应用版本
		"version" : "all",
		# 测试用例描述
		"desc" : '''
			获得服务指纹。
		''',
		# 解决建议
		"proposed": '''
			NULL
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
		"vul_template_1": "[*] Service Banner Host: %s Port: %s Banner: %s",
		# 扫描漏洞结果
		"vul_res": []
	}
	return msg

# 漏洞测试(不存储结果，直接输出，返回状态给主程序)
def verify_print(host,port):
	_info = info()

	try:
		if re.match("^http://",host):
			req=urllib2.urlopen(host+":"+port)
		else:
			req=urllib2.urlopen("http://"+host+":"+port)
		
		banner=req.info().dict['server']
		print _info['vul_template_1'] % (host,port,banner)
		_info['vul_res'].append([host,port,banner])
	except:
		pass

	return len(_info['vul_res'])

# 漏洞测试(存储测试结果，上传到安全平台)
def verify_save(host,port):
	pass
