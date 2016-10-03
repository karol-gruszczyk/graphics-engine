#ifndef GRAPHICS_ENGINE_INITIALIZATION_FAILED_EXCEPTION_HPP
#define GRAPHICS_ENGINE_INITIALIZATION_FAILED_EXCEPTION_HPP

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

#endif /* GRAPHICS_ENGINE_INITIALIZATION_FAILED_EXCEPTION_HPP */
