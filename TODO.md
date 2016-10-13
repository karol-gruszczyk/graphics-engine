# TODO`S

## alpha 1.1.4
* ~~OpenGL Debug callback~~
* ~~Add normal mapping~~
* ~~Parallax displacement mapping~~
* ~~Opacity maps - basic discard if lower than X~~
* ~~SkyBox~~
* Blinn-Phong
* AntiAliasing:
  * FXAA
* ~~Improve scene loader:~~
  * ~~nodes~~
  * ~~lights~~
  * ~~cameras~~
* ~~OpenGL extension class~~

## alpha 1.1.5
* SkyDome
* Simple sky shader
* Deferred rendering
* Instanced rendering
* Rendering detail settings
  * anisotropy
  * mipmap level
  * filter type
* Stencil Shadow Volume

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

## Optimizations
* Improve caching in factories
  * Use shared_ptr
  * When no reference to object exists it should be destroyed
* Optimize texture storage
* Optimize texture loading
  * remove converting to 32 BPP, instead return format
* Rewrite Camera class
  * add lookAt
  * use quaternions

## bugs
* Random Text artifacts
