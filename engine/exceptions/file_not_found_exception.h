#ifndef FILE_NOT_FOUND_EXCEPTION_H_
#define FILE_NOT_FOUND_EXCEPTION_H_


#include <exception>


namespace engine
{
	class FileNotFoundException;
}

class engine::FileNotFoundException : public std::runtime_error
{
public:
	FileNotFoundException(std::string path)
		: runtime_error("The file '" + path + "' could not be found")
	{}
};

#endif /* FILE_NOT_FOUND_EXCEPTION_H_ */
