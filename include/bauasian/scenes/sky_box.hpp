#ifndef BAUASIAN_SKY_BOX_HPP
#define BAUASIAN_SKY_BOX_HPP

#include "bauasian/shaders/shader_program.hpp"
#include "bauasian/primitives/screen_cube.hpp"


namespace bauasian
{
	class SkyBox;
}

class bauasian::SkyBox
{
public:
	SkyBox(const boost::filesystem::path& fragment_shader_path);
	virtual ~SkyBox();

	virtual void render(const glm::mat4& projection_view_matrix) const;

protected:
	ShaderProgram* m_shader_program;
	ScreenCube* m_box;

	GLint m_location_projection_view_matrix;

};

#endif /* BAUASIAN_SKY_BOX_HPP */
