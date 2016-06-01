#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "texture.h"


namespace engine
{
	class Material;
}

class engine::Material
{
public:
	Material();
	~Material();
private:
	Texture m_diffuse_texture;
};

#endif /* MATERIAL_H_ */
