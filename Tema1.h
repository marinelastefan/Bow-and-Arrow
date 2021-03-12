#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include"Balloon.h"
#include"Shuriken.h"

#define PI  (3.14159292035f)
#define TWO_PI (6.28318530718f)
#define LengthX (60)
#define LengthY (10)
#define BalloonRadius (60)
#define BowRadiusX (60)
#define BalloonRadiusY (50)
#define ShurikenRadius (30.0f)
#define MOVE_RATIO_ARROW (100)
#define LIMIT_SPEED_ARROW (600)
#define BeginPositionArrowX  (50)
#define BeginPositionArrowY  (300)
#define NUM_TRIANGLES_CIRCLE 50

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		GLboolean CheckBalloonColision(int xBalloon, int yBalloon, int xArrow, int yArrow);
		GLboolean CheckShurikenCollison(float xArrow, float yArrow, float xShuriken, float yShuriken);
		GLboolean CheckBowShurikenCollison(float xShuriken, float yShuriken, float xBow, float yBow);

	protected:
		glm::mat3 modelMatrix, modelMatrix2, modelMatrix3, modelMatrix4,modelMatrix5, modelMatrix6;
		float translateYBalloonString;
		float translateYBowArrow,translateXBowArrow;
		float translateXArrow, translateYArrow;
		float angleArrow = 0;
		float scaleXBalloon, scaleYBalloon;
		float scalePowerBar;
		int score;
		std::vector<Balloon> balloons;
		std::vector<Shuriken> shuriken;
		bool star1, star2;
		int whichShuriken, whichShuriken2;
};
