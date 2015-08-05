# Merriment

Entity/Components based 2D engine written in C with embedded Lua scripts.

## Description

Engine written on my spare. Wanted to do a game, ended up doing an engine ... again. Hey, engines are fun.
Sometimes I come back and continue my journey, still have a lot of ideas to implement.

## Usage

Nothing much can be done so far, except loading scenes with scripts and program shaders.
You can run and load a scene :

```
scons -Q && ./bin/merriment
```

## Requirements

- Scons
- SDL2
- OpenGL (OS X only)
- chipmunk
- LuaJIT

- python2.7 (only require for the so called "editor")

## Scene example

```json
{
    "entities": [
        {
            "components": [
                [
                    "script",
                    {
                        "instance": {},
                        "path": "assets/scripts/player.lua"
                    }
                ],
                [
                    "transform",
                    {
                        "angle": 0.0,
                        "position": [
                            0.0,
                            0.0
                        ],
                        "scale": [
                            1.0,
                            1.0
                        ]
                    }
                ],
                [
                    "sprite",
                    {
                        "sprite": "assets/sprites/red_square.png",
                        "program": ["assets/shaders/vertex.vs", "assets/shaders/fragment.fs"]
                    }
                ]
            ],
            "name": "test"
        }
    ],
    "path": "scene.mp",
    "source": "scene.json"
}
```

Install the python requirements in `/editor/` and you can convert it to msgpack format with the following command :

```
python editor/compiler.py
```

## Why Merriment ?

```
mer•ri•ment (mĕrˈĭ-mənt)

    n.  High-spirited fun and enjoyment; hilarity.
```

It's jun for fun and for learning.

## Resources

- [Game Engine Architecture (1st Edition)](http://www.amazon.com/Game-Engine-Architecture-Jason-Gregory/dp/1568814135/). (2009). Florida: Jason Gregory
- [Game Programming Patterns](http://gameprogrammingpatterns.com/). (2014). Seattle: Robert Nystrom
