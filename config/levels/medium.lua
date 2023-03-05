
function loadMediumLevel(factory)
    local mediumLevel =  createLevel(factory, "Medium Level", 4200)
    mediumLevel:addObject("enemy1", 0, 450)
    mediumLevel:addObject("enemy1", 0, 650)
    mediumLevel:addObject("enemy2", 750, 100)
    mediumLevel:addObject("obstacle1", 50, 100)
    mediumLevel:addObject("enemy1", 2050, 550)
    mediumLevel:addObject("enemy1", 2050, 150)
    mediumLevel:addObject("enemy2", 1800, 800)
    mediumLevel:addObject("obstacle1", 1350, 550)
    mediumLevel:addObject("obstacle1", 1350, 150)
end