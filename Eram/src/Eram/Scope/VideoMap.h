#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Eram
{

	class VideoMap
	{
	public:
		VideoMap() = default;
		VideoMap(const std::string& filePath);

		void Draw();
	private:
		void ParseGeoJson(const std::string& filePath);
		glm::vec2 GetVec2(json& array);
	private:
		std::string m_Name;

		std::vector<std::pair<glm::vec2, glm::vec2>> m_Lines;
	};

}