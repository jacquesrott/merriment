import msgpack
import json
import os
import time

from editor.compiler import init, finish, map_types, EDITOR_PATH, SCENES_PATH, COMPONENT_TYPES

COMPONENT_TYPES = {v: k for k, v in COMPONENT_TYPES.items()}


if __name__ == "__main__":
    scenes = init(SCENES_PATH)
    start = time.time()

    for path in scenes:
        full_path = os.path.join(SCENES_PATH, path)
        print "start    %s" % full_path

        with open(full_path, "r+b") as compiled:
            mp_scene = compiled.read()

        print "unpack   %s" % full_path
        scene = msgpack.unpackb(mp_scene)

        map_types(scene['entities'], COMPONENT_TYPES)

        full_source = os.path.join(EDITOR_PATH, scene["source"])

        print "write    %s" % full_source
        with open(full_source, "w") as decompiled:
            json.dump(scene, decompiled, sort_keys=True, indent=4, separators=(',', ': '))
        print "-" * 4
    end = time.time()
    finish(start, end, len(scenes), "de")
