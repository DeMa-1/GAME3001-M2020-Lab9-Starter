#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"


class Player final : public Sprite
{
public:
	Player(glm::vec2 position);
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void addAbility(Ability*);
	void deleteAbility();
	void useCurrentAbility(int player);
	void changeAbility();


	// setters
	void setAnimationState(PlayerAnimationState new_state);
	virtual std::vector<Ability*> getAbilitiesList() { return m_pListAbilities; };
	virtual int getAbilitiesCounter() { return m_currentAbility; };

protected:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;
	Player* m_pObject;
	bool m_abilityReady = true;
	int m_currentAbility;
	std::vector<Ability *> m_pListAbilities;
};

#endif /* defined (__PLAYER__) */