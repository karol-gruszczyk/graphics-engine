#ifndef FILE_TYPE_NOT_SUPPORTED_EXCEPTION_HPP_
#define FILE_TYPE_NOT_SUPPORTED_EXCEPTION_HPP_

#include <exception>
#include <boost/filesystem/operations.hpp>


namespace engine
{
	class FileTypeNotSupportedException;
}

class engine::FileTypeNotSupportedException : public std::runtime_error
{
public:
	FileTypeNotSupportedException(boost::filesystem::path path)
		: runtime_error("The file type of '" + boost::filesystem::canonical(path).string() + "' is not supported")
	{}
};

#endif /* FILE_TYPE_NOT_SUPPORTED_EXCEPTION_HPP_ */
