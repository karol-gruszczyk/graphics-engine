#ifndef BAUASIAN_PREPROCESSOR_HPP
#define BAUASIAN_PREPROCESSOR_HPP

#include <string>
#include <boost/filesystem/path.hpp>
#include "bauasian/exceptions/file_not_found_exception.hpp"
#include "bauasian/exceptions/glsl_syntax_error_exception.hpp"


namespace bauasian
{
	class Preprocessor;
}

class bauasian::Preprocessor
{
public:
	Preprocessor(const boost::filesystem::path& path);

	std::string getSourceCode() const;
private:
	std::string m_source_code;

	void parseIncludes(const boost::filesystem::path& current_file);
	std::string getFileContent(const boost::filesystem::path& path) const;
};

#endif /* BAUASIAN_PREPROCESSOR_HPP */
