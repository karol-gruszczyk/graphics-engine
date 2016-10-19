# TODO`S

## alpha 1.1.5
* Shadow mapping
  * Directional lights
  * Spot lights
  * Point lights
* ~~Simple sky shader~~
* Deferred rendering
* Additional primitives
  * Circle
  * Sphere
* ~~Gamma correction~~
* ~~High Dynamic Range~~

## alpha 1.1.6
* Stencil Shadow Volume
  * Directional lights
  * Spot lights
  * Point lights
* Instanced rendering
* Add Circle primitive
* Add Sphere primitive
* SkyDome alternative for SkyBox

## Improvements
* Add support for non ASCII characters in paths
* Remove 2D / 3D classification
  * Project all as 3D
  * Project 2D as a 3D scene with camera looking down
  * Rewrite 2D objects to 3D entities with one coord 0
  * Project 2D without depth test
* Rendering settings
  * anisotropy
  * mipmap level
  * filter type

## Optimizations
* ~~Improve single channel textures in shader`s~~
* FXAA:
  * prior shader should calculate luminance into alpha channel
* Improve caching in factories
  * Use shared_ptr
  * When no reference to object exists it should be destroyed
* ~~Optimize texture storage~~
* ~~Optimize texture loading~~
  * ~~remove converting to 32 BPP, instead return format~~
* Rewrite Camera class
  * add lookAt
  * use quaternions

## bugs
* Random Text artifacts
