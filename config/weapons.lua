
function loadWeapons(factory)
    registerWeapon(factory, "weapon1", "projectile1", ENGINE_TPS * 1, 10, 0)
    registerWeapon(factory, "weapon4", "projectile1", math.floor(ENGINE_TPS * 0.7), 10, 0)
    registerWeapon(factory, "weapon2", "projectile2", ENGINE_TPS * 2, -10, 0)
    registerWeapon(factory, "weapon3", "projectile3", ENGINE_TPS * 3, -5, -5)
    registerWeapon(factory, "weapon5", "projectile1", math.floor(ENGINE_TPS * 0.3), 10, 0)
end