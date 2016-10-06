# TODO`S

## Optimizations
* Create UniformBufferObjects for:
  * ~~materials~~
  * Scene entities
  * scene lights
* ~~Remove position initialization etc. from constructors~~
* Get uniform locations only once
* Set sampler2D textures in shader`s only once
* Create DSA methods for settings gl objects attributes
  * ~~shader`s~~
  * ~~textures~~
* ~~Join vertex position, normal and texture coordinates buffers~~
* Create Fabrics for:
  * Texture
  * Font

## alpha 1.1.4
* Add dynamic font(one quad per glyph line)
* Add static fps_text handling(using FrameBufferObject)

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
* Add flip UV option for scene loading
* Fix recognizing backslashes as path separator in boost::path
* Fix material memory leaks from scene loader
* Fix font caching (does not consider font size)
