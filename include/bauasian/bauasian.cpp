#include "bauasian.hpp"
#include "context_width_interface.hpp"
#include <boost/filesystem/operations.hpp>


using bauasian::Bauasian;

std::map<GLenum, const char* const> Bauasian::s_gl_errors = {
		{ GL_INVALID_ENUM,                  "GL_INVALID_ENUM" },
		{ GL_INVALID_VALUE,                 "GL_INVALID_VALUE" },
		{ GL_INVALID_OPERATION,             "GL_INVALID_OPERATION" },
		{ GL_STACK_OVERFLOW,                "GL_STACK_OVERFLOW" },
		{ GL_STACK_UNDERFLOW,               "GL_STACK_UNDERFLOW" },
		{ GL_OUT_OF_MEMORY,                 "GL_OUT_OF_MEMORY" },
		{ GL_INVALID_FRAMEBUFFER_OPERATION, "GL_INVALID_FRAMEBUFFER_OPERATION" },
		{ GL_CONTEXT_LOST,                  "GL_CONTEXT_LOST" }
};
std::map<Bauasian::LogLevel, const char* const> Bauasian::s_log_level_string = {
		{ DEBUG,   "[ DEBUG ] " },
		{ INFO,    "[ INFO ] " },
		{ WARNING, "[ WARNING ] " },
		{ ERROR,   "[ ERROR ] " }
};

Bauasian::Bauasian()
{
	m_working_dir = boost::filesystem::current_path();
}

Bauasian::~Bauasian()
{
	if (m_logger_file)
		m_logger_file->close();
}

Bauasian& Bauasian::getInstance()
{
	static Bauasian instance;
	return instance;
}

void Bauasian::setShaderPath(const boost::filesystem::path& path)
{
	getInstance().m_shader_path = path;
}

const boost::filesystem::path& Bauasian::getShaderPath() const
{
	return getInstance().m_shader_path;
}

void Bauasian::initializeLogger(const boost::filesystem::path& path /* = "log.txt" */)
{
	if (m_logger_file)
	{
		m_logger_file->close();
		m_logger_file.reset();
	}
	m_logger_file = std::make_unique<std::ofstream>();
	m_logger_file->open(path.c_str(), std::ios::out);
	if (m_logger_file->good())
	{
		m_logger = std::make_unique<std::ostream>(m_logger_file->rdbuf());
		logInitial();
	}
}

void Bauasian::initializeLogger(std::streambuf* ostream)
{
	m_logger = std::make_unique<std::ostream>(ostream);
	logInitial();
}

void Bauasian::logInfo(const std::string& message) const
{
	*m_logger << s_log_level_string[INFO] << message << std::endl;
}

void Bauasian::logWarning(const std::string& message) const
{
	*m_logger << s_log_level_string[WARNING] << message << std::endl;
}

void Bauasian::logError(const std::string& message) const
{
	*m_logger << s_log_level_string[ERROR] << message << std::endl;
}

void Bauasian::logDebug(const std::string& message) const
{
	*m_logger << s_log_level_string[DEBUG] << message << std::endl;
}

void Bauasian::logInitial() const
{
	logInfo(std::string("Using OpenGL ") + (char*) glGetString(GL_VERSION));
	logInfo(std::string("OpenGL Shading Language version: ") + (char*) glGetString(GL_SHADING_LANGUAGE_VERSION));
	logInfo(std::string("Graphics card: ") + (char*) glGetString(GL_VENDOR) + " " + (char*) glGetString(GL_RENDERER));
}

void Bauasian::setContextSize(const glm::uvec2& context_size)
{
	ContextWidthInterface::setContextSize(context_size);
}

void Bauasian::checkErrors() const
{
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::string error_message;
		if (s_gl_errors.count(error))
			error_message = s_gl_errors[error];
		else
			error_message = "Error code not recognized";
		logError(error_message);
	}
}
