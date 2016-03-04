#ifndef FRAGMENT_SHADER_H_
#define FRAGMENT_SHADER_H_

#include "shader.h"


namespace engine
{
	class FragmentShader;
}

class engine::FragmentShader final : public engine::Shader
{
private:
	void initializeShader() override;
};

#endif /* FRAGMENT_SHADER_H_ */
