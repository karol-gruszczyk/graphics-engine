#ifndef BAUASIAN_SHADER_PROFRAM_HPP
#define BAUASIAN_SHADER_PROFRAM_HPP

#include <initializer_list>
#include <glm/glm.hpp>
#include "shader.hpp"
#include "bauasian/exceptions/shader_link_exception.hpp"


namespace bauasian
{
	class ShaderProgram;
}

class bauasian::ShaderProgram final
{
public:
	ShaderProgram(const std::initializer_list<Shader*>& shaders);
	~ShaderProgram();

	void bind() const;
	void unbind() const;
	void setUniformBool(const std::string& uniform_name, const bool& value) const;
	void setUniformFloat(const std::string& uniform_name, const float& value) const;
	void setUniformInt(const std::string& uniform_name, const int& value) const;
	void setUniformUInt(const std::string& uniform_name, const unsigned& value) const;
	void setUniformVector2(const std::string& uniform_name, const glm::vec2& vector) const;
	void setUniformVector3(const std::string& uniform_name, const glm::vec3& vector) const;
	void setUniformMatrix3(const std::string& uniform_name, const glm::mat3& matrix) const;
	void setUniformMatrix4(const std::string& uniform_name, const glm::mat4& matrix) const;
private:
	GLuint m_shader_program_id;
	bool m_shader_program_created;
};

#endif /* BAUASIAN_SHADER_PROFRAM_HPP */
