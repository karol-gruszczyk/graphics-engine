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
	VertexShader();
	VertexShader(boost::filesystem::path path);

	void loadFromFile(boost::filesystem::path path) override;
};

#endif /* VERTEX_SHADER_H_ */
