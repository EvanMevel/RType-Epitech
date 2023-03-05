
function loadObstacles(factory)
    local obstacle1 = registerEntityType(factory, "obstacle1", 200, 117)
    obstacle1:addComponent("PhysicComponent")
    obstacle1:addComponent("InanimateComponent")
end