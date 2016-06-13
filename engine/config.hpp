#ifndef CONFIG_HPP_
#define CONFIG_HPP_

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

	void setShaderPath(const boost::filesystem::path& path);
	const boost::filesystem::path& getShaderPath() const;
	void initializeLogger(const boost::filesystem::path& path = "");
	void initializeLogger(std::streambuf* ostream);
	void log(const std::string& info_log, const LogLevel& log_level = INFO) const;
	void logErrors() const;
private:
	Config();
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;
	~Config();

	void logEngineInitial() const;
	const std::string logLevelToString(const LogLevel& log_level) const;

	boost::filesystem::path m_working_dir;
	boost::filesystem::path m_shader_path;
	std::unique_ptr<std::ostream> m_logger;
	std::unique_ptr<std::ofstream> m_logger_file;
};

#endif /* CONFIG_HPP_ */
