#include <sstream>
#include "texture.hpp"
#include "../config.hpp"
#include "image_loader.hpp"

using engine::Texture;


std::map<std::string, Texture*> Texture::s_textures;

Texture::Texture()
{}

Texture::Texture(unsigned width, unsigned height, GLubyte* pixels, GLint internal_format, GLenum format, bool generate_mipmaps)
{
	loadFromMemory(width, height, pixels, internal_format, format, generate_mipmaps);
}

Texture::~Texture()
{
	if (m_texture_created)
		glDeleteTextures(1, &m_texture_id);

    if (m_static_member)
    {
        for (const auto& texture : s_textures)
            delete texture.second;
    }
}

Texture* Texture::loadFromFile(const boost::filesystem::path& path)
{
    if (!boost::filesystem::exists(path))
        throw FileNotFoundException(path);

    auto string_path = boost::filesystem::canonical(path).string();
    if (s_textures.count(string_path))
        return s_textures[string_path];

    getInstance();
	ImageLoader loader(path);
	Texture* texture = new Texture();
    texture->loadFromMemory(loader.getWidth(), loader.getHeight(), loader.getPixels(),
                            GL_RGBA, GL_BGRA, true, string_path);
    s_textures[string_path] = texture;
    return texture;
}

void Texture::bind(unsigned short texture_level /* = 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + texture_level);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadFromMemory(unsigned width, unsigned height, GLubyte* pixels, GLint internal_format, GLenum format, bool generate_mipmaps, std::string image_name /* = "" */)
{
	m_width = width;
	m_height = height;

	auto is_power_of_2 = [](unsigned number) -> bool { return !(number & (number - 1)); };
	if (!is_power_of_2(m_width) || !is_power_of_2(m_height))
	{
		if (image_name.empty())
        {
            std::stringstream ss;
            ss << (void*)pixels;
            image_name = "In memory object at 0x" + ss.str();
        }
		auto dimensions = std::to_string(m_width) + " x " + std::to_string(m_height);
		engine::Config::getInstance().logWarning("Performance warning, image '" + image_name + "' - dimensions " + dimensions + " are not a power of 2");
	}

	glGenTextures(1, &m_texture_id);
	m_texture_created = true;

	glBindTexture(GL_TEXTURE_2D, m_texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, pixels);

	if (generate_mipmaps)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		if (glewIsExtensionSupported("GL_EXT_texture_filter_anisotropic"))
		{
			GLfloat max_anisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unbind(); 
}

Texture &Texture::getInstance()
{
    static Texture instance;
    instance.m_static_member = true;
    return instance;
}
