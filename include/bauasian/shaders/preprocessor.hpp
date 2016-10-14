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

	bool isInsideComment(const std::size_t& position) const;
	void parseIncludes(const boost::filesystem::path& current_file);
	std::string getFileContent(const boost::filesystem::path& path) const;
	void insertDefines(const auto& defines);

};

#endif /* BAUASIAN_PREPROCESSOR_HPP */
