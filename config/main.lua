

function loadEntitySprites(graphicLib)
    playerSpriteSheet = createSpriteSheet(graphicLib, "r-typesheet42.gif")

    registerSprite(graphicLib, playerSpriteSheet, "player1", 0, 3, 33, 14, 5, 0, 30, 4.0)
    registerSprite(graphicLib, playerSpriteSheet, "player2", 0, 20, 33, 14, 5, 0, 30, 4.0)
    registerSprite(graphicLib, playerSpriteSheet, "player3", 0, 37, 33, 14, 5, 0, 30, 4.0)
    registerSprite(graphicLib, playerSpriteSheet, "player4", 0, 54, 33, 14, 5, 0, 30, 4.0)

    projectileSpriteSheet = createSpriteSheet(graphicLib, "r-typesheet1.gif")

    registerSprite(graphicLib, projectileSpriteSheet, "projectile1", 103, 170, 81, 16, 2, 0, 30, 1.0)
    registerSprite(graphicLib, projectileSpriteSheet, "projectile2", 267, 170, 81, 16, 2, 0, 30, 1.0)

    enemySpriteSheet = createSpriteSheet(graphicLib, "r-typesheet23.gif")

    registerSprite(graphicLib, enemySpriteSheet, "enemy1", 0, 6, 33, 22, 8, 0, 30, 3.0)

    enemySpriteSheet2 = createSpriteSheet(graphicLib, "r-typesheet7.gif")

    registerSprite(graphicLib, enemySpriteSheet2, "enemy2", 1, 34, 33, 32, 3, 0, 30, 3.0)
end

function loadEntityTypes(factory)
    registerEntityType(factory, "player", 100, 56)
    addComponentToType(factory, "player", "TeamComponent", 0)
    addComponentToType(factory, "player", "HealthComponent", 100, 1000)
    addComponentToType(factory, "player", "PhysicComponent", 10)

    registerEntityType(factory, "projectile", 81, 16)
    addComponentToType(factory, "projectile", "PhysicComponent", 0, 1, 0)

    registerEntityType(factory, "enemy1", 99, 66)
    addComponentToType(factory, "enemy1", "TeamComponent", 1)
    addComponentToType(factory, "enemy1", "HealthComponent", 50, 400)
    addComponentToType(factory, "enemy1", "CooldownComponent", math.floor(ENGINE_TPS * 2))
    addComponentToType(factory, "enemy1", "PhysicComponent")
    addComponentToType(factory, "enemy1", "IAComponent")


    registerEntityType(factory, "enemy2", 99, 96)
    addComponentToType(factory, "enemy2", "TeamComponent", 1)
    addComponentToType(factory, "enemy2", "HealthComponent", 50, 400)
    addComponentToType(factory, "enemy2", "CooldownComponent", math.floor(ENGINE_TPS * 1.2))
    addComponentToType(factory, "enemy2", "PhysicComponent")
    addComponentToType(factory, "enemy2", "IAComponent")
end
