#include "texture_factory.hpp"
#include "image_loader.hpp"


using bauasian::TextureFactory;
using bauasian::Texture;
using bauasian::CubeTexture;

TextureFactory& TextureFactory::getInstance()
{
	static TextureFactory instance;
	return instance;
}

Texture* TextureFactory::getTexture(const boost::filesystem::path& path)
{
	if (!boost::filesystem::exists(path))
		throw FileNotFoundException(path);

	const auto string_path = boost::filesystem::canonical(path).string();
	if (m_textures.count(string_path))
		return static_cast<Texture*>(m_textures[string_path]);

	ImageLoader loader(path);
	Texture* texture = new Texture(loader.getWidth(), loader.getHeight(), loader.getPixels(),
	                               GL_RGBA, GL_BGRA, true, string_path);
	m_textures[string_path] = texture;
	return texture;
}

CubeTexture* TextureFactory::getCubeTexture(const boost::filesystem::path& path)
{
	throw std::runtime_error("not implemented");
}

CubeTexture* TextureFactory::getCubeTexture(const std::vector<boost::filesystem::path>& paths)
{
	assert(paths.size() == 6);

	const auto path_str = paths.front().string();
	if (m_textures.count(path_str))
		return static_cast<CubeTexture*>(m_textures[path_str]);

	std::for_each(paths.begin(), paths.end(),
	              [](const auto& p) -> void { if (!boost::filesystem::exists(p)) throw FileNotFoundException(p); });

	std::vector<ImageLoader*> loaders;
	std::vector<unsigned> widths, heights;
	std::vector<unsigned char*> pixel_ptrs;
	for (const auto& path : paths)
	{
		loaders.push_back(new ImageLoader(path));
		widths.push_back(loaders.back()->getWidth());
		heights.push_back(loaders.back()->getHeight());
		pixel_ptrs.push_back(loaders.back()->getPixels());
	}
	CubeTexture* texture = new CubeTexture(widths, heights, pixel_ptrs, GL_RGB, GL_RGB);
	m_textures[path_str] = texture;
	std::for_each(loaders.begin(), loaders.end(), [](ImageLoader* l) -> void { delete l; });
	return texture;
}

TextureFactory::TextureFactory()
{}

TextureFactory::~TextureFactory()
{
	for (const auto& texture : m_textures)
		delete texture.second;
}
