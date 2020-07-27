#pragma once
#ifndef _ABILITY_
#define _ABILITY_
#include "DisplayObject.h"
#include "Sprite.h"

class Ability : public DisplayObject
{
public:
	Ability();
	virtual ~Ability();

	virtual void draw() override = 0;
	virtual void update() override = 0;
	virtual void clean() override = 0;

	virtual void execute(glm::vec2 position, int angle, bool secondAbility) = 0;
	virtual void stop();
	virtual void sound();
	virtual void animation();
	virtual void pickable(glm::vec2 position) = 0;

	bool& getAbilityDone() { return m_abilityDone; }
	bool& IsRunning() { return m_running; }
	virtual Ability* getAbility() = 0;

protected:
	std::unordered_map<std::string, Animation> m_pAnimations;
	bool m_abilityDone = false;
	bool m_running = false;
	bool m_pickable = false;
	int m_angle;
	int m_pLife;
	int m_pDamage;


};

#endif
