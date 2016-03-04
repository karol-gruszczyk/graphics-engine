#include "fragment_shader.h"

using engine::FragmentShader;


void FragmentShader::initializeShader()
{
	m_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
}
