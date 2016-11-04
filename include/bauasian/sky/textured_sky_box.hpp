#ifndef BAUASIAN_TEXTURED_SKY_BOX_HPP
#define BAUASIAN_TEXTURED_SKY_BOX_HPP

#include "sky_box.hpp"
#include "bauasian/textures/cube_texture.hpp"


namespace bauasian
{
	class TexturedSkyBox;
}

class bauasian::TexturedSkyBox : public SkyBox
{
public:
	TexturedSkyBox(const CubeTexture* texture);

	void render(const glm::mat4& projection_view_matrix) const override;

private:
	const CubeTexture* m_texture;

};

#endif /* BAUASIAN_TEXTURED_SKY_BOX_HPP */
