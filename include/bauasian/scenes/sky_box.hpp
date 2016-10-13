#ifndef BAUASIAN_SKY_BOX_HPP
#define BAUASIAN_SKY_BOX_HPP

#include "bauasian/interfaces/context_size_interface.hpp"
#include "bauasian/materials/cube_texture.hpp"
#include "bauasian/shaders/shader_program.hpp"
#include "bauasian/primitives/screen_cube.hpp"


namespace bauasian
{
	class SkyBox;
}

class bauasian::SkyBox
{
public:
	SkyBox(CubeTexture* texture);
	~SkyBox();

	void render(const glm::mat4& projection_view_matrix) const;

private:
	ShaderProgram* m_shader_program;
	CubeTexture* m_texture;
	ScreenCube* m_box;

	GLint m_location_projection_view_matrix;

};


#endif /* BAUASIAN_SKY_BOX_HPP */
