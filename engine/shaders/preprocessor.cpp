#include "preprocessor.hpp"
#include <fstream>
#include <sstream>

using engine::Preprocessor;


Preprocessor::Preprocessor(boost::filesystem::path path)
{
	m_source_code = getFileContent(path);
	parseIncludes(path.parent_path());
}

std::string& Preprocessor::getSourceCode()
{
	return m_source_code;
}

void Preprocessor::parseIncludes(boost::filesystem::path directory)
{
	std::size_t position(0);
	while (auto position = m_source_code.find("#include", position) != std::string::npos)
	{
		auto start = line.find('"', position);
		auto end = line.find('"', start + 1);
		if (start == std::string::npos || end != std::string::npos)
		{
			// unexpected end of string
		}
		auto filename = line.substr(start + 1, end - start);
		if (filename.size())
			m_source_code.replace(position, end - position, getFileContent(directory / filename));
		else
		{
			// empty filename
		}
		position = end;
	}
}

std::string Preprocessor::getFileContent(boost::filesystem::path path)
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
