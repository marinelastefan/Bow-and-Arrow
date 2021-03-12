#include "Tema1.h"

#include <vector>
#include <iostream>
#include<cmath>

#include <Core/Engine.h>
#include "Transform2D.h"
#include"Balloon.h"
#include "Object2D.h"
#include "Shuriken.h"

using namespace std;

bool mouseMoved = false;
int speedShuriken = 30;
int speedBalloon = 50;
bool mouseClicked = false;
float angleToMove = 0;
float lengthX, lengthY;
int timesOfShurikenColision = 0;
int timesOfBowCollision = 0;
float speedArrow = 150;
bool hasAlreadyBeenIncreased = false;
int aux = 0;

Tema1::Tema1()
{

}
Tema1::~Tema1()
{

}
void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);


	/*translateYBalloon = 0;
	translateXBalloon = 600;*/
	//translateYBalloonString = translateYBalloon - 60;
	translateYBalloonString = 60;


	translateXArrow = BeginPositionArrowX;
	translateYArrow = BeginPositionArrowY;

	translateXBowArrow = BeginPositionArrowX;
	translateYBowArrow = BeginPositionArrowY;

	angleArrow = 0;
	scaleXBalloon = 0;
	scaleYBalloon = 0;

	scalePowerBar = 1;

	score = 0;
	star1 = false;
	star2 = false;
	whichShuriken = -1;



    Mesh* arrow = Object2D::CreateArrow("arrow", glm::vec3(255, 255, 255), true);
	AddMeshToList(arrow);
	
	Shuriken shuriken;
	Mesh* shurikenMesh = shuriken.CreateShuriken("shuriken", glm::vec3(0, 0, 255), true);
	AddMeshToList(shurikenMesh);

	Balloon balloon;
	Mesh* balloonMesh = balloon.CreateBalloon("balloonRedMesh",glm::vec3(255, 0, 0), true);
	AddMeshToList(balloonMesh);

	Balloon balloonY;
	Mesh* balloonMeshY = balloonY.CreateBalloon("balloonYelMesh",glm::vec3(255, 255, 0), true);
	AddMeshToList(balloonMeshY);


	Mesh* balloonString = Object2D::CreateBalloonString("balloonString", glm::vec3(255, 0, 0 ), true);
	AddMeshToList(balloonString);

	Mesh* yellowString = Object2D::CreateBalloonString("yellowString", glm::vec3(255, 255, 0 ), true);
	AddMeshToList(yellowString);

	
	Mesh* arrowBow = Object2D::CreateArrowBow("arrowBow", glm::vec3(255, 255, 255), true);
	AddMeshToList(arrowBow);

	Mesh* star = Object2D::CreateStars("star", glm::vec3(255, 255, 0), true);
	AddMeshToList(star);

	Mesh* powerBar = Object2D::CreatePowerBar("powerBar",glm::vec3(0, 255, 0), true);
	AddMeshToList(powerBar);
	

}

