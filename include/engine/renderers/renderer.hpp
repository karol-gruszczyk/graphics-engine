#ifndef GRAPHICS_ENGINE_RENDERER_HPP
#define GRAPHICS_ENGINE_RENDERER_HPP

#include <memory>
#include <glm/glm.hpp>
#include "engine/shaders/shader_program.hpp"
#include "engine/shaders/vertex_shader.hpp"
#include "engine/shaders/fragment_shader.hpp"
#include "engine/engine.hpp"
#include "engine/context_width_interface.hpp"


namespace engine
{
	class Renderer;
}

class engine::Renderer : public ContextWidthInterface
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
