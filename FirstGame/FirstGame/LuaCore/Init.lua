--require("Rooms.lua")

function Init()
    addSpriteSheets()
    createMap()
    createPlayer()
end

function Update()
    --local asd = Engine.Game.Player.getPositionComponent(Engine.Game.Player)
    --asd.setX(asd, asd.getX(asd) + 0)
end

function Destroy()
    
end

function createMap() 
    local tileMap = Engine.Game.TileMap
    addLayers(tileMap)
    createTiles(tileMap,"Floor",1,4,2,11,3,3)
    createRoom(tileMap,1,1,5,5,3,3,1,3)
    createRoom(tileMap,1,15,5,5,3,3,1,3)
end

function createRoom(tileMap,xPos, yPos, xSize, ySize, floorSpriteX, floorSpriteY, wallSpriteX, wallSpriteY)
    createTiles(tileMap,"Floor",xPos,yPos,xSize,ySize,floorSpriteX,floorSpriteY)
    createTiles(tileMap,"Wall",xPos-1,yPos-1,xSize+2,ySize+2,wallSpriteX,wallSpriteY)
end

function createTiles(tileMap,name,xPos, yPos, xSize, ySize, spriteX, spriteY)
    for x=xPos,xPos + xSize do 
        for y=yPos,yPos + ySize do 
            tileMap.createTileChar(tileMap, name, x, y, spriteX, spriteY)
        end
    end
end

function addSpriteSheets()
    Engine.AssetManager.addSpriteSheet("Player0", "Assets/sprites/Characters/Player0.png")
    Engine.AssetManager.addSpriteSheet("Pest0", "Assets/sprites/Characters/Pest0.png")
    Engine.AssetManager.addSpriteSheet("Floor", "Assets/sprites/Objects/Floor.png")
    Engine.AssetManager.addSpriteSheet("Wall", "Assets/sprites/Objects/Wall.png")
    Engine.AssetManager.addSpriteSheet("Pit0", "Assets/sprites/Objects/Pit0.png")
    Engine.AssetManager.addSpriteSheet("Pit1", "Assets/sprites/Objects/Pit1.png")
end

function addLayers(tileMap)
    tileMap.addLayerChar(tileMap, "Floor", false)
    tileMap.addLayerChar(tileMap, "Wall", true)
    tileMap.addLayerChar(tileMap, "Pit0", false)
    tileMap.addLayerChar(tileMap, "Pit1", false)
end

function createPlayer()
    local entityManager = Engine.Game.EntityManager
    local player = entityManager.createEntity(entityManager)
    --local player = Engine.Game.Player
    player.addComponent(player, 0)
    player.addComponent(player, 2)
    local playerSpriteSheet = Engine.AssetManager.getSpriteSheet("Player0")
    local playerSpriteComp = player.getSpriteComponent(player)
    playerSpriteComp.setSpriteSheet(playerSpriteComp, playerSpriteSheet, 2, 1)
    player.addComponent(player, 4)
    player.addComponent(player, 1)
    player.addComponent(player, 3)
    player.addGroup(player, "Sprite")

    --local asd = player.getPositionComponent(player)
    --asd.setX(asd, 32)
    --asd.setY(asd, 32)
    Engine.Game.Player = player
end