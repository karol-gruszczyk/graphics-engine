#ifndef GRAPHICS_ENGINE_CONFIG_HPP
#define GRAPHICS_ENGINE_CONFIG_HPP

#include <string>
#include <fstream>
#include <boost/filesystem/path.hpp>


namespace engine
{
	class Config;
}

class engine::Config final
{
public:
	enum LogLevel
	{
		DEBUG, INFO, WARNING, ERROR
	};

	static Config& getInstance();

	void setShaderPath(const boost::filesystem::path& path);
	const boost::filesystem::path& getShaderPath() const;
	void initializeLogger(const boost::filesystem::path& path = "");
	void initializeLogger(std::streambuf* ostream);
	void log(const std::string& message, const LogLevel& log_level = INFO) const;
	void logInfo(const std::string& message) const;
	void logWarning(const std::string& message) const;
	void logError(const std::string& message) const;
	void logDebug(const std::string& message) const;

	void logErrors() const;
private:
	Config();
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;
	~Config();

	void logInitial() const;
	const std::string logLevelToString(const LogLevel& log_level) const;

	boost::filesystem::path m_working_dir;
	boost::filesystem::path m_shader_path = "glsl/";
	std::unique_ptr<std::ostream> m_logger;
	std::unique_ptr<std::ofstream> m_logger_file;
};

#endif /* GRAPHICS_ENGINE_CONFIG_HPP */
