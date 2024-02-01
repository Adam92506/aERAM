#include "erpch.h"
#include "VideoMap.h"

#include "Eram/Renderer/Renderer.h"

namespace Eram
{

	VideoMap::VideoMap(const std::string& filePath)
	{
		ParseGeoJson(filePath);
	}

	void VideoMap::Draw()
	{
		for (auto& line : m_Lines)
		{
			Renderer::DrawLine(line.first, line.second, { 0.2f, 0.2f, 0.2f, 1.0f });
		}
	}

	void VideoMap::ParseGeoJson(const std::string& filePath)
	{
		// Load File

		std::ifstream stream(filePath);

		if (stream.fail())
		{
			ER_ERROR("Unable to load file: {0}", filePath.c_str());
			
			return;
		}

		// Parse Json

		json data = json::parse(stream);

		// Validate Format

		if (!data.contains("features"))
		{
			ER_ERROR("Invalid GeoJson format: {0}", filePath.c_str());

			return;
		}

		if (!data.contains("name"))
			m_Name = "Untitled";
		else
			m_Name = data["name"];

		// Get Data

		for (auto& feature : data["features"])
		{
			if (feature.contains("geometry"))
			{
				if (feature["geometry"]["type"] == "LineString")
				{
					auto& coordinates = feature["geometry"]["coordinates"];

					if (coordinates.size() == 2)
					{
						m_Lines.push_back({ GetVec2(coordinates[0]), GetVec2(coordinates[1]) });
					}

					else
					{
						for (uint32_t i = 0; i < coordinates.size() - 1; i++)
						{
							m_Lines.push_back({ GetVec2(coordinates[i]), GetVec2(coordinates[i + 1]) });
						}
					}
				}
			}
		}

		ER_TRACE("Loaded Video Map: {0}", m_Name.c_str());
	}

	glm::vec2 VideoMap::GetVec2(json& array)
	{
		glm::vec2 coordinate;

		coordinate.x = array[0].template get<float>();
		coordinate.y = array[1].template get<float>();

		return coordinate;
	}

}