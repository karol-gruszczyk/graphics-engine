#ifndef BAUASIAN_OPEN_GL_EXTENSIONS_HPP
#define BAUASIAN_OPEN_GL_EXTENSIONS_HPP

#include <set>

#include <GL/glew.h>


namespace bauasian
{
	class OpenGLExtensions;
}

class bauasian::OpenGLExtensions
{
public:
	static OpenGLExtensions& getInstance();
	static bool isExtensionSupported(const std::string& name);

	bool isAnisotropicFilteringSupported() const;
	GLfloat getMaxAnisotropy();

private:
	OpenGLExtensions();

	std::set<std::string> m_extension_names;
	std::set<GLenum> m_extensions;
	GLfloat m_max_anisotropy;

	void loadSupportedExtensions();

};


#endif /* BAUASIAN_OPEN_GL_EXTENSIONS_HPP */
