#ifndef GRAPHICS_ENGINE_PREPROCESSOR_HPP
#define GRAPHICS_ENGINE_PREPROCESSOR_HPP

#include <string>
#include <boost/filesystem/path.hpp>
#include "engine/exceptions/file_not_found_exception.hpp"
#include "engine/exceptions/glsl_syntax_error_exception.hpp"


namespace engine
{
	class Preprocessor;
}

class engine::Preprocessor
{
public:
	Preprocessor(const boost::filesystem::path &path);

	std::string getSourceCode() const;
private:
	std::string m_source_code;

	void parseIncludes(const boost::filesystem::path &current_file);
	std::string getFileContent(const boost::filesystem::path &path) const;
};

#endif /* GRAPHICS_ENGINE_PREPROCESSOR_HPP */
