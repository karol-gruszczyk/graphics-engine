#include "config.h"
#include <GL/glew.h>
#include <boost/filesystem/operations.hpp>

using engine::Config;


Config::Config()
{
	m_working_dir = boost::filesystem::current_path();
	m_shader_path = m_working_dir;
}

Config::~Config()
{
	if (m_logger_file)
		m_logger_file->close();
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
	if (m_logger_file)
	{
		m_logger_file->close();
		m_logger_file.reset();
	}
	if (path.empty())
		path = m_working_dir / "log.txt";
	m_logger_file = std::make_unique<std::ofstream>();
	m_logger_file->open(path.c_str(), std::ios::out);
	if (m_logger_file->good())
	{
		m_logger = std::make_unique<std::ostream>(m_logger_file->rdbuf());
		logEngineInitial();
	}
}

void Config::initializeLogger(std::streambuf* ostream)
{
	m_logger = std::make_unique<std::ostream>(ostream);
	logEngineInitial();
}

void Config::log(std::string info_log, LogLevel log_level /* = INFO */)
{
	if (m_logger)
		*m_logger << logLevelToString(log_level) << info_log << std::endl;
}

void Config::logEngineInitial()
{
	log(std::string("Using OpenGL ") + (char*)glGetString(GL_VERSION));
	log(std::string("OpenGL Shading Language version: ") + (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	log(std::string("Graphics card: ") + (char*)glGetString(GL_VENDOR) + " " + (char*)glGetString(GL_RENDERER));
}

std::string Config::logLevelToString(LogLevel log_level)
{
	switch (log_level)
	{
	case DEBUG:
		return "[ DEBUG ] ";
	case INFO:
		return "[ INFO ] ";
	case WARNING:
		return "[ WARNING ] ";
	case ERROR:
		return "[ ERROR ] ";
	default:
		return "";
	}
}

void Config::logErrors()
{
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::string error_message;
		switch (error)
		{
		case GL_INVALID_ENUM:
			error_message = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			error_message = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			error_message = "GL_INVALID_OPERATION";
			break;
		case GL_STACK_OVERFLOW:
			error_message = "GL_STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			error_message = "GL_STACK_UNDERFLOW";
			break;
		case GL_OUT_OF_MEMORY:
			error_message = "GL_OUT_OF_MEMORY";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			error_message = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_CONTEXT_LOST:
			error_message = "GL_CONTEXT_LOST";
			break;
		default:
			error_message = "Error code not recognized";
		}
		log(error_message, ERROR);
	}
}
