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
	Preprocessor(boost::filesystem::path path);

	std::string& getSourceCode();
private:
	std::string m_source_code;

	void parseIncludes(boost::filesystem::path current_file);
	std::string getFileContent(boost::filesystem::path path);
};

#endif /* PREPROCESSOR_HPP_ */
