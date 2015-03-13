import msgpack
import json
import os

from editor.compiler import EDITOR_PATH, SCENES_PATH, COMPONENT_TYPES

COMPONENT_TYPES = {v: k for k, v in COMPONENT_TYPES.items()}


if __name__ == "__main__":
    scenes = [file for file in os.listdir(SCENES_PATH)
              if os.path.isfile(os.path.join(SCENES_PATH, file))]

    for path in scenes:
        full_path = os.path.join(SCENES_PATH, path)
        print "%s\tstart" % full_path

        with open(full_path, "r+b") as compiled:
            mp_scene = compiled.read()

        scene = msgpack.unpackb(mp_scene)
        print "%s\tunpacked" % full_path

        for entity in scene["entities"]:
            for component in entity["components"]:
                component["type"] = COMPONENT_TYPES.get(component["type"])

        full_source = os.path.join(EDITOR_PATH, scene["source"])

        with open(full_source, "w") as decompiled:
            json.dump(scene, decompiled, sort_keys=True, indent=4, separators=(',', ': '))
        print "%s\twritten" % full_source
        print "-" * 4

    print "%s files decompiled" % len(scenes)