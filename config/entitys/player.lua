
function loadPlayer(factory)
    local player = registerEntityType(factory, "player", 132, 56)
    player:addComponent("TeamComponent", 0)
    player:addComponent("HealthComponent", 100, 1000)
    player:addComponent("PhysicComponent", 10)
    player:addComponent("WeaponComponent", "weapon1")
end