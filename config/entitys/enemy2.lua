
function loadEnemy2(factory)
    local enemy2 = registerEntityType(factory, "enemy2", 99, 96)
    enemy2:addComponent("TeamComponent", 1)
    enemy2:addComponent("HealthComponent", 50, 400)
    enemy2:addComponent("PhysicComponent")
    enemy2:addComponent("IAComponent")
    enemy2:addComponent("WeaponComponent", "weapon3")
end