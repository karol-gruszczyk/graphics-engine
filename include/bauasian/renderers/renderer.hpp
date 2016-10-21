#ifndef BAUASIAN_RENDERER_HPP
#define BAUASIAN_RENDERER_HPP

#include "bauasian/bauasian.hpp"
#include "bauasian/interfaces/context_size_interface.hpp"
#include "bauasian/shaders/shader_program.hpp"

#include <glm/glm.hpp>


namespace bauasian
{
	class Renderer;
}

class bauasian::Renderer : public ContextSizeInterface
{
	friend class Scene;

public:
	Renderer();
	virtual ~Renderer();

	void clearScreen() const;

	ShaderProgram* getShaderProgram() const;
	const glm::mat4& getProjectionMatrix() const;

protected:
	glm::mat4 m_projection_matrix;

	ShaderProgram* m_shader_program = nullptr;
};

#endif /* BAUASIAN_RENDERER_HPP */
