#pragma once

#include <Core/Engine.h>
#include <string>

class Balloon {
    public: 
        Balloon();
        ~Balloon();

        Mesh* CreateBalloon(std::string name, glm::vec3 color, bool fill = false);
        

        float balloonPositionX;
        float balloonPositionY;
        float scaleXBalloon, scaleYBalloon;
        bool colisionBalloon;
        bool isRed;
        float baloonString;
        float posXstring, posYString;
        


};
