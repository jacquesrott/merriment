local gz = require "assets/scripts/galaczy"

Player = {}

Player.__index = Player


function Player.create()
    local player = {}
    setmetatable(player, Player)
    return player
end


function Player:init()
    player.name = "Jaqk"
    player.life = 100
end


function Player:update()
end


function Player:finish()
    self.life = 0
end


instance = "player"
player = Player.create()
