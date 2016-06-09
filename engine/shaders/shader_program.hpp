#ifndef SHADER_PROFRAM_HPP_
#define SHADER_PROFRAM_HPP_

#include <initializer_list>
#include <glm/glm.hpp>
#include "shader.hpp"
#include "../exceptions/shader_link_exception.hpp"


namespace engine
{
	class ShaderProgram;
}

class engine::ShaderProgram final
{
public:
	ShaderProgram(std::initializer_list<Shader*> shaders);
	~ShaderProgram();

	void bind();
	void unbind();
	void setUniformFloat(std::string uniform_name, float value);
	void setUniformUint(std::string uniform_name, unsigned value);
	void setUniformVector3(std::string uniform_name, glm::vec3 vector);
	void setUniformMatrix3(std::string uniform_name, glm::mat3 matrix);
	void setUniformMatrix4(std::string uniform_name, glm::mat4 matrix);
private:
	GLuint m_shader_program_id;
	bool m_shader_program_created;
};

#endif /* SHADER_PROFRAM_HPP_ */
