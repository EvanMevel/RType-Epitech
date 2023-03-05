

function loadTextures(graphicLib)
    registerTexture(graphicLib, "obstacle1", "asteroide.png")
    registerTexture(graphicLib, "weapon1", "stronger_pistol.png")
    registerTexture(graphicLib, "weapon5", "pistol.png")
end

function loadEntitySprites(graphicLib)
    playerSpriteSheet = createSpriteSheet(graphicLib, "r-typesheet42.gif")

    registerSprite(graphicLib, playerSpriteSheet, "player1", 0, 3, 33, 14, 5, 0, 30, 4.0)
    registerSprite(graphicLib, playerSpriteSheet, "player2", 0, 20, 33, 14, 5, 0, 30, 4.0)
    registerSprite(graphicLib, playerSpriteSheet, "player3", 0, 37, 33, 14, 5, 0, 30, 4.0)
    registerSprite(graphicLib, playerSpriteSheet, "player4", 0, 54, 33, 14, 5, 0, 30, 4.0)

    projectileSpriteSheet = createSpriteSheet(graphicLib, "r-typesheet1.gif")

    registerSprite(graphicLib, projectileSpriteSheet, "projectile1", 103, 170, 81, 16, 2, 0, 30, 1.0)
    registerSprite(graphicLib, projectileSpriteSheet, "projectile2", 267, 170, 81, 16, 2, 0, 30, 1.0)
    registerSprite(graphicLib, projectileSpriteSheet, "projectile3", 204, 276, 18, 12, 7, 0, 30, 3.0)

    enemySpriteSheet = createSpriteSheet(graphicLib, "r-typesheet23.gif")

    registerSprite(graphicLib, enemySpriteSheet, "enemy1", 0, 6, 33, 22, 8, 0, 30, 3.0)

    enemySpriteSheet2 = createSpriteSheet(graphicLib, "r-typesheet7.gif")

    registerSprite(graphicLib, enemySpriteSheet2, "enemy2", 1, 34, 33, 32, 3, 0, 30, 3.0)
end

function loadPlayer(factory)
    local player = registerEntityType(factory, "player", 132, 56)
    player:addComponent("TeamComponent", 0)
    player:addComponent("HealthComponent", 100, 1000)
    player:addComponent("PhysicComponent", 10)
    player:addComponent("WeaponComponent", "weapon1")
end

function loadProjectiles(factory)
    local projectile = registerEntityType(factory, "projectile1", 81, 16)
    projectile:addComponent("PhysicComponent", 0, 1, 0)

    local projectile2 = registerEntityType(factory, "projectile2", 81, 16)
    projectile2:addComponent("PhysicComponent", 0, 1, 0)

    local projectile3 = registerEntityType(factory, "projectile3", 18 * 3, 12 * 3)
    projectile3:addComponent("PhysicComponent", 0, 1, 0)
end

function loadEnemy1(factory)
    local enemy1 = registerEntityType(factory, "enemy1", 99, 66)
    enemy1:addComponent("TeamComponent", 1)
    enemy1:addComponent("HealthComponent", 50, 400)
    enemy1:addComponent("PhysicComponent")
    enemy1:addComponent("IAComponent")
    enemy1:addComponent("WeaponComponent", "weapon2")
end

function loadEnemy2(factory)
    local enemy2 = registerEntityType(factory, "enemy2", 99, 96)
    enemy2:addComponent("TeamComponent", 1)
    enemy2:addComponent("HealthComponent", 50, 400)
    enemy2:addComponent("PhysicComponent")
    enemy2:addComponent("IAComponent")
    enemy2:addComponent("WeaponComponent", "weapon3")
end

function loadWeapon1(factory)
    local weapon1 = registerEntityType(factory, "weapon1", 50, 50)
    weapon1:addComponent("IAComponent")
    weapon1:addComponent("CollectableComponent", "weapon", "weapon4")
    weapon1:addComponent("PhysicComponent")
end

function loadWeapon5(factory)
    local weapon5 = registerEntityType(factory, "weapon5", 50, 50)
    weapon5:addComponent("IAComponent")
    weapon5:addComponent("CollectableComponent", "weapon", "weapon5")
    weapon5:addComponent("PhysicComponent")
end

function loadEntityTypes(factory)

    loadPlayer(factory);

    loadProjectiles(factory);

    loadEnemy1(factory);

    loadEnemy2(factory);

    loadWeapon1(factory);

    loadWeapon5(factory);

    local obstacle1 = registerEntityType(factory, "obstacle1", 200, 117)
    obstacle1:addComponent("PhysicComponent")
    obstacle1:addComponent("InanimateComponent")

end

function loadWeapons(factory)
    registerWeapon(factory, "weapon1", "projectile1", ENGINE_TPS * 1, 10, 0)
    registerWeapon(factory, "weapon4", "projectile1", math.floor(ENGINE_TPS * 0.7), 10, 0)
    registerWeapon(factory, "weapon2", "projectile2", ENGINE_TPS * 2, -10, 0)
    registerWeapon(factory, "weapon3", "projectile3", ENGINE_TPS * 3, -5, -5)
    registerWeapon(factory, "weapon5", "projectile1", math.floor(ENGINE_TPS * 0.3), 10, 0)
end

function loadLevels(factory)

    local easyLevel = createLevel(factory, "Easy Level",2220)
    easyLevel:addObject("enemy1", 0, 450)
    easyLevel:addObject("enemy1", 0, 550)
    easyLevel:addObject("enemy2", 250, 100)

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
    hardLevel:addObject("weapon5", 0, 620)
    hardLevel:addObject("BOSS", 2600, 250)

    local impossibleLevel = createLevel(factory, "Impossible Level");
    impossibleLevel:addObject("enemy1", 0, 450)
    impossibleLevel:addObject("enemy1", 0, 650)
    impossibleLevel:addObject("enemy2", 750, 100)
    impossibleLevel:addObject("obstacle1", 50, 100)
    impossibleLevel:addObject("enemy1", 2050, 550)
    impossibleLevel:addObject("enemy1", 2050, 150)
    impossibleLevel:addObject("enemy2", 1800, 800)
    impossibleLevel:addObject("obstacle1", 1350, 550)
    impossibleLevel:addObject("obstacle1", 1350, 150)
    impossibleLevel:addObject("weapon1", 0, 620)
    impossibleLevel:addObject("BOSS", 4000, 250)
    impossibleLevel:addObject("enemy2", 4200, 800)
    impossibleLevel:addObject("enemy2", 4400, 680)
    impossibleLevel:addObject("enemy2", 4600, 480)
    impossibleLevel:addObject("enemy2", 4800, 540)
    impossibleLevel:addObject("enemy2", 5005, 240)
    impossibleLevel:addObject("enemy2", 5205, 800)
    impossibleLevel:addObject("enemy2", 5400, 680)
    impossibleLevel:addObject("enemy2", 5605, 480)
    impossibleLevel:addObject("enemy2", 5800, 540)
    impossibleLevel:addObject("enemy2", 6005, 240)
    impossibleLevel:addObject("enemy2", 6205, 800)
    impossibleLevel:addObject("enemy2", 6400, 680)
    impossibleLevel:addObject("enemy2", 6605, 480)
    impossibleLevel:addObject("enemy2", 6800, 540)
end
