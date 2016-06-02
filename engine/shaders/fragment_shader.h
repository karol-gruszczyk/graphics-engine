#ifndef FRAGMENT_SHADER_H_
#define FRAGMENT_SHADER_H_

#include "shader.h"


namespace engine
{
	class FragmentShader;
}

class engine::FragmentShader final : public Shader
{
public:
	FragmentShader(boost::filesystem::path path);
};

#endif /* FRAGMENT_SHADER_H_ */
