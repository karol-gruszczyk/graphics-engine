#include "config.h"
#include <boost/filesystem/operations.hpp>
#include <iostream>

using engine::Config;


Config::Config()
{
	m_working_dir = boost::filesystem::current_path();
	m_shader_path = m_working_dir;
}

Config::~Config()
{
	if (m_logger_active)
		m_logger.close();
}

Config& Config::getInstance()
{
	static Config instance;
	return instance;
}

void Config::setShaderPath(boost::filesystem::path path)
{
	getInstance().m_shader_path = path;
}

boost::filesystem::path Config::getShaderPath()
{
	return getInstance().m_shader_path;
}

void Config::initializeLogger(boost::filesystem::path path /* = "" */)
{
	if (getInstance().m_logger_active)
		getInstance().m_logger.close();
	if (path.empty())
		path = getInstance().m_working_dir / "log.txt";
	getInstance().m_logger.open(path.c_str(), std::ios::out);
	if (getInstance().m_logger.good())
		getInstance().m_logger_active = true;
}

void Config::log(std::string& info_log)
{
	getInstance().m_logger << info_log << std::endl;
}
