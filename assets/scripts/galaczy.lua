local ffi = require 'ffi'

gz = setmetatable({}, {__index = ffi.C})

gz.string = ffi.string
