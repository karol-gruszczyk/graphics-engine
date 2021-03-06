#ifndef BAUASIAN_FILE_TYPE_NOT_SUPPORTED_EXCEPTION_HPP
#define BAUASIAN_FILE_TYPE_NOT_SUPPORTED_EXCEPTION_HPP

#include <exception>
#include <boost/filesystem/operations.hpp>


namespace bauasian
{
	class FileTypeNotSupportedException;
}

class bauasian::FileTypeNotSupportedException : public std::runtime_error
{
public:
	FileTypeNotSupportedException(boost::filesystem::path path)
			: runtime_error("The file type of '" + boost::filesystem::canonical(path).string() + "' is not supported")
	{}
};

#endif /* BAUASIAN_FILE_TYPE_NOT_SUPPORTED_EXCEPTION_HPP */
