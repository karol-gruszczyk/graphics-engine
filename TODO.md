# TODO`S

## alpha 1.1.2
* ~~Rewrite Config class to Engine~~
  * add functionality for setting context sizes where it is needed  
    - this could be done by creating an interface ContextWidthInterface, 
      and it would add method and instance pointers to the main Engine class
* ~~Implement FreeType font loading~~
* Add dynamic text(one quad per glyph)

## alpha 1.1.3
* Implement FrameBufferObject
* Implement basic kernel filters

## alpha 1.1.4
* Rewrite dynamic text(one quad per glyph line)
* Add static text handling(using FrameBufferObject)

## non-release
* Implement a system for uniform location storage  
  * Add locations as shader program members with appropriate setters
* Add support for non ASCII characters in paths
* Improve scene loader
  * light loading
  * affine transformations
* Remove 2D / 3D classification
  * Project all as 3D
  * Project 2D as a 3D scene with camera looking down
  * Rewrite 2D objects to 3D entities with one coord 0
  * Project 2D without depth test

## bugs
* Directional light wont show if its the only light in the scene
