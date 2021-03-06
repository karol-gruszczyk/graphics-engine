#ifndef BAUASIAN_LIGHT_LIMIT_REACHED_EXCEPTION_HPP
#define BAUASIAN_LIGHT_LIMIT_REACHED_EXCEPTION_HPP

#include <exception>
#include <boost/filesystem/operations.hpp>


namespace bauasian
{
	class LightLimitReachedException;
}

class bauasian::LightLimitReachedException : public std::runtime_error
{
public:
	LightLimitReachedException(std::string light_type, unsigned max_light_num)
			: std::runtime_error(
			"The limit of " + std::to_string(max_light_num) + " " + light_type + " lights has been reached")
	{}
};

#endif /* BAUASIAN_LIGHT_LIMIT_REACHED_EXCEPTION_HPP */
