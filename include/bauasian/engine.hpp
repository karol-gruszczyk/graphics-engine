#ifndef GRAPHICS_ENGINE_ENGINE_HPP
#define GRAPHICS_ENGINE_ENGINE_HPP

#include <string>
#include <fstream>
#include <map>
#include <GL/glew.h>
#include <boost/filesystem/path.hpp>
#include <glm/glm.hpp>


namespace bauasian
{
	class Engine;
}

class bauasian::Engine final
{
public:
	enum LogLevel
	{
		DEBUG, INFO, WARNING, ERROR
	};

	static Engine& getInstance();

	void setShaderPath(const boost::filesystem::path& path);
	const boost::filesystem::path& getShaderPath() const;
	void initializeLogger(const boost::filesystem::path& path = "log.txt");
	void initializeLogger(std::streambuf* ostream);
	void logInfo(const std::string& message) const;
	void logWarning(const std::string& message) const;
	void logError(const std::string& message) const;
	void logDebug(const std::string& message) const;
	void setContextSize(const glm::uvec2& context_size);

	void checkErrors() const;
private:
	Engine();
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	~Engine();

	static std::map<GLenum, const char* const> s_gl_errors;
	static std::map<LogLevel, const char* const> s_log_level_string;

	boost::filesystem::path m_working_dir;
	boost::filesystem::path m_shader_path = "glsl/";
	std::unique_ptr<std::ostream> m_logger;
	std::unique_ptr<std::ofstream> m_logger_file;

	void logInitial() const;
};

#endif /* GRAPHICS_ENGINE_ENGINE_HPP */
