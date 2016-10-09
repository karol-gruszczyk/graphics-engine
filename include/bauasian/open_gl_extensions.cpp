#include <iostream>
#include "open_gl_extensions.hpp"


using bauasian::OpenGLExtensions;

OpenGLExtensions& bauasian::OpenGLExtensions::getInstance()
{
	static OpenGLExtensions instance;
	return instance;
}

bool OpenGLExtensions::isExtensionSupported(const std::string& name)
{
	return getInstance().m_extension_names.count(name) != 0;
}

bool OpenGLExtensions::isAnisotropicFilteringSupported() const
{
	return m_extensions.count(GL_EXT_texture_filter_anisotropic) != 0;
}

const GLfloat& OpenGLExtensions::getMaxAnisotropy()
{
	return m_max_anisotropy;
}

OpenGLExtensions::OpenGLExtensions()
{
	loadSupportedExtensions();
}

void OpenGLExtensions::loadSupportedExtensions()
{
	GLint num_extensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
	for (GLuint i = 0; i < num_extensions; i++)
	{
		const std::string extension = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));
		m_extension_names.insert(extension);
	}

	if (m_extension_names.count("GL_EXT_texture_filter_anisotropic") != 0)
	{
		m_extensions.insert(GL_EXT_texture_filter_anisotropic);
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &m_max_anisotropy);
	}
}
