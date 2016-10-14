#include "preprocessor.hpp"
#include "bauasian/bauasian.hpp"

#include <sstream>


using bauasian::Preprocessor;
using bauasian::Bauasian;

Preprocessor::Preprocessor(const boost::filesystem::path& path, const std::map<std::string, std::string>& defines)
{
	m_source_code = getFileContent(path);
	parseIncludes(path);
	insertDefines(defines);
}

std::string Preprocessor::getSourceCode() const
{
	return m_source_code;
}

bool Preprocessor::isInsideComment(const std::size_t& position) const
{
	const auto first_block = m_source_code.rfind("/*", position);
	const auto last_block = m_source_code.rfind("*/", position);
	if (first_block != std::string::npos && (first_block > last_block || last_block == std::string::npos))
		return true;
	const auto inline_pos = m_source_code.rfind("//", position);
	const auto end_line = m_source_code.find("\n", inline_pos);
	return inline_pos != std::string::npos && (end_line > position || end_line == std::string::npos);
}

void Preprocessor::parseIncludes(const boost::filesystem::path& current_file)
{
	std::size_t position(0);
	while ((position = m_source_code.find("#include", position)) != std::string::npos)
	{
		if (isInsideComment(position))
		{
			position += 1;
			continue;
		}
		auto start = m_source_code.find('"', position);
		auto end = m_source_code.find('"', start + 1);
		auto line_end = m_source_code.find('\n', start + 1);
		if (start == std::string::npos || end == std::string::npos || end >= line_end)
		{
			auto exception = GLSLSyntaxErrorException(current_file,
			                                          m_source_code.substr(position, line_end - position));
			Bauasian::getInstance().logError(exception.what());
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

void Preprocessor::insertDefines(const auto& defines)
{
	const auto insert_location = m_source_code.find("\n", m_source_code.find("#version")) + 1;
	for (const auto& define : defines)
	{
		const auto formatted = "#define " + define.first + " " + define.second + "\n";
		m_source_code.insert(insert_location, formatted);
	}
}
