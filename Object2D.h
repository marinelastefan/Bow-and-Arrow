#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>


namespace Object2D
{

	// Create square with given bottom left corner, length and color
    Mesh* CreateArrow(std::string name, glm::vec3 color, bool fill = false);
    Mesh* CreateBalloonString(std::string name, glm::vec3 color, bool fill = false);
    Mesh* CreateArrowBow(std::string name, glm::vec3 color, bool fill = false);
    Mesh* CreateStars(std::string name, glm::vec3 color, bool fill = false);
    Mesh* CreatePowerBar(std::string name, glm::vec3 color, bool fill = false);

}