
function loadEnemy1(factory)
    local enemy1 = registerEntityType(factory, "enemy1", 99, 66)
    enemy1:addComponent("TeamComponent", 1)
    enemy1:addComponent("HealthComponent", 50, 400)
    enemy1:addComponent("PhysicComponent")
    enemy1:addComponent("IAComponent")
    enemy1:addComponent("WeaponComponent", "weapon2")
end