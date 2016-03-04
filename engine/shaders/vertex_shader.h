#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include "shader.h"


namespace engine
{
	class VertexShader;
}

class engine::VertexShader final : public engine::Shader
{
private:
	void initializeShader() override;
};

#endif /* VERTEX_SHADER_H_ */
