#ifndef GRAPHICS_ENGINE_RENDERER_HPP
#define GRAPHICS_ENGINE_RENDERER_HPP

#include <memory>
#include <glm/glm.hpp>
#include "bauasian/shaders/shader_program.hpp"
#include "bauasian/shaders/vertex_shader.hpp"
#include "bauasian/shaders/fragment_shader.hpp"
#include "bauasian/bauasian.hpp"
#include "bauasian/context_width_interface.hpp"


namespace bauasian
{
	class Renderer;
}

class bauasian::Renderer : public ContextWidthInterface
{
	friend class Scene;

public:
	Renderer();
	~Renderer();

	void clearScreen() const;

	ShaderProgram* getShaderProgram() const;
	const glm::mat4& getProjectionMatrix() const;
protected:
	glm::mat4 m_projection_matrix;

	ShaderProgram* m_shader_program = nullptr;
	virtual void updateContextSize() override;
};

#endif /* GRAPHICS_ENGINE_RENDERER_HPP */
