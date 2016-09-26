#ifndef VERTEX_SHADER_HPP_
#define VERTEX_SHADER_HPP_

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

#endif /* VERTEX_SHADER_HPP_ */
