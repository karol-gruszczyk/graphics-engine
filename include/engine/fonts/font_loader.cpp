#include "font_loader.hpp"
#include "engine/config.hpp"


using engine::FontLoader;

FT_Library *FontLoader::s_ft_lib;

FontLoader::FontLoader(const boost::filesystem::path &path)
{
	getGlobalInstance();

	auto full_path = boost::filesystem::canonical(path).string();
	Config::getInstance().logInfo("Loading font '" + full_path + "'");

	auto error = FT_New_Face(*s_ft_lib, path.string().c_str(), 0, &m_face);
	if (error != 0)
	{
		Config::getInstance().logError("FreeType failed to load font" + full_path + ". FT error code: "
		                               + std::to_string(error));
		return;
	}
	Config::getInstance().logInfo("Font '" + full_path + "' loaded");
}

FontLoader::~FontLoader()
{
	if (m_is_global)
	{
		FT_Done_FreeType(*s_ft_lib);
		delete s_ft_lib;
		Config::getInstance().logInfo("FreeType unloaded");
	}
}

const std::string FontLoader::getFreeTypeVersion()
{
	FT_Int major, minor, patch;
	FT_Library_Version(*s_ft_lib, &major, &minor, &patch);
	return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}

FontLoader::FontLoader()
		: m_is_global(true)
{
	s_ft_lib = new FT_Library;
	auto error = FT_Init_FreeType(s_ft_lib);
	if (error != 0)
		Config::getInstance().logError("FreeType failed to initialize. FT error code: " + std::to_string(error));
	else
		Config::getInstance().logInfo("FreeType " + getFreeTypeVersion() + " loaded");
}

FontLoader &FontLoader::getGlobalInstance()
{
	static FontLoader instance;
	return instance;
}
