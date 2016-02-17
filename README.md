# Smart7ec Scan Console

## 工具说明

基于linux c 开发的WEB扫描与系统扫描集合一身的扫描工具，它能利用lua和python插件进行快速的插件扩展，最大程度的提高漏洞扫描的综合能力。

## 功能介绍

    --1)Web层面扫描
	支持常规web扫描测试，用于新业务上线进行安全检测，巡检。
	-- (1) SQL inject
	-- (2) Cross Site Scripting(XSS)
	-- (3) File inclusion vulnerability（LFI/RFI）
	-- (4) Directory traversal attacks
	-- (5) XPath injection
	-- (6) Code execution

    --2)系统服务层面扫描
	支持常规的系统服务扫描测试，用于新上线业务系统安全检测。
	-- (1) FTP Service  [√]
		1) Anonymous Logon [√]
		2) Weak passwords  [√]
	-- (2) MSSQL Service  [√]
	-- (3) MYSQL Service  [√]
	-- (4) SSH Service  [√]
	-- (5) Telnet Service
	-- (6) HTTP Service Banner [√]

    --3)集成插件扫描
	支持多钟扫描插件，可以根据自己的需求弹性扩展，插件类型不做过多限制。
	＊ 支持python插件。
	＊ 支持lua插件。

## 程序命令执行

    Usage: Smart7ec-scan-console [OPTION] [...] 
    website,System or plugin scanner, you can choose a single, 
    you can complete scanning, perform customized according to personal choice. 

    -h, --help           output this message
    -m, --Scan-mode      Set the scan type(website/system/imploded). 
    -u, --Scan-modules   Set the scan module, a plurality of modules are ',' divided.
    -v, --version        output version number.
    -l, --list           List all of the scanning module.
    -f, --find           Search scanning module.
    -t, --test           Test scan module is operating normally.

    Report bugs to <tangyucong@163.com> 

## 程序依赖
   
    * python2.7
    * pycrypto2.6
    * ftplib
    * mysqldb
    * paramiko-1.7.7.1
    * ecdsa-0.10
    * pymssql

