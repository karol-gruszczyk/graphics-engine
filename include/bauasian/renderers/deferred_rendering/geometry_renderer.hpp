#ifndef BAUASIAN_GEOMETRY_RENDERER_HPP
#define BAUASIAN_GEOMETRY_RENDERER_HPP

#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/shaders/shader_program.hpp"
#include "bauasian/materials/texture.hpp"
#include "bauasian/scenes/scene_3d.hpp"


namespace bauasian
{
	class GeometryRenderer;
}

class bauasian::GeometryRenderer
{
public:
	GeometryRenderer(const glm::uvec2& size);
	~GeometryRenderer();

	void setSize(const glm::uvec2& size);
	void render(const Scene3D* const scene);

private:
	glm::uvec2 m_size;

	FrameBuffer* m_frame_buffer = nullptr;

	ShaderProgram* m_shader;

	std::shared_ptr<Texture> m_albedo_buffer;
	std::shared_ptr<Texture> m_specular_buffer;
	std::shared_ptr<Texture> m_normal_buffer;
	std::shared_ptr<Texture> m_position_buffer;

};

#endif /* BAUASIAN_GEOMETRY_RENDERER_HPP */
