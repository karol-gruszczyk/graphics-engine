#ifndef PREPROCESSOR_HPP_
#define PREPROCESSOR_HPP_

#include <string>
#include <boost/filesystem/path.hpp>
#include "../exceptions/file_not_found_exception.hpp"
#include "../exceptions/glsl_syntax_error_exception.hpp"


namespace engine
{
	class Preprocessor;
}

class engine::Preprocessor
{
public:
	Preprocessor(const boost::filesystem::path& path);

	std::string getSourceCode() const;
private:
	std::string m_source_code;

	void parseIncludes(const boost::filesystem::path& current_file);
	std::string getFileContent(const boost::filesystem::path& path) const;
};

#endif /* PREPROCESSOR_HPP_ */
