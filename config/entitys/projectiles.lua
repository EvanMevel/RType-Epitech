
function loadProjectiles(factory)
    local projectile = registerEntityType(factory, "projectile1", 81, 16)
    projectile:addComponent("PhysicComponent", 0, 1, 0)

    local projectile2 = registerEntityType(factory, "projectile2", 81, 16)
    projectile2:addComponent("PhysicComponent", 0, 1, 0)

    local projectile3 = registerEntityType(factory, "projectile3", 18 * 3, 12 * 3)
    projectile3:addComponent("PhysicComponent", 0, 1, 0)
end