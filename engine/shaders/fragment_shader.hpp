#ifndef FRAGMENT_SHADER_HPP_
#define FRAGMENT_SHADER_HPP_

#include "shader.hpp"


namespace engine
{
	class FragmentShader;
}

class engine::FragmentShader final : public Shader
{
public:
	FragmentShader(boost::filesystem::path path);
};

#endif /* FRAGMENT_SHADER_HPP_ */
