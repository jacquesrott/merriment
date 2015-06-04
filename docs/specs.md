Camera:

- camera is dependant on window
- All the renderer have a bounding box, circle, by preference
- the only mask to check the collision with, is with the one from the camera, for speed reasons
- if colliding with camera mask, then add mesh/sprite to the linked list to render
- clear linked list


Programs:

- have to be unique
- can have a list of renderer

Renderer:

- renderable objects to render on the screen


Object to (de)serialize

- Entity
    - Physic Component:
        * Body
            * Shapes
                * attr
        * Mask
        * Group
    - Transform Component:
        * Position {2}
        * Angle 1
        * Scale {2}
    - Sprite Component:
        * Image path str
        * shader path
    - Mesh Component
        * shader path
        * indices
        * vertices
        ... normals
    - Script Component :
        * script path
        * instance (whole metatable from lua)
    - Camera Component :
        * Matrix {4, 4}