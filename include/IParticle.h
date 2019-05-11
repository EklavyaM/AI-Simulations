#pragma once

#include <SFML/Graphics.hpp>

#include "ISimulatable.h"
#include "ITransformable.h"

class IParticle : public ISimulatable, public ITransformable
{
public:
    virtual ~IParticle() {}
    virtual void setColor(sf::Color &color) = 0;
};
