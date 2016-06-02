#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <boost/filesystem/path.hpp>
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
	Shader(boost::filesystem::path path, GLenum type);
	virtual ~Shader();
protected:
	GLuint m_shader_id;
};

#endif /* SHADER_H_ */
