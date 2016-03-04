#ifndef SHADER_PROFRAM_H_
#define SHADER_PROFRAM_H_

#include <vector>
#include "shader.h"
#include "../exceptions/shader_link_exception.h"


namespace engine
{
	class ShaderProgram;
}

class engine::ShaderProgram final
{
public:
	ShaderProgram() {}
	~ShaderProgram();
	void create(std::vector<Shader*> shaders);
	void bind();
	void unbind();
private:
	GLuint m_shader_program_id;
};

#endif /* SHADER_PROFRAM_H_ */
