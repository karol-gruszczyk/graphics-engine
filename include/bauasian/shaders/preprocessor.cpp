#include "preprocessor.hpp"
#include "bauasian/engine.hpp"
#include <sstream>


using bauasian::Preprocessor;
using bauasian::Engine;


Preprocessor::Preprocessor(const boost::filesystem::path& path)
{
	m_source_code = getFileContent(path);
	parseIncludes(path);
}

std::string Preprocessor::getSourceCode() const
{
	return m_source_code;
}

void Preprocessor::parseIncludes(const boost::filesystem::path& current_file)
{
	std::size_t position(0);
	while ((position = m_source_code.find("#include")) != std::string::npos)
	{
		auto start = m_source_code.find('"', position);
		auto end = m_source_code.find('"', start + 1);
		auto line_end = m_source_code.find('\n', start + 1);
		if (start == std::string::npos || end == std::string::npos || end >= line_end)
		{
			auto exception = GLSLSyntaxErrorException(current_file,
			                                          m_source_code.substr(position, line_end - position));
			Engine::getInstance().logError(exception.what());
			throw exception;
		}
		auto filename = m_source_code.substr(start + 1, end - start - 1);
		m_source_code.replace(position, end - position + 1, getFileContent(current_file.parent_path() / filename));
	}
}

std::string Preprocessor::getFileContent(const boost::filesystem::path& path) const
{
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	file.open(path.c_str(), std::ios::in);
	if (!file.good())
		throw FileNotFoundException(path);

	std::string file_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return file_content;
}
