import msgpack
import json
import os
import time
import sys


SCENES_PATH = "assets/scenes/"
EDITOR_PATH = "assets/editor/"

COMPONENT_TYPES = {
    "camera": 1 << 0,
    "physic": 1 << 1,
    "transform": 1 << 2,
    "sprite": 1 << 3,
    "mesh": 1 << 4,
    "script": 1 << 5
}

def init(path):
    return [os.path.join(path, file) for file in os.listdir(path)
            if os.path.isfile(os.path.join(path, file))]

def finish(start, end, count, action=""):
    delta = end - start
    velocity = delta / count
    print "%s files %scompiled in %.4f s - %.4f s/file" % (count, action, delta, velocity)


def instance_pack(scene):
    for entity in scene["entities"]:
        for component in entity["components"]:
            if component[0] == "script":
                script = component[1]
                script["instance"] = msgpack.packb(script["instance"])


def map_types(entities, types):
    for entity in entities:
        for component in entity["components"]:
            component[0] = types.get(component[0])


if __name__ == "__main__":
    scenes = sys.argv[1:]

    if not scenes:
        scenes = init(EDITOR_PATH)
    start = time.time()

    for path in scenes:
        print "start    %s" % path
        with open(path, "r+") as decompiled:
            scene = json.load(decompiled)

        print "pack     %s" % path
        instance_pack(scene)
        map_types(scene['entities'], COMPONENT_TYPES)
        mp_scene = msgpack.packb(scene)

        destination = os.path.join(SCENES_PATH, scene["path"])
        print "write    %s" % destination
        with open(destination, "w+b") as compiled:
            compiled.write(mp_scene)

        print "-" * 4
    end = time.time()
    finish(start, end, len(scenes))
