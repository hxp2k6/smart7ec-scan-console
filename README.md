# Smart7ec Scan Console

## 工具说明

基于linux c 开发的WEB扫描与系统扫描集合一身的扫描工具，它能利用lua和python插件进行快速的插件扩展，最大程度的提高漏洞扫描的综合能力。

## 功能介绍

    --1)Web层面扫描
	支持常规web扫描测试，用于新业务上线进行安全检测，巡检。
	-- (1) Web Spider
	-- (2) SQL inject
	-- (3) Cross Site Scripting(XSS)
	-- (4) File inclusion vulnerability（LFI/RFI）
	-- (5) Directory traversal attacks
	-- (6) XPath injection
	-- (7) Code execution

    --2)系统服务层面扫描
	支持常规的系统服务扫描测试，用于新上线业务系统安全检测。
	-- (1) Port Scanner 
	-- (2) FTP Service  [√]
		1) Anonymous Logon [√]
		2) Weak passwords  [√]
	-- (3) MSSQL Service  [√]
	-- (4) MYSQL Service  [√]
	-- (5) SSH Service  [√]
	-- (6) Telnet Service
	-- (7) HTTP Service Banner [√]
    
    --4)基线配置的安全扫描
        支持系统配置的安全检测，确保当前系统配置处于最优的安全状态。
	-- (1) Banner leakage
	-- (2) Home directory permissions
	-- (3) Sensitive documents
	-- (4) Logon check
	-- (5) Set up automatic logout
	-- (6) Mysql service configuration
	-- (7) Nginx service configuration
	-- (8) Garbage clean-up users
	-- (9) Php service configuration
	-- (10) Port status
	-- (11) passwd & shadow permissions
	-- (12) Ssh service configuration
	-- (13) System log access restrictions
	-- (14) Vsftp service configuration

    --5)集成插件扫描
	支持多钟扫描插件，可以根据自己的需求弹性扩展，插件类型不做过多限制。
	＊ 支持python插件。
	＊ 支持lua插件。

## 程序命令执行

    Usage: Smart7ec-scan-console [OPTION] [...] 
    website,System or plugin scanner, you can choose a single, 
    you can complete scanning, perform customized according to personal choice. 

    -h, --help           output this message
    -m, --Scan-mode      Set the scan type(website/system/imploded/baseline). 
    -u, --Scan-modules   Set the scan module, a plurality of modules are ',' divided.
    -v, --version        output version number.
    -l, --list           List all of the scanning module.
    -f, --find           Search scanning module.
    -t, --test           Test scan module is operating normally.

    Report bugs to <tangyucong@163.com> 

## 编译使用

    make
    ./Smart7ec-scan-console

## 程序依赖
   
    * python2.7
    * pycrypto2.6
    * ftplib
    * mysqldb
    * paramiko-1.7.7.1
    * ecdsa-0.10
    * pymssql

## 待实现

    1) 有些功能还没实现，比如多进程调用模块。
    2) 端口扫描联动系统模块调用。