void Tema1::FrameStart()
{
    // clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}
void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// adaug  bara pentru viteza
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(100, 50);
	modelMatrix *= Transform2D::Scale(scalePowerBar, 1);
	RenderMesh2D(meshes["powerBar"], shaders["VertexColor"], modelMatrix);
  
	// arcul
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXBowArrow, translateYBowArrow);
	if (mouseMoved == true) {
		modelMatrix *= Transform2D::Rotate(angleArrow);
	}
	RenderMesh2D(meshes["arrowBow"], shaders["VertexColor"], modelMatrix);

	// sageata
	modelMatrix = glm::mat3(1);
	// daca sageata iese din ecran, o readuc la arc
	if (translateXArrow > resolution.x || translateXArrow < 0 
				|| translateYArrow < 0 || translateYArrow > resolution.y) {
					translateXArrow = translateXBowArrow;
					translateYArrow = translateYBowArrow;
					mouseClicked = false;
					scalePowerBar = 1;
				}

    modelMatrix *= Transform2D::Translate(translateXArrow, translateYArrow);
	if (mouseMoved == true) {
		if (mouseClicked == false)
			modelMatrix *= Transform2D::Rotate(angleArrow);
		else 
			modelMatrix *= Transform2D::Rotate(angleToMove);
	}
	// miscare sub unghi
	if (mouseClicked == true) {
		translateXArrow  +=  speedArrow * deltaTimeSeconds * cos(angleToMove);
		translateYArrow  +=  speedArrow * deltaTimeSeconds * sin(angleToMove);
	}
	RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);

	// daca sageata a fost lansata sub unghi aflu cat trebuie sa adaug pentru
	// a ajunge in varful sagetii
	if(angleToMove != 0) {
		lengthX = sqrt((1 - sin(angleToMove) * sin(angleToMove)) * LengthX * LengthX);
		lengthY = sqrt(LengthX * LengthX - lengthX * lengthX);

	} else {
		lengthX = LengthX;
		lengthY = LengthY; 
	}


	aux++;
	if (aux > 200) {
		balloons.push_back(Balloon());
		shuriken.push_back(Shuriken());
		if (balloons.size() % 2 == 0) {
			balloons[balloons.size() - 1].isRed = true;
			
		}
		aux = 0;
	}
	vector<int> redBalloonsCollision;
	vector<int> yellowBalloonCollsion;
	vector<int> shurikenCollision;
	for (int i = 0; i < balloons.size() ; i++) {
		modelMatrix = glm::mat3(1);
		modelMatrix2 = glm::mat3(1);
		balloons[i].balloonPositionY += deltaTimeSeconds * speedBalloon;
		modelMatrix *= Transform2D::Translate(balloons[i].balloonPositionX,balloons[i].balloonPositionY);
		if (CheckBalloonColision(balloons[i].balloonPositionX , balloons[i].balloonPositionY, translateXArrow + lengthX, translateYArrow + lengthY)) {
				balloons[i].colisionBalloon = true;
		}
		balloons[i].posYString  += deltaTimeSeconds * speedBalloon;
		shuriken[i].angularStep += deltaTimeSeconds;
		shuriken[i].posShurikenX -= speedShuriken * deltaTimeSeconds;
		modelMatrix2 *= Transform2D::Translate(balloons[i].posXstring, balloons[i].posYString);
		if (balloons[i].colisionBalloon) {
			modelMatrix *= Transform2D::Scale(scaleXBalloon, scaleYBalloon);
			modelMatrix2 *= Transform2D::Scale(scaleXBalloon, scaleYBalloon);
			balloons[i].colisionBalloon = true;
			
		}
		if(balloons[i].colisionBalloon == true && balloons[i].isRed == true) {
			redBalloonsCollision.push_back(i);
		}
		if (balloons[i].colisionBalloon == true && balloons[i].isRed == false) {
			yellowBalloonCollsion.push_back(i);
		}
	
		modelMatrix *= Transform2D::Scale(0.75f, 1);

		if (balloons[i].isRed == true) {
			RenderMesh2D(meshes["balloonRedMesh"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["balloonString"], shaders["VertexColor"], modelMatrix2);
		}
		else {
			RenderMesh2D(meshes["balloonYelMesh"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["yellowString"], shaders["VertexColor"], modelMatrix2);

		}
		modelMatrix3 = glm::mat3();
		modelMatrix3 *= Transform2D::Translate(shuriken[i].posShurikenX, shuriken[i].posShurikenY);
		modelMatrix3 *= Transform2D::Rotate(shuriken[i].angularStep);
		if (CheckShurikenCollison(translateXArrow + lengthX, translateYArrow + lengthY, shuriken[i].posShurikenX, shuriken[i].posShurikenY)) 
			shuriken[i].collisonShuriken = true;
      	if (shuriken[i].collisonShuriken == true) {
			modelMatrix3 *= Transform2D::Scale(0,0);
			shurikenCollision.push_back(i);
		}
		if(CheckBowShurikenCollison(shuriken[i].posShurikenX, shuriken[i].posShurikenY, translateXBowArrow, translateYBowArrow) == true) {
			if(star1 == false ) {
				star1 = true;
				whichShuriken = i;

			} else {
				if (whichShuriken != i && star2 == false) {
					star2 = true;
					whichShuriken2 = i;
				} else
				{
					if(star2 == true && whichShuriken2 != i) {
						printf("GAME OVER\n");
						std::exit(1);
					}
				}
				

			}
		}
			
		RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix3);

		modelMatrix4 = glm::mat3(1);
		modelMatrix5 = glm::mat3(1);
		modelMatrix6 = glm::mat3(1);
		modelMatrix4 *= Transform2D::Translate( resolution.x - 200, 50);
		if (star1 == true)
			modelMatrix4 *= Transform2D::Scale(0,0);
		RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix4);
		if (star2 == true)
			modelMatrix5 *= Transform2D::Scale(0,0);
		modelMatrix5 *= Transform2D::Translate(resolution.x - 250 , 50);
		RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix5);
		modelMatrix6 *= Transform2D::Translate(resolution.x - 300, 50);
		RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix6);

	}
	int scoreUpdated =  redBalloonsCollision.size() - yellowBalloonCollsion.size() + shurikenCollision.size();
	if (scoreUpdated != score) {
		printf("SCORE %d\n", scoreUpdated);
		score = scoreUpdated;
	}
	




}
void Tema1::FrameEnd()
{

}
void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		translateYArrow += deltaTime * 50;
		translateYBowArrow += deltaTime * 50;
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		translateYArrow -= deltaTime * 50;
		translateYBowArrow -= deltaTime * 50;
	}
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		if (speedArrow <= LIMIT_SPEED_ARROW) {
			speedArrow += MOVE_RATIO_ARROW * deltaTime;
			scalePowerBar += 10 * deltaTime;
		}

	}

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	glm::ivec2 resolution = window->GetResolution();
	// add mouse move event
	mouseMoved = true;
	angleArrow = atan2(resolution.y - mouseY - translateYBowArrow, mouseX- translateXBowArrow);
	
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	mouseClicked = true;
	angleToMove = angleArrow;


}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

GLboolean Tema1::CheckBalloonColision(int xBalloon, int yBalloon, int xArrow, int yArrow) {
	float dx = xBalloon - xArrow;
	float dy = yBalloon - yArrow;
	float distance = sqrt(dx * dx  + dy * dy);
	return distance < BalloonRadius;
}

GLboolean Tema1::CheckShurikenCollison(float xArrow, float yArrow, float xShuriken, float yShuriken) {
	float dx = xShuriken - xArrow;
	float dy = yShuriken - yArrow;
	float distance = sqrt(dx * dx + dy * dy);
	return distance < ShurikenRadius;
}
GLboolean Tema1::CheckBowShurikenCollison(float xShuriken, float yShuriken, float xBow, float yBow) {
	float dx = xShuriken - xBow;
	float dy = yShuriken - yBow;
	float distance = sqrt(dx * dx + dy * dy);
	return distance < BowRadiusX + ShurikenRadius;
}
