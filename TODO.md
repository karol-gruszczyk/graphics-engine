# TODO`S

## Optimizations
* Get uniform locations only once
* Set sampler2D textures in shaders only once

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
* Fix recognizing backslashes as path separator in boost::path
