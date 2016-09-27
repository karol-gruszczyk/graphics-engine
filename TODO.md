# TODOS
## alpha 0.1.1
* ~~Add object loading~~
* ~~Add materials~~
* ~~Implement global texture storage in Texture class:~~
  * ~~private Texture constructor~~
  * ~~public static method for loading~~
* Implement materials to object loading
  * ~~Diffuse~~
  * Specular

## alpha 1.1.2
* Implement FreeType font loading
* Add dynamic text(one quad per glyph)

## alpha 1.1.3
* Implement FrameBufferObject
* Implement basic kernel filters

## alpha 1.1.4
* Rewrite dynamic text(one quad per glyph line)
* Add static text handling(using FrameBufferObject)

## non-release
* Remove 2D / 3D classification
  * Project all as 3D
  * Project 2D as a 3D scene with camera looking down
  * Rewrite 2D objects to 3D entities with one coord 0
  * Project 2D without depth test

## bugs
* Directional light wont show if its the only light in the scene
