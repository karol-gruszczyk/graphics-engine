#ifndef BAUASIAN_ENGINE_HPP
#define BAUASIAN_ENGINE_HPP

#include <map>
#include <string>
#include <fstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <boost/filesystem/path.hpp>


namespace bauasian
{
	class Bauasian;
}

class bauasian::Bauasian final
{
public:
	enum LogLevel
	{
		DEBUG, INFO, WARNING, ERROR
	};

	static Bauasian& getInstance();

	void setShaderPath(const boost::filesystem::path& path);
	const boost::filesystem::path& getShaderPath() const;
	void initialize(const boost::filesystem::path& log_file = "log.txt",
	                const boost::filesystem::path& error_file = "error.log");
	void initialize(std::streambuf* ostream, std::streambuf* err_ostream);
	void logInfo(const std::string& message) const;
	void logWarning(const std::string& message) const;
	void logError(const std::string& message) const;
	void logDebug(const std::string& message) const;
	void setContextSize(const glm::uvec2& context_size);
	void checkErrors() const;

private:
	Bauasian();
	Bauasian(const Bauasian&) = delete;
	Bauasian& operator=(const Bauasian&) = delete;
	~Bauasian();

	static std::map<GLenum, const char* const> s_gl_errors;
	static std::map<LogLevel, const char* const> s_log_level_string;

	boost::filesystem::path m_working_dir;
	boost::filesystem::path m_shader_path = "glsl/";
	std::unique_ptr<std::ostream> m_logger, m_error_logger;
	std::ofstream m_logger_file, m_error_logger_file;

	void logInitial() const;
};

#endif /* BAUASIAN_ENGINE_HPP */
