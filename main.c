#include <stdio.h>
#include <dirent.h>
#include <getopt.h>

#include "include/luado.h"
#include "include/pubdo.h"
#include "include/strdo.h"
#include "include/pydo.h"

void str_help(void);
void str_list(void);
void find_module(char* scan_mode,char* find_modules);
void test_module(char* scan_mode,char* scan_modules);
void baseline_testing(void);

char* path[] = {"website","system","imploded","baseline"};

// 当前版本设定
char* version = "v1.0";

char *scan_mode, *find_modules, *scan_modules, *target;
int path_index;
struct dirent *direntp;
char * analyres;
int res;

char* const short_options = "hvltm:u:f:T:";
struct option long_options[] = {
   { "help", 0, NULL, 'h' },
   { "version", 0, NULL, 'v' },
   { "list", 0, NULL, 'l' },
   { "scan-mode", 1, NULL, 'm' },
   { "scan-modules", 1, NULL, 'u' },
   { "find", 1, NULL, 'f' },
   { "test", 0, NULL, 't' },
   { "baseline",1,NULL, 'b'},
   { "target", 1, NULL, 'T' },
   { 0, 0, 0, 0},
};

// 输出提示
void str_help(void)
{
	char help_msg[] =
		"Usage: Smart7ec-scan-console [OPTION] [...] \n"
		"  website,System or plugin scanner, you can choose a single,you can complete scanning, \n"
		"  tperform customized according to personal choice. \n"
		"\n"
		"  -h, --help           output this message\n"
		"  -m, --scan-mode      Set the scan type(website/system/imploded). \n"
		"  -u, --scan-modules   Set the scan module, a plurality of modules are ',' divided.\n"
		"  -v, --version        output version number.\n"
		"  -l, --lmoist           List all of the scanning module.\n"
		"  -f, --find           Search scanning module.\n"
		"  -t, --test           Test scan module is operating normally.\n"
		"  -b, --baseline       localhost configuration baseline testing.(Unix/Linux)\n"
		"  -T, --target         target for scanner.\n"
		"\n"
		"Report bugs to <tangyucong@163.com> \n";
	printf("%s", help_msg);
}

// 输出所有插件列表
void str_list(void)
{
	DIR *dirp;

	printf("[*] Loading Plugin List ...\n");

	for (path_index = 0; path_index < 4; path_index++)
	{
		char* this_path;
		// 路径尾部组合
		char* path_last = splice("plugins/",splice(path[path_index],"/"));
		// 全路径
		char* path_obj = splice(defpath(),path_last);

		dirp = opendir(path_obj);

		if(dirp != NULL)
		{
			while(1)
			{
				direntp = readdir(dirp);

				if(direntp == NULL){
					break;
				}else if(direntp->d_name[0] != '.'){
					printf("[*] Path: %s ,Plugin: %s \n",path[path_index],direntp->d_name);
				}
			}
			closedir(dirp);
		}	
    }
}

// 查找模块的名称
void find_module(char* scan_mode,char* find_modules)
{
	DIR *dirp;

	int find_status = 0;

	char* this_path;
	// 路径尾部组合
	char* path_last = splice("plugins/",splice(scan_mode,"/"));
	// 全路径
	char* path_obj = splice(defpath(),path_last);

	dirp = opendir(path_obj);

	if(dirp != NULL)
	{
		while(1)
		{
			direntp = readdir(dirp);

			if(direntp == NULL){
				break;
			}else if(direntp->d_name[0] != '.'){
				if (strcmp(direntp->d_name,find_modules) == 0){
					printf("[*] Find modules Path: %s ,Plugin: %s \n",path[path_index],direntp->d_name);
					find_status = find_status + 1;
				}
			}
		}
		if (find_status < 1){
			printf("[*] Can't not found this module.\n");
		}
		closedir(dirp);
	}
}

// 测试模块是否正常
void test_module(char* scan_mode,char* scan_modules)
{
	DIR *dirp;

	int find_status = 0;

	char* this_path;
	// 路径尾部组合
	char* path_last = splice("plugins/",splice(scan_mode,"/"));
	// 全路径
	char* path_obj = splice(defpath(),path_last);

	dirp = opendir(path_obj);

	char* modules[99];

	char* splitword = strtok(scan_modules, ",");

	int i = 0;
	int count = 0;

	while(splitword)
	{
		modules[i]=splitword;
		splitword=strtok(NULL, ",");
		i++;
		count++;
	}

	if(dirp != NULL)
	{
		while(1)
		{
			direntp = readdir(dirp);

			if(direntp == NULL){
				break;
			}else if(direntp->d_name[0] != '.'){

				if (count > 1){
					for (i=0; i<count; i++){
						if (strcmp(modules[i],direntp->d_name)==0)
						{
							analyres = (char*)analystr(direntp->d_name);
							// 脚本解析器
							if (strcmp(analyres,"lua")==0){
								this_path = splice(path_obj,direntp->d_name);
								verify_lua_test(this_path);
								find_status = find_status + 1;
							}else if (strcmp(analyres,"py")==0){
								verify_python_test(path_obj,direntp->d_name);
								find_status = find_status + 1;
							}
						}
					}
				}else if (count = 1){
					if (strcmp(modules[0],direntp->d_name)==0)
					{
						analyres = (char*)analystr(direntp->d_name);
						// 脚本解析器
						if (strcmp(analyres,"lua")==0){
							this_path = splice(path_obj,direntp->d_name);
							verify_lua_test(this_path);
							find_status = find_status + 1;
						}else if (strcmp(analyres,"py")==0){
							verify_python_test(path_obj,direntp->d_name);
							find_status = find_status + 1;
						}
					}
				}
			}
		}
		if (find_status < 1){
			printf("[*] Can't not found this module.\n");
		}
		closedir(dirp);
	}
}

