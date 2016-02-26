#include <string.h>
#include <stdlib.h>

/**
 * 字符串合并
 * @param  str1 [description]
 * @param  str2 [description]
 * @return      [description]
 */
char* splice(char* str1, char* str2)
{
    char *result = malloc(strlen(str1)+strlen(str2)+1);
    if (result == NULL) exit (1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

/**
 * 获得文件后缀名
 * @param file_name [description]
 * @param extension [description]
 */
void interception(const char *file_name,char *extension)
{
    int i=0,length;
    length=strlen(file_name);
        while(file_name[i])
    {
        if(file_name[i]=='.')
        break;
        i++;
    }
    if(i<length)
    strcpy(extension,file_name+i+1);
    else
    strcpy(extension,"\0");
}

/**
 * 获得文件前缀名
 * @param  filename [description]
 * @return          [description]
 */
char* firstname(char * filename)
{
    char * name = strtok(filename,".");
    return name;
}
