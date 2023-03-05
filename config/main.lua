

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


function loadEntityTypes(factory)
    loadPlayer(factory)

    loadProjectiles(factory)

    loadEnemy1(factory)

    loadEnemy2(factory)

    loadWeapon1(factory)

    loadWeapon5(factory)

    loadObstacles(factory)

end

function loadLevels(factory)
    loadEasyLevel(factory)
    loadMediumLevel(factory)
    loadHardLevel(factory)
    loadImpossibleLevel(factory)
end
