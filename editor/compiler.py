import msgpack
import json
import os


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


if __name__ == "__main__":
    scenes = [file for file in os.listdir(EDITOR_PATH)
              if os.path.isfile(os.path.join(EDITOR_PATH, file))]

    for path in scenes:
        full_path = os.path.join(EDITOR_PATH, path)

        print "%s\tstart" % full_path
        with open(full_path, "r+") as decompiled:
            scene = json.load(decompiled)

        print "%s\tloaded" % full_path

        for entity in scene["entities"]:
            for component in entity["components"]:
                component["type"] = COMPONENT_TYPES.get(component["type"], COMPONENT_TYPES['script'])
        mp_scene = msgpack.packb(scene)
        print "%s\tpacked" % full_path

        destination = os.path.join(SCENES_PATH, scene["path"])
        with open(destination, "w+b") as compiled:
            compiled.write(mp_scene)

        print "%s\twritten" % destination
        print "-" * 4

    print "%s files compiled" % len(scenes)