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
	-- (2) MSSQL Service
	-- (3) MYSQL Service
	-- (4) SSH Service
	-- (5) Telnet Service

    --3)集成插件扫描
	支持多钟扫描插件，可以根据自己的需求弹性扩展，插件类型不做过多限制。
	＊ 支持python插件。
	＊ 支持lua插件。

