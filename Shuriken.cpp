#include "Shuriken.h"
#include"Tema1.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include <string>
Shuriken::Shuriken() {
    posShurikenY = rand() % 600;
    posShurikenX = 1280;
    angularStep = 0;
    collisonShuriken = false;
    collisionBow = false;

    

}
Shuriken::~Shuriken() {

}

Mesh* Shuriken::CreateShuriken(std::string name, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices = 
    {
        VertexFormat(glm::vec3(0, 0, 0), color),//0
        VertexFormat(glm::vec3(0, -ShurikenRadius, 0), color), //1 triunghi cadran 4
        VertexFormat(glm::vec3(ShurikenRadius, -ShurikenRadius, 0), color), //2 triunghi cadran 4
        VertexFormat(glm::vec3(ShurikenRadius, 0, 0), color), //3 triunghi cadran 1
        VertexFormat(glm::vec3(ShurikenRadius, ShurikenRadius, 0), color), //4 triunghi cadran 1
        VertexFormat(glm::vec3(0, ShurikenRadius, 0), color), //5 triunghi cadran 2
        VertexFormat(glm::vec3(-ShurikenRadius, ShurikenRadius, 0), color), //6 triunghi cadran 2
        VertexFormat(glm::vec3(-ShurikenRadius, 0, 0), color), //7 triunghi cadran 3
        VertexFormat(glm::vec3(-ShurikenRadius, -ShurikenRadius, 0), color), //8 triunghi cadran 3
    };

    Mesh* shuriken = new Mesh(name);
    std::vector<unsigned short> indices = {
        0, 1, 2, // triunghi cadran 4
        0, 3, 4, // triunghi cadran 1
        0, 5, 6, // triunghi cadran 2
        0, 7, 8 // triunghi cadran 3

    };
    shuriken->SetDrawMode(GL_TRIANGLES);
    shuriken->InitFromData(vertices, indices);
    return shuriken;
}