#ifndef BAUASIAN_PREPROCESSOR_HPP
#define BAUASIAN_PREPROCESSOR_HPP

#include "bauasian/exceptions/file_not_found_exception.hpp"
#include "bauasian/exceptions/glsl_syntax_error_exception.hpp"

#include <map>

#include <boost/filesystem/path.hpp>


namespace bauasian
{
	class Preprocessor;
}

class bauasian::Preprocessor
{
public:
	Preprocessor(const boost::filesystem::path& path, const std::map<std::string, std::string>& defines);

	std::string getSourceCode() const;
private:
	std::string m_source_code;

	bool isInsideComment(size_t position, const std::string& code) const;
	const std::string parseIncludes(const std::string& code, const boost::filesystem::path& path) const;
	const std::string getFileContent(const boost::filesystem::path& path) const;
	void insertDefines(const std::map<std::string, std::string>& defines);

};

#endif /* BAUASIAN_PREPROCESSOR_HPP */
