import msgpack
import json
import os
import time
import sys

from editor.compiler import init, finish, map_types, EDITOR_PATH, SCENES_PATH, COMPONENT_TYPES

COMPONENT_TYPES = {v: k for k, v in COMPONENT_TYPES.items()}

def instance_unpack(scene):
    for entity in scene["entities"]:
        for component in entity["components"]:
            if component[0] == "script":
                script = component[1]
                script["instance"] = msgpack.unpackb(script["instance"])


if __name__ == "__main__":
    scenes = sys.argv[1:]

    if not scenes:
        scenes = init(SCENES_PATH)
    start = time.time()

    for path in scenes:
        print "start    %s" % path

        with open(path, "r+b") as compiled:
            mp_scene = compiled.read()

        print "unpack   %s" % path
        scene = msgpack.unpackb(mp_scene)

        map_types(scene['entities'], COMPONENT_TYPES)

        if "source" in scene:
            full_source = os.path.join(EDITOR_PATH, scene["source"])
        else:
            full_source = os.path.splitext(path)[0]
            full_source += ".json"
            scene["source"] = os.path.basename(full_source)
        instance_unpack(scene)

        print "write    %s" % full_source
        with open(full_source, "w") as decompiled:
            json.dump(scene, decompiled, sort_keys=True, indent=4, separators=(',', ': '))
        print "-" * 4
    end = time.time()
    finish(start, end, len(scenes), "de")
