local msgpack = require "assets/scripts/msgpack"

function serialize(instance)
    compiled = msgpack.pack(instance)
    return compiled
end


function deserialize(instance, compiled)
    decompiled = msgpack.unpack(compiled)
    for k, v in pairs(decompiled) do
        instance[k] = v
    end
end
