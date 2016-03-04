#include "vertex_shader.h"

using engine::VertexShader;


void VertexShader::initializeShader()
{
	m_shader_id = glCreateShader(GL_VERTEX_SHADER);
}

