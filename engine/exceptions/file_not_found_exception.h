#ifndef FILE_NOT_FOUND_EXCEPTION_H_
#define FILE_NOT_FOUND_EXCEPTION_H_

#include <exception>
#include <boost/filesystem/path.hpp>


namespace engine
{
	class FileNotFoundException;
}

class engine::FileNotFoundException : public std::runtime_error
{
public:
	FileNotFoundException(boost::filesystem::path path)
		: runtime_error("The file '" + path.string() + "' could not be found")
	{}
};

#endif /* FILE_NOT_FOUND_EXCEPTION_H_ */
