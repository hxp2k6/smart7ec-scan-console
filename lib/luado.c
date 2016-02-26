#include  <stdio.h>
#include  "lua.h"
#include  "lualib.h"
#include  "lauxlib.h"

/*the lua interpreter*/
lua_State* L;

/**
 * lua脚本安全测试（只返回是否存在）
 * @param  filename [lua脚本路径和文件名称]
 * @param  host     [网站/ip地址]
 * @param  port     [端口]
 * @return          [1/0]
 */
int verify_lua(char* filename,char* host,int port)
{
    int res;
    // 初始化lua
    L = lua_open();
    // 加载lua基础库
    luaL_openlibs(L);
    // 加载lua脚本
    luaL_dofile(L, filename);

    // 加载lua测试脚本的信息函数(info)
    lua_getglobal(L,"info");
    lua_call(L, 0, 1);
    
    lua_getglobal(L,"msg");
    int t_idx = lua_gettop(L);

    if (t_idx > 0){
        lua_pushnil(L);
        while (lua_next(L,t_idx)!=0)
        {
            printf("[*] %s - %s\n",lua_tostring(L,-2),lua_tostring(L,-1));
            lua_pop(L,1);
        }
        /**
         * 漏洞测试使用，返回是否存在漏洞
         */
        lua_getglobal(L,"verify");
        lua_pushstring(L, host);
        lua_pushnumber(L, port);
        lua_call(L, 2, 1);
        res = (int)lua_tonumber(L, -1);
        lua_pop(L,1);
        res = 1;
    }else{
        res = 0;
    }

    lua_close(L);
    return res;

        // if (mode == 1){
        //         /**
        //          * 漏洞测试使用，返回是否存在漏洞
        //          */
        //         lua_getglobal(L,"verify");
        //         lua_pushstring(L, host);
        //         lua_pushnumber(L, port);
        //         lua_call(L, 2, 1);
        //         res = (int)lua_tonumber(L, -1);
        //         lua_pop(L,1);
        //         // 清理lua加载的资源
        //         lua_close(L);
        //         return res;
        // }else if (mode == 2){
        //         /**
        //          * 漏洞攻击测试，返回结果数据，并且打印出来
        //          */
        //         lua_getglobal(L,"exploit");
        //         lua_pushstring(L, host);
        //         lua_pushnumber(L, port);
        //         lua_call(L, 2, 1);
                
        //         lua_getglobal(L,"description");
        //         int t_idx = lua_gettop(L);
        //         if (t_idx > 0){
        //                 lua_pushnil(L);
        //                 while (lua_next(L,t_idx)!=0)
        //                 {
        //                         printf("%s - %s\n",lua_tostring(L,-2),lua_tostring(L,-1));
        //                         lua_pop(L,1);
        //                 }
        //                 res = 1;
        //         }else{
        //                 res = 0;
        //         }

        //         // 清理lua加载的资源
        //         lua_close(L);
        //         return res;
        // }
}

