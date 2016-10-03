#ifndef GRAPHICS_ENGINE_VERTEX_SHADER_HPP
#define GRAPHICS_ENGINE_VERTEX_SHADER_HPP

#include "shader.hpp"


namespace bauasian
{
	class VertexShader;
}

class bauasian::VertexShader final : public Shader
{
public:
	VertexShader(const boost::filesystem::path& path);
};

#endif /* GRAPHICS_ENGINE_VERTEX_SHADER_HPP */
