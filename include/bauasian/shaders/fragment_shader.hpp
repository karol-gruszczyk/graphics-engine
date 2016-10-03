#ifndef GRAPHICS_ENGINE_FRAGMENT_SHADER_HPP
#define GRAPHICS_ENGINE_FRAGMENT_SHADER_HPP

#include "shader.hpp"


namespace bauasian
{
	class FragmentShader;
}

class bauasian::FragmentShader final : public Shader
{
public:
	FragmentShader(const boost::filesystem::path& path);
};

#endif /* GRAPHICS_ENGINE_FRAGMENT_SHADER_HPP */
