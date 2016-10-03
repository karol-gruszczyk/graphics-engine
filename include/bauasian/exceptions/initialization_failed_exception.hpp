#ifndef BAUASIAN_INITIALIZATION_FAILED_EXCEPTION_HPP
#define BAUASIAN_INITIALIZATION_FAILED_EXCEPTION_HPP

#include <exception>
#include <boost/filesystem/operations.hpp>


namespace bauasian
{
	class InitializationFailedException;
}

class bauasian::InitializationFailedException : public std::runtime_error
{
public:
	InitializationFailedException(std::string what_failed)
			: runtime_error("Initialization of " + what_failed + " failed")
	{}
};

#endif /* BAUASIAN_INITIALIZATION_FAILED_EXCEPTION_HPP */
