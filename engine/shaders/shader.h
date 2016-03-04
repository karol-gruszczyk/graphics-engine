#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include "../exceptions/shader_compile_exception.h"
#include "../exceptions/file_not_found_exception.h"


namespace engine
{
	class Shader;
}

class engine::Shader abstract
{
	friend class ShaderProgram;
public:
	Shader() {}
	~Shader();
	void loadFromFile(std::string path);
protected:
	GLuint m_shader_id;

	virtual void initializeShader() = 0;
};

#endif /* SHADER_H_ */
