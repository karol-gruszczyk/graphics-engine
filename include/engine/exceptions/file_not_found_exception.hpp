#ifndef GRAPHICS_ENGINE_FILE_NOT_FOUND_EXCEPTION_HPP
#define GRAPHICS_ENGINE_FILE_NOT_FOUND_EXCEPTION_HPP

#include <exception>
#include <boost/filesystem/operations.hpp>


namespace engine
{
	class FileNotFoundException;
}

class engine::FileNotFoundException : public std::runtime_error
{
public:
	FileNotFoundException(boost::filesystem::path path)
			: std::runtime_error("The file '" + toAbsolutePath(path) + "' could not be found")
	{}

private:
	std::string toAbsolutePath(boost::filesystem::path path)
	{
		if (path.is_absolute())
			return path.string();
		auto absolute_path = boost::filesystem::current_path();
		for (auto& subpath : path)
		{
			if (subpath == "..")
				absolute_path.remove_leaf();
			else if (subpath == ".")
				continue;
			else
				absolute_path /= subpath;
		}
		return absolute_path.string();
	}
};

#endif /* GRAPHICS_ENGINE_FILE_NOT_FOUND_EXCEPTION_HPP */
