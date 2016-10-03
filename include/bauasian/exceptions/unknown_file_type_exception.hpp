#ifndef BAUASIAN_UNKNOWN_FILE_TYPE_EXCEPTION_HPP
#define BAUASIAN_UNKNOWN_FILE_TYPE_EXCEPTION_HPP

#include <exception>
#include <boost/filesystem/operations.hpp>


namespace bauasian
{
	class UnknownFileTypeException;
}

class bauasian::UnknownFileTypeException : public std::runtime_error
{
public:
	UnknownFileTypeException(boost::filesystem::path path)
			: runtime_error("The file '" + boost::filesystem::canonical(path).string() + "' is of an unknown file type")
	{}
};

#endif /* BAUASIAN_UNKNOWN_FILE_TYPE_EXCEPTION_HPP */
