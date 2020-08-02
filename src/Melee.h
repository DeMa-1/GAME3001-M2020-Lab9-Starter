#pragma once
#ifndef _MELEE_
#define _MELEE_

#include "Ability.h"
#include "Game.h"

class Melee : public Ability
{
public:
	Melee();
	~Melee();
	Melee(glm::vec2 position, bool running, int angle, bool pickable, bool secondAbility);
	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;

	void start();
	void execute(glm::vec2 position, int angle, bool secondAbility);
	void stop();
	void sound();
	void animation();
	void pickable(glm::vec2 position);

	Melee* getAbility() override { return new Melee(); }


	
};

#endif