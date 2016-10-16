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

	Texture* getTexture(const boost::filesystem::path& path, const bool& is_standardized = true);
	CubeTexture* getCubeTexture(const boost::filesystem::path& path);
	CubeTexture* getCubeTexture(const std::vector<boost::filesystem::path>& paths);

private:
	TextureFactory();
	~TextureFactory();

	std::map<std::string, TextureInterface*> m_textures;

	const GLenum getFormatFromBPP(const unsigned& bpp, const bool& is_internal, const bool& is_standardized);

};

#endif /* BAUASIAN_TEXTURE_FACTORY_HPP */
