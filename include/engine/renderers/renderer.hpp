#ifndef GRAPHICS_ENGINE_RENDERER_HPP
#define GRAPHICS_ENGINE_RENDERER_HPP

#include <memory>
#include <glm/glm.hpp>
#include "engine/shaders/shader_program.hpp"
#include "engine/shaders/vertex_shader.hpp"
#include "engine/shaders/fragment_shader.hpp"
#include "engine/engine.hpp"


namespace engine
{
	class Renderer;
}

class engine::Renderer
{
	friend class Scene;

public:
	Renderer();
	~Renderer();

	virtual void setContextWidth(const unsigned& context_width, const unsigned& context_height);
	void clearScreen() const;

	ShaderProgram* getShaderProgram() const;
	const glm::mat4& getProjectionMatrix() const;
protected:
	unsigned m_context_width, m_context_height;
	glm::mat4 m_projection_matrix;

	ShaderProgram* m_shader_program = nullptr;
	virtual void updateProjectionMatrix() = 0;
};

#endif /* GRAPHICS_ENGINE_RENDERER_HPP */
