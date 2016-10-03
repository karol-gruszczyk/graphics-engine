#ifndef GRAPHICS_ENGINE_VERTEX_SHADER_HPP
#define GRAPHICS_ENGINE_VERTEX_SHADER_HPP

#include "shader.hpp"


namespace engine
{
	class VertexShader;
}

class engine::VertexShader final : public Shader
{
public:
	VertexShader(const boost::filesystem::path& path);
};

#endif /* GRAPHICS_ENGINE_VERTEX_SHADER_HPP */
