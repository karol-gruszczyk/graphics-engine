#ifndef CONFIG_H_
#define CONFIG_H_

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
	enum LogLevel { DEBUG, INFO, WARNING, ERROR };

	static Config& getInstance();

	void setShaderPath(boost::filesystem::path path);
	boost::filesystem::path getShaderPath();
	void initializeLogger(boost::filesystem::path path = "");
	void initializeLogger(std::streambuf* ostream);
	void log(std::string info_log, LogLevel log_level = INFO);
	void logErrors();
private:
	Config();
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;
	~Config();

	void logEngineInitial();
	std::string logLevelToString(LogLevel log_level);

	boost::filesystem::path m_working_dir;
	boost::filesystem::path m_shader_path;
	std::unique_ptr<std::ostream> m_logger;
	std::unique_ptr<std::ofstream> m_logger_file;
};

#endif /* CONFIG_H_ */
