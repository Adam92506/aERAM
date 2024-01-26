#include "erpch.h"
#include "Utils.h"

#include <ShlObj.h>
#include <GLFW/glfw3.h>

namespace Eram
{

	// Move to platform dependant
	float Time::GetTime()
	{
		return (float)glfwGetTime();
	}

	namespace Utils
	{

		std::string ReadFile(const std::string filepath)
		{
			ER_PROFILE_FUNCTION();

			std::string result;
			std::ifstream in(filepath, std::ios::in | std::ios::binary);

			if (in)
			{
				in.seekg(0, std::ios::end);
				size_t size = in.tellg();
				if (size != -1)
				{
					result.resize(size);
					in.seekg(0, std::ios::beg);
					in.read(&result[0], size);
				}
				else
				{
					ER_ERROR("Could not read from file '{0}'", filepath);
				}
			}
			else
			{
				ER_ERROR("Could not open file '{0}'", filepath);
			}

			return result;
		}

	}

}