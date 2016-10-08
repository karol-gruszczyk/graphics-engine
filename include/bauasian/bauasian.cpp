#include "bauasian.hpp"
#include "context_size_interface.hpp"
#include "exceptions/open_gl_version_too_low.hpp"

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
	if (m_logger_file.good())
		m_logger_file.close();
	if (m_error_logger_file.good())
		m_error_logger_file.close();
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

void Bauasian::initialize(const boost::filesystem::path& log_file /* = "log.txt" */,
                          const boost::filesystem::path& error_file /* = "error.log" */)
{
	m_logger_file.open(log_file.c_str(), std::ios::out);
	if (m_logger_file.good())
	{
		m_logger = std::make_unique<std::ostream>(m_logger_file.rdbuf());
		logInitial();
	}
	m_error_logger_file.open(error_file.c_str(), std::ios::out);
	if (m_error_logger_file.good())
		m_error_logger = std::make_unique<std::ostream>(m_error_logger_file.rdbuf());
}

void Bauasian::initialize(std::streambuf* ostream, std::streambuf* err_ostream)
{
	m_logger = std::make_unique<std::ostream>(ostream);
	m_error_logger = std::make_unique<std::ostream>(err_ostream);
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
	*m_error_logger << s_log_level_string[ERROR] << message << std::endl;
}

void Bauasian::logDebug(const std::string& message) const
{
	*m_logger << s_log_level_string[DEBUG] << message << std::endl;
}

void Bauasian::setContextSize(const glm::uvec2& context_size)
{
	ContextSizeInterface::setContextSize(context_size);
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

void Bauasian::logInitial() const
{
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	if (major <= BAUASIAN_REQUIRED_OPEN_GL_MAJOR && minor < BAUASIAN_REQUIRED_OPEN_GL_MINOR)
		throw OpenGLVersionTooLow(major, minor);
	logInfo(std::string("Using OpenGL ") + (char*) glGetString(GL_VERSION));
	logInfo(std::string("OpenGL Shading Language version: ") + (char*) glGetString(GL_SHADING_LANGUAGE_VERSION));
	logInfo(std::string("Graphics card: ") + (char*) glGetString(GL_VENDOR) + " " + (char*) glGetString(GL_RENDERER));
}
