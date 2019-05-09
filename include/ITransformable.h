#pragma once

class ITransformable
{
public:
    virtual void setPosition(int x, int y) = 0;
    virtual void setSize(int width, int height) = 0;
};