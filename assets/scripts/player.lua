local gz = require "assets/scripts/galaczy"

Player = {}

Player.__index = Player


function Player.create()
    local player = {}
    setmetatable(player, Player)

    player.name = "Jaqk"
    player.life = 0

    return player
end


function Player:init()
    self.life = 100
end


function Player:update()
    -- print(self.name)
    -- print(self.life)
end


function Player:finish()
    self.life = 0
end


instance = "player"
player = Player.create()
