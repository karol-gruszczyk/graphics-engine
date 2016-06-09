#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <memory>
#include <glm/glm.hpp>
#include "../shaders/shader_program.hpp"
#include "../shaders/vertex_shader.hpp"
#include "../shaders/fragment_shader.hpp"
#include "../config.hpp"


namespace engine
{
	class Renderer;
}

class engine::Renderer abstract
{
	friend class Scene;
public:
	Renderer();

	virtual void setContextWidth(unsigned context_width, unsigned context_height);
	void clearScreen();

	ShaderProgram* getShaderProgram();
	glm::mat4& getProjectionMatrix();
protected:
	unsigned m_context_width, m_context_height;
	glm::mat4 m_projection_matrix;

	std::unique_ptr<VertexShader> m_vertex_shader;
	std::unique_ptr<FragmentShader> m_fragment_shader;
	std::unique_ptr<ShaderProgram> m_shader_program;
	virtual void updateProjectionMatrix() = 0;
};

#endif /* RENDERER_HPP_ */