// 扫描模式
// 1:web扫描
// 2:sys扫描
// 3:集成扫描
// void scanner_mode(int mode,char* scan_target)
// {
	// web扫描
	// 单纯针对80端口扫描
	// 1)先爬虫
	// 2)针对爬虫的结果进行扫描测试
	// 3)将结果存储
	// if (mode == 1)

	// sys扫描
	// 单纯针对所有的端口进行扫描
	// 1)端口扫描
	// 2)针对对应的端口进行漏洞测试
	// 3)将结果存储
	// if (mode == 2)

	// 集成扫描
	// 单纯的模块测试
	// 1)测试模块
	// 2)上传结果
	// if (mode == 3)

	// 全面扫描
	// 先进行系统扫描
	// 再进行web扫描
	// 最后进行集成插件扫描
	// if (mode == 4)
// }

void baseline_testing(void)
{
	// 设立基线计分机制
	float result;
	// 计算总执行模块数
	int count_modules = 0;
	// 计算存在风险的模块数
	int count_vul_modules = 0;
	char* this_path;
	// 路径尾部组合
	char* path_last = splice("plugins/",splice(path[4],"/"));
	// 全路径
	char* path_obj = splice(defpath(),path_last);

	dirp = opendir(path_obj);

	if(dirp != NULL)
	{
		while(1)
		{
			direntp = readdir(dirp);

			if(direntp == NULL){
				break;
			}else if(direntp->d_name[0] != '.'){
				analyres = (char*)analystr(direntp->d_name);

				// 脚本解析器
				if (strcmp(analyres,"py")==0){
					res=(int)verify_python_baseline(path_obj,direntp->d_name);
					count_modules++;
					if (res == 1){
						count_vul_modules++;
					}
				}
			}
		}
		closedir(dirp);
	}

	// 计算最后基线检查得分
	result = (float)count_vul_modules/count_modules*100;
	printf("[*] Baseline Testing Result: %.2f%%\n",result);
}


int main(int argc,char *argv[])
{
	int teststatus=0;

	int input;
	while((input = getopt_long (argc, argv, short_options, long_options, NULL)) != -1)
	{
		switch (input)
		{
			// 属于标准输出类函数
			case 'h':
				str_help();
				break;
			case 'v':
				printf("Smart7ec Scan Console %s\n",version);
				break;
			case 'l':
				str_list();
				break;
			// 属于定制函数
			case 'm':
				scan_mode = optarg;
				break;
			case 'f':
				find_modules = optarg;
				break;
			case 'u':
				scan_modules = optarg;
				break;
			case 't':
				teststatus = 1;
				break;
			case 'T':
				target = optarg;
				break;
			case 'b':
				baseline_testing();
			break;
		}

	}
	// 查找模块模式
	if (scan_mode != NULL && find_modules != NULL){
		find_module(scan_mode,find_modules);
	}
	// 测试模块模式
	if (scan_mode != NULL && scan_modules !=NULL && teststatus == 1){
		test_module(scan_mode,scan_modules);
	}
	// 执行扫描测试
    

	// for (path_index = 0; path_index < 3; path_index++)
	// {
	// 	char* this_path;
	// 	// 路径尾部组合
	// 	char* path_last = splice("plugins/",splice(path[path_index],"/"));
	// 	// 全路径
	// 	char* path_obj = splice(defpath(),path_last);

	// 	dirp = opendir(path_obj);

	// 	if(dirp != NULL)
	// 	{
	// 		while(1)
	// 		{
	// 			direntp = readdir(dirp);

	// 			if(direntp == NULL){
	// 				break;
	// 			}else if(direntp->d_name[0] != '.'){
	// 				analyres = (char*)analystr(direntp->d_name);

	// 				// 脚本解析器
	// 				if (strcmp(analyres,"lua")==0){
	// 					printf("[*] Lua work\n");
	// 					// this_path = splice(path_obj,direntp->d_name);
	// 					// printf("Lua loading: %s \n",this_path);
	// 					// res=(int)verify_lua(this_path,2,"127.0.0.1",80);
	// 					// printf("Testing Lua result: %d\n",res);
	// 				}else if (strcmp(analyres,"py")==0){
	// 					// printf("[*] Python plugin loading: %s \n",splice(path_obj,direntp->d_name));
	// 					res=(int)verify_python(path_obj,direntp->d_name,1,argv[1],21);
	// 					printf("[*] Testing Python result: %d\n",res);
	// 				}
	// 			}
	// 		}
	// 		closedir(dirp);
	// 	}	
 //    }
    return 0;
}
