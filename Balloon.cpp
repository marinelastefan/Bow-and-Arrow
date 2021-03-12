#include "Balloon.h"
#include"Tema1.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include <string>

Balloon::Balloon()  
    {
        balloonPositionY = 0;
        posYString = balloonPositionY -  BalloonRadius;
        // am facut ca pe ox sa mi apara pe ecran intre 300 si 1200 baloanele
        balloonPositionX = rand() % (1200 + 1 - 300) + 300;
        posXstring  = balloonPositionX;
  
        

    }
Balloon::~Balloon()
{

}

Mesh* Balloon::CreateBalloon(std::string name, glm::vec3 color, bool fill) {
    std::vector<VertexFormat> vertices;
    std::vector<GLushort> indices;
    GLfloat arg;
    vertices.emplace_back(glm::vec3(0, 0, 0), color);
    	for (GLushort i = 0; i < NUM_TRIANGLES_CIRCLE; i++) {
			arg = TWO_PI * i  / NUM_TRIANGLES_CIRCLE;
            float x = BalloonRadius * cos(arg);
            float y = BalloonRadius * sin( arg);
			vertices.emplace_back(glm::vec3( x , y, 0), color);
			indices.push_back(i);
		}
		indices.push_back(50);
		indices.push_back(1);

        // pentru triunghiul de jos de care se prinde sfoara
        arg = TWO_PI * 38 / 50;
        vertices.emplace_back(glm::vec3( -10, BalloonRadius * sin( arg) - 10, 0), color);
        vertices.emplace_back(glm::vec3( 10, BalloonRadius * sin( arg) - 10, 0), color);
        indices.push_back(51);
        indices.push_back(52);
        

        Mesh* balloon = new Mesh(name);
        balloon->SetDrawMode(GL_TRIANGLE_FAN);
        balloon->InitFromData(vertices, indices);
        return balloon;
}