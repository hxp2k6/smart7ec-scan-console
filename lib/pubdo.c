#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE (PATH_MAX+1)


/**
 * 分析后缀是否是指定的后缀
 * @param  filename [description]
 * @return          [1:true/0:false]
 */
char * analystr(char* filename)
{
	char * result = "NULL";
	char name[4];
	char * lasttypes[] = {"py","lua"};
	interception(filename,name);

	int type_index;

	for (type_index=0;type_index<2;type_index++){

		if (strcmp(name,lasttypes[type_index])==0){
			result = lasttypes[type_index];
		}
	}

	return result;
}

/**
 * 获取默认的路径
 * @return [description]
 */
char* defpath()
{
	static char current_absolute_path[MAX_SIZE];
	//获取当前程序绝对路径
	int cnt = readlink("/proc/self/exe", current_absolute_path, MAX_SIZE);
	if (cnt < 0 || cnt >= MAX_SIZE)
	{
	  printf("***Error***\n");
	  exit(-1);
	}
	//获取当前目录绝对路径，即去掉程序名
	int i;
	for (i = cnt; i >=0; --i)
	{
	  if (current_absolute_path[i] == '/')
	  {
	      current_absolute_path[i+1] = '\0';
	      break;
	  }
	}
	return current_absolute_path;
}
