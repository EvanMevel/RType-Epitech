
function loadHardLevel(factory)
    local hardLevel = createLevel(factory, "Hard Level");
    hardLevel:addObject("enemy1", 0, 450)
    hardLevel:addObject("enemy1", 0, 550)
    hardLevel:addObject("enemy2", 750, 100)
    hardLevel:addObject("obstacle1", 50, 100)
    hardLevel:addObject("enemy1", 2050, 550)
    hardLevel:addObject("enemy1", 2050, 150)
    hardLevel:addObject("enemy2", 1800, 800)
    hardLevel:addObject("obstacle1", 1350, 550)
    hardLevel:addObject("obstacle1", 1350, 150)
    hardLevel:addObject("weapon5", 0, 720)
    hardLevel:addObject("BOSS", 2600, 250)
end