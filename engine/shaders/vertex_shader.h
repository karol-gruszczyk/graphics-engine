#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include "shader.h"


namespace engine
{
	class VertexShader;
}

class engine::VertexShader final : public Shader
{
public:
	VertexShader(boost::filesystem::path path);
};

#endif /* VERTEX_SHADER_H_ */
