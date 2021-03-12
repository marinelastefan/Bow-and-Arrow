#pragma once

#include <Core/Engine.h>
class Shuriken {
    public: 
        Shuriken();
        ~Shuriken();
        Mesh* CreateShuriken(std::string name, glm::vec3 color, bool fill = false);
        float posShurikenX;
        float posShurikenY;
        bool collisonShuriken;
        bool collisionBow;
        float angularStep;

};