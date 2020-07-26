#include "Melee.h"

Melee::Melee()
{
	m_running = false;
	m_pDamage = 30;

	TextureManager::Instance()->load("../Assets/textures/swordSilver.png", "sword");


	setWidth(30);
	setHeight(30);
	getRigidBody()->isColliding = false;


	setType(PLAYERABILITY);
}

Melee::~Melee()
{

}

Melee::Melee(glm::vec2 position, bool running, int angle, bool pickable, bool secondAbility)
{
	m_angle = angle;
	m_running = running;
	m_pickable = pickable;
	m_pDamage = 30;

	TextureManager::Instance()->load("../Assets/textures/swordSilver.png", "sword");

	getTransform()->position = position;
	getRigidBody()->velocity += 0;
	glm::vec2 direction = { cos(m_angle * M_PI / 180.0) , sin(m_angle * M_PI / 180.0) };
	getRigidBody()->velocity *= direction;

	setWidth(30);//for collision
	setHeight(30);
	getRigidBody()->isColliding = false;

	if (m_pickable) {
		setType(PICKABLE);
	}
	else {
		getTransform()->position += (50.0f * direction);
		if (secondAbility) {
			setType(SECONDABILITY);
		}
		else {
			setType(PLAYERABILITY);
		}
	}
	start();
}

void Melee::update()
{
	setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);
}

void Melee::draw()
{
	if (m_running) {
		TextureManager::Instance()->draw("sword", getTransform()->position.x, getTransform()->position.y, m_angle + 90, 255, true);
	}
}

void Melee::clean()
{
}

void Melee::start()
{
	if (m_pickable)
	{
		sound();
	}
}

void Melee::execute(glm::vec2 position, int angle, bool secondAbility)
{
	Game::Instance()->getCurrentScene()->addChild(new Melee(position, true, angle, false, secondAbility));
	SoundManager::Instance().playSound("Sword");

}

void Melee::stop()
{
}

void Melee::sound()
{
}

void Melee::animation()
{
}

void Melee::pickable(glm::vec2 position)
{
}
