#include "preprocessor.hpp"
#include "bauasian/bauasian.hpp"

#include <sstream>


using bauasian::Preprocessor;
using bauasian::Bauasian;

Preprocessor::Preprocessor(const boost::filesystem::path& path, const std::map<std::string, std::string>& defines)
{
	m_source_code = getFileContent(path);
	insertDefines(defines);
}

bool Preprocessor::isInsideComment(size_t position, const std::string& code) const
{
	const auto first_block = code.rfind("/*", position);
	const auto last_block = code.rfind("*/", position);
	if (first_block != std::string::npos && (first_block > last_block || last_block == std::string::npos))
		return true;
	const auto inline_pos = code.rfind("//", position);
	const auto end_line = code.find("\n", inline_pos);
	return inline_pos != std::string::npos && (end_line > position || end_line == std::string::npos);
}

const std::string Preprocessor::parseIncludes(const std::string& code,  const boost::filesystem::path& path) const
{
	std::string parsed_code = code;
	std::size_t position(0);
	while ((position = parsed_code.find("#include", position)) != std::string::npos)
	{
		if (isInsideComment(position, parsed_code))
		{
			position += 1;
			continue;
		}
		auto start = parsed_code.find('"', position);
		auto end = parsed_code.find('"', start + 1);
		auto line_end = parsed_code.find('\n', start + 1);
		if (start == std::string::npos || end == std::string::npos || end >= line_end)
		{
			auto exception = GLSLSyntaxErrorException(path, parsed_code.substr(position, line_end - position));
			Bauasian::getInstance().logError(exception.what());
			throw exception;
		}
		auto filename = parsed_code.substr(start + 1, end - start - 1);
		parsed_code.replace(position, end - position + 1, getFileContent(path.parent_path() / filename));
	}
	return parsed_code;
}

const std::string Preprocessor::getFileContent(const boost::filesystem::path& path) const
{
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	file.open(path.c_str(), std::ios::in);
	if (!file.good())
		throw FileNotFoundException(path);

	std::string file_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return parseIncludes(file_content, path);
}

void Preprocessor::insertDefines(const std::map<std::string, std::string>& defines)
{
	const auto insert_location = m_source_code.find("\n", m_source_code.find("#version")) + 1;
	for (const auto& define : defines)
	{
		const auto formatted = "#define " + define.first + " " + define.second + "\n";
		m_source_code.insert(insert_location, formatted);
	}
}
