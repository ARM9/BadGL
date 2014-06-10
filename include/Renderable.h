#pragma once

class Renderable
{
public:
	virtual ~Renderable() {}
	virtual void render(float dt) = 0;
	virtual void update() = 0;
};
