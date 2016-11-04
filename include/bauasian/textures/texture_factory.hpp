#ifndef BAUASIAN_TEXTURE_FACTORY_HPP
#define BAUASIAN_TEXTURE_FACTORY_HPP

#include "texture.hpp"
#include "cube_texture.hpp"


namespace bauasian
{
	class TextureFactory;
}

class bauasian::TextureFactory
{
public:
	TextureFactory(const TextureFactory&) = delete;
	TextureFactory& operator=(const TextureFactory&) = delete;

	static TextureFactory& getInstance();

	Texture* getTexture(const boost::filesystem::path& path, bool is_standardized = true);
	CubeTexture* getCubeTexture(const boost::filesystem::path& path, bool is_standardized = true);
	CubeTexture* getCubeTexture(const std::vector<boost::filesystem::path>& paths, bool is_standardized = true);

private:
	TextureFactory();
	~TextureFactory();

	std::map<std::string, TextureMixin*> m_textures;

	const GLenum getFormatFromBPP(unsigned bpp, bool is_internal, bool is_standardized);

};

#endif /* BAUASIAN_TEXTURE_FACTORY_HPP */
