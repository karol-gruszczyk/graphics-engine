#ifndef LIGHT_LIMIT_REACHED_EXCEPTION_HPP_
#define LIGHT_LIMIT_REACHED_EXCEPTION_HPP_

#include <exception>
#include <boost/filesystem/operations.hpp>


namespace engine
{
	class LightLimitReachedException;
}

class engine::LightLimitReachedException : public std::runtime_error
{
public:
	LightLimitReachedException(std::string light_type, unsigned max_light_num)
		: std::runtime_error("The limit of " + std::to_string(max_light_num) + " " + light_type + " lights has been reached")
	{}
};

#endif /* LIGHT_LIMIT_REACHED_EXCEPTION_HPP_ */
