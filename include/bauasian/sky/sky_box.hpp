#ifndef BAUASIAN_SKY_BOX_HPP
#define BAUASIAN_SKY_BOX_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/primitives/screen_cube.hpp"


namespace bauasian
{
	class SkyBox;
}

class bauasian::SkyBox : public ShaderMixin
{
public:
	SkyBox(const boost::filesystem::path& fragment_shader_path);
	virtual ~SkyBox() {};

	virtual void render(const glm::mat4& projection_view_matrix) const;

protected:
	std::unique_ptr<ScreenCube> m_box;

	GLint m_location_projection_view_matrix;

};

#endif /* BAUASIAN_SKY_BOX_HPP */
