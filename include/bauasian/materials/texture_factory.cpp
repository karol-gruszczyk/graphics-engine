#include "texture_factory.hpp"


using bauasian::TextureFactory;

TextureFactory& TextureFactory::getInstance()
{
	static TextureFactory instance;
	return instance;
}

bauasian::Texture* TextureFactory::getTexture(const boost::filesystem::path& path)
{
	if (!boost::filesystem::exists(path))
		throw FileNotFoundException(path);

	auto string_path = boost::filesystem::canonical(path).string();
	if (m_textures.count(string_path))
		return m_textures[string_path];

	ImageLoader loader(path);
	Texture* texture = new Texture(loader.getWidth(), loader.getHeight(), loader.getPixels(),
	                               GL_RGBA, GL_BGRA, true, string_path);
	m_textures[string_path] = texture;
	return texture;
}

TextureFactory::TextureFactory()
{}

TextureFactory::~TextureFactory()
{
	for (const auto& texture : m_textures)
		delete texture.second;
}
