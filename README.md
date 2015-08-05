# Merriment

Entity/Components based 2D engine written in C with embedded Lua scripts.

## Description

Engine written on my spare time. I wanted to do a game, ended up doing an engine ... again. Hey, engines are fun.

## Usage

It is currently possible to load scenes with scripts and program shaders.
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
- python2.7 (only required for the so-called "editor")

## Editor

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

Install the python requirements from `/editor/requirements.txt` with

```
pip install -r editor/requirements.txt
```

It is possible to convert a json scene to msgpack format with the following command :

```
python editor/compiler.py
```

To unpack a scene :

```
python editor/decompiler.py
```

By default, `compiler` and `decompiler` will run through all the files of `assets/editor/` or `assets/scenes/`.
In order to (de)compile only one file, the usage would be :

```
python editor/decompiler.py MSGPACK_FILE_PATH
```

or

```
python editor/compiler.py JSON_FILE_PATH
```

#### Hot reload

If you have already a running application, it is possible to hotreload a scene by pressing `BACKSPACE`.

## Why Merriment ?

```
mer•ri•ment (mĕrˈĭ-mənt)

    n.  High-spirited fun and enjoyment; hilarity.
```

It's jun for fun and for learning.

## Resources

- [Game Engine Architecture (1st Edition)](http://www.amazon.com/Game-Engine-Architecture-Jason-Gregory/dp/1568814135/). (2009). Florida: Jason Gregory
- [Game Programming Patterns](http://gameprogrammingpatterns.com/). (2014). Seattle: Robert Nystrom
