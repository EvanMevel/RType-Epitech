
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