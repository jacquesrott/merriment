local ffi = require 'ffi'
local cmsgpack = require "cmsgpack"

gz = setmetatable({}, {__index = ffi.C})

gz.string = ffi.string


function serialize(instance)
    return cmsgpack.pack(instance)
end


function deserialize(instance, compiled)
    instance = cmsgpack.unpack(compiled)
end
