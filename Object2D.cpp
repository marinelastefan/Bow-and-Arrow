#include "Object2D.h"
#include "Tema1.h"

#include <Core/Engine.h>



Mesh* Object2D::CreateArrow(std::string name, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 5, 0), color),
		VertexFormat(glm::vec3(30, 5, 0), color),
		VertexFormat(glm::vec3(30, 0, 0), color),
		VertexFormat(glm::vec3(60, 10, 0), color),
        VertexFormat(glm::vec3(30, 20, 0), color),
        VertexFormat(glm::vec3(30, 15, 0), color),
        VertexFormat(glm::vec3(0, 15, 0), color),
        
	};

	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices = { 
        0, 1, 5,
        0, 5, 6,
        2, 3, 4
    };
	
	arrow->SetDrawMode(GL_TRIANGLES);
arrow->InitFromData(vertices, indices);
	return arrow;
}


Mesh* Object2D::CreateBalloonString(std::string name, glm::vec3 color, bool fill) {
       Mesh* balloonString = new Mesh(name);
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(glm::vec3(0, 0, 0), color),
            VertexFormat(glm::vec3(-10, -10, 0), color),
            VertexFormat(glm::vec3(10, -20, 0), color),
            VertexFormat(glm::vec3(-10, -30, 0), color),
            VertexFormat(glm::vec3(10, -40, 0), color),
        };

        std::vector<unsigned short> indices = { 
                0,1,2,3,4
        };
        balloonString->SetDrawMode(GL_LINE_STRIP);
        balloonString->InitFromData(vertices, indices);

        return balloonString;
}
Mesh* Object2D::CreateArrowBow(std::string name, glm::vec3 color, bool fill) {
    Mesh *arrowBow = new Mesh(name);
    std::vector<VertexFormat> vertices;
    std::vector<GLushort> indices;
    GLfloat arg;

    int k = 0;
    	for (GLushort i = 0; i < NUM_TRIANGLES_CIRCLE ; i++) {
			arg = TWO_PI * i  / NUM_TRIANGLES_CIRCLE;
            if (cos(arg) >= 0) {
                vertices.emplace_back(glm::vec3(cos(arg) * BalloonRadius, sin( arg) * BalloonRadius, 0), color);
                indices.push_back(k);
                k++;
            }
		}
	arrowBow->SetDrawMode(GL_LINE_LOOP);
    arrowBow->InitFromData(vertices, indices);
    return arrowBow;

}

Mesh* Object2D::CreateStars(std::string name, glm::vec3 color, bool fill) {
    std::vector<VertexFormat> vertices = 
    {
        VertexFormat(glm::vec3(0, 20, 0), color),
        VertexFormat(glm::vec3(20, 50, 0), color),
        VertexFormat(glm::vec3(40, 20, 0), color),
        VertexFormat(glm::vec3(20, 10, 0), color),
        VertexFormat(glm::vec3(0, 40, 0), color),
        VertexFormat(glm::vec3(40, 40, 0), color)
        
    };

    std::vector<unsigned short> indices = { 
                0,1,2, //triunghi 1
                4,5,3 //triunghi 2
    };
    Mesh* star = new Mesh(name);
    star->SetDrawMode(GL_TRIANGLES);
    star->InitFromData(vertices, indices);
    return star;

}

Mesh* Object2D::CreatePowerBar(std::string name, glm::vec3 color, bool fill) {
    std::vector<VertexFormat> vertices = 
    {
        VertexFormat(glm::vec3(0, 0, 0), color),
        VertexFormat(glm::vec3(5, 0, 0), color),
        VertexFormat(glm::vec3(5, 30, 0), color),
        VertexFormat(glm::vec3(0, 30, 0), color)
    };
    std::vector<unsigned short> indices = { 
                0,1,3,
                1,2,3

    };
    Mesh* powerBar = new Mesh(name);
    powerBar->SetDrawMode(GL_TRIANGLES);
    powerBar->InitFromData(vertices, indices);
    return powerBar;


}

