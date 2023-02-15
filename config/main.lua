

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
    registerEntityType(factory, "player", 100, 56, 100, 1000)
    registerEntityType(factory, "projectile", 81, 16, 1, 0)
end
