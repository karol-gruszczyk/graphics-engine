#ifndef CONTROL_H_
#define CONTROL_H_

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
	static void setShaderPath(boost::filesystem::path path);
	static boost::filesystem::path getShaderPath();
	static void initializeLogger(boost::filesystem::path path = "");
	static void log(std::string& info_log);
private:
	Config();
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;
	~Config();

	static Config& getInstance();

	boost::filesystem::path m_working_dir;
	boost::filesystem::path m_shader_path;
	bool m_logger_active;
	std::ofstream m_logger;
};

#endif /* CONTROL_H_ */
