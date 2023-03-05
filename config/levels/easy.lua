
function loadEasyLevel(factory)
    local easyLevel = createLevel(factory, "Easy Level",2220)
    easyLevel:addObject("enemy1", 0, 450)
    easyLevel:addObject("enemy1", 0, 550)
    easyLevel:addObject("enemy2", 250, 100)
end