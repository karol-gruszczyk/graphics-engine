#include "textured_sky_box.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::TexturedSkyBox;

TexturedSkyBox::TexturedSkyBox(bauasian::CubeTexture* texture)
		: SkyBox("skybox/basic_fs.glsl"), m_texture(texture)
{
	const auto location_cube_texture = m_shader->getUniformLocation("cube_texture");
	m_shader->setUniform(location_cube_texture, 0);
}

void TexturedSkyBox::render(const glm::mat4& projection_view_matrix) const
{
	m_texture->bind(0);
	SkyBox::render(projection_view_matrix);
}
