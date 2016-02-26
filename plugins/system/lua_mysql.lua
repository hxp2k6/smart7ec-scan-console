local mysql = require("luasql.mysql")

-- 测试脚本的信息输出
function info()
    local msg = {
        -- 测试用例名称
        name = "MySql 弱口令测试",
        -- 测试用例针对应用版本
        version = "all",
        -- 测试用例描述
        desc = [[
            用于测试 MYSQL 服务是否存在弱口令。
        ]],
        -- 测试用例开发者
        author = "Smarttang",
        -- 测试用例应用范围
        type = "service",
        -- 测试用例产出风险危害等级 high,medium,low
        severity = "high",
        -- 测试用例开发时间
        create_date = "2016-2-11",
        -- 测试用例最后更新时间
        update_date = "2016-2-11"
    }
    return msg
end

-- 执行测试（验证是否存在风险，返回测试结果）
function verify(host,port)
    local env = assert(mysql.mysql())
    for u in io.lines("dic/mysql_user.dic") do
        for p in io.lines("dic/mysql_pass.dic") do
            print("username:",u,"password",p)
            local conn = env:connect("",u,p,host)
            if not conn then
                    print("mysql error")
            else
                    print("mysql yes")
            end
        end
    end
    conn:close()
    env:close()
    return 1
end
