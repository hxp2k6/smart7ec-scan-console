#include <Python.h>
#include <stdio.h>

/**
 * 获得当前python插件的绝对路径
 * @param  path [插件目录]
 * @return      [description]
 */
char* pyfile_path(char* path)
{
	char* srcfilepath = (char *)splice(splice("sys.path.append('",path),"')");
	return srcfilepath;
}

/**
 * 读取字典里面的值(并转换为字符串)
 * @param  pValue [python返回的字典]
 * @param  str    [需要读取的字典主键]
 * @return        [description]
 */
char* getDictString(PyObject* pValue,char* str)
{
	char * res = PyString_AsString(PyDict_GetItemString(pValue,str));
	return res;
}

/**
 * 单纯测试模块，输出模块信息
 * @param  filepath [description]
 * @param  filename [description]
 * @param  mode     [description]
 * @param  host     [description]
 * @param  port     [description]
 * @return          [description]
 */
void verify_python_test(char* filepath,char* filename)
{
	// 初始化python环境
	Py_Initialize();
	
	PyObject *pModule,*pFunc,*pValue;

	PyRun_SimpleString("import os,sys");
	PyRun_SimpleString(pyfile_path(filepath));

	pModule = PyImport_Import(PyString_FromString((char*)firstname(filename)));

	// 加载信息定义模块
	pFunc = PyObject_GetAttrString(pModule, "info");
	pValue = PyEval_CallObject(pFunc, NULL);

	// 输出模块相关的信息
	printf("[*] Loading module name: %s \n", getDictString(pValue,"name"));
	printf("[*] Module Author: %s \n",getDictString(pValue,"author"));
	printf("[*] Module severity: %s \n", getDictString(pValue,"severity"));
	printf("[*] Module description: %s \n", getDictString(pValue,"desc"));
	printf("[*] Module proposed: %s \n", getDictString(pValue,"proposed"));
	printf("[*] Module testing type: %s \n", getDictString(pValue,"type"));
	printf("[*] Module testing version: %s \n",getDictString(pValue,"version"));
	printf("[*] Module create date: %s ,last update date: %s \n",getDictString(pValue,"create_date"),getDictString(pValue,"update_date"));

	Py_CLEAR(pValue);
	Py_CLEAR(pFunc);

}

/**
 * 纯基线安全测试的执行(仅用于基线安全测试)
 * @param  filepath [description]
 * @param  filename [description]
 * @return          [description]
 */
int verify_python_baseline(char* filepath,char* filename)
{
	int res;
	// 初始化python环境
	Py_Initialize();
	PyObject *pModule,*pFunc,*pValue;

	PyRun_SimpleString("import os,sys");
	PyRun_SimpleString(pyfile_path(filepath));

	pModule = PyImport_Import(PyString_FromString((char*)firstname(filename)));

	// 加载信息定义模块
	pFunc = PyObject_GetAttrString(pModule, "info");
	pValue = PyEval_CallObject(pFunc, NULL);

	// 输出模块相关的信息
	printf("[*] Loading module name: %s \n", getDictString(pValue,"name"));
	printf("[*] Module severity: %s \n", getDictString(pValue,"severity"));
	printf("[*] Module create date: %s ,last update date: %s \n",getDictString(pValue,"create_date"),getDictString(pValue,"update_date"));

	Py_CLEAR(pValue);
	Py_CLEAR(pFunc);

	pFunc = PyObject_GetAttrString(pModule,"verify_print");
	pValue = PyEval_CallObject(pFunc, NULL);
	res = PyInt_AsLong(pValue);
	Py_Finalize();

	Py_CLEAR(pFunc);
	Py_CLEAR(pValue);

	return res;
}

/**
 * 执行python插件的安全测试
 * @param  filepath [插件搜索路径]
 * @param  filename [插件名称]
 * @param  mode     [插件执行模式｜1:测试｜2:攻击]
 * @param  host     [攻击地址]
 * @param  port     [端口]
 * @return          [description]
 */
int verify_python(char* filepath,char* filename,int mode,char* host,int port)
{
	int res;
	// 初始化python环境
	Py_Initialize();
	PyObject *pModule,*pFunc;
	PyObject *pArgs, *pValue;
	PyRun_SimpleString("import os,sys");
	PyRun_SimpleString(pyfile_path(filepath));

	pModule = PyImport_Import(PyString_FromString((char*)firstname(filename)));

	// 加载信息定义模块
	pFunc = PyObject_GetAttrString(pModule, "info");
	pValue = PyEval_CallObject(pFunc, NULL);

	// 输出模块相关的信息
	printf("[*] Loading module name: %s \n", getDictString(pValue,"name"));
	printf("[*] Module severity: %s \n", getDictString(pValue,"severity"));
	printf("[*] Module create date: %s ,last update date: %s \n",getDictString(pValue,"create_date"),getDictString(pValue,"update_date"));

	Py_CLEAR(pValue);
	Py_CLEAR(pFunc);

	if (mode == 1){
		// 现场输出模块
		pFunc = PyObject_GetAttrString(pModule,"verify_print");
		pArgs = PyTuple_New(2);
		PyTuple_SetItem(pArgs,0, PyString_FromString(host));
		PyTuple_SetItem(pArgs,1, PyInt_FromLong(port));
		pValue = PyObject_CallObject(pFunc, pArgs);
		res = PyInt_AsLong(pValue);
		Py_Finalize();

	}else if (mode == 2){
		// 执行漏洞测试后，存储漏洞测试结果
		pFunc = PyObject_GetAttrString(pModule,"verify_save");
		pArgs = PyTuple_New(2);
		PyTuple_SetItem(pArgs,0, PyString_FromString(host));
		PyTuple_SetItem(pArgs,1, PyInt_FromLong(port));
		pValue = PyObject_CallObject(pFunc, pArgs);

		// 存储功能未实现 ------------- Mark
		Py_Finalize();
	}
	Py_CLEAR(pFunc);
	Py_CLEAR(pArgs);
	Py_CLEAR(pValue);

	return res;
}

