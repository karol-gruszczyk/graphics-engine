#ifndef INITIALIZATION_FAILED_EXCEPTION_H_
#define INITIALIZATION_FAILED_EXCEPTION_H_

#include <exception>
#include <boost/filesystem/operations.hpp>


namespace engine
{
	class InitializationFailedException;
}

class engine::InitializationFailedException : public std::runtime_error
{
public:
	InitializationFailedException(std::string what_failed)
		: runtime_error("Initialization of " + what_failed + " failed")
	{}
};

#endif /* INITIALIZATION_FAILED_EXCEPTION_H_ */
