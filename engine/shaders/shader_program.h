#ifndef SHADER_PROFRAM_H_
#define SHADER_PROFRAM_H_

#include <initializer_list>
#include <glm/glm.hpp>
#include "shader.h"
#include "../exceptions/shader_link_exception.h"


namespace engine
{
	class ShaderProgram;
}

class engine::ShaderProgram final
{
public:
	ShaderProgram();
	ShaderProgram(std::initializer_list<Shader*> shaders);
	~ShaderProgram();

	void init(std::initializer_list<Shader*> shaders);
	void bind();
	void unbind();
	void setUniformMatrix4(std::string uniform_name, glm::mat4 matrix);
private:
	GLuint m_shader_program_id;
	bool m_shader_program_created;
};

#endif /* SHADER_PROFRAM_H_ */
