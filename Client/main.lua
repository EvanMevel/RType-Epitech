-- define Lua function --
function MyLuaFunction(num, str)
    print("Hello from Lua!")
    print("num = "..tostring(num)..", str = "..str)
end

function TestLua(num)
    ret = cAdd(num, 5);
    return ret
end