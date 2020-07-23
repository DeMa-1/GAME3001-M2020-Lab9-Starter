#include "Player.h"
#include "TextureManager.h"

Player::Player(): m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/skeleton.txt",
		"../Assets/sprites/skeleton.png", 
		"skeleton");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("skeleton"));
	
	// set frame width
	setWidth(64);

	// set frame height
	setHeight(64);

	getTransform()->position = glm::vec2(600.0f, 500.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->maxSpeed = 5.0f;
	getRigidBody()->isColliding = false;
	setType(PLAYER);

	m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("skeleton", getAnimation("idle"),
			x, y, 0.45f, 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("skeleton", getAnimation("idle"),
			x, y, 0.45f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;


	case PLAYER_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("skeleton", getAnimation("run"),
			x, y, 0.45f, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance()->playAnimation("skeleton", getAnimation("run"),
			x, y, 0.45f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;


	case PLAYER_RUN_UP:
		TextureManager::Instance()->playAnimation("skeleton", getAnimation("runup"),
			x, y, 0.45f, 0, 255, true);
		break;
	case PLAYER_RUN_DOWN:
		TextureManager::Instance()->playAnimation("skeleton", getAnimation("rundown"),
			x, y, 0.45f, 0, 255, true);
		break;

	default:
		break;
	}
	
}

void Player::update()
{
}

void Player::clean()
{
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();
	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-idle-1"));	
	setAnimation(idleAnimation);

	Animation runAnimation = Animation();
	runAnimation.name = "run";
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-right-2"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-right-3"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-right-4"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-right-5"));
	setAnimation(runAnimation);

	Animation runupAnimation = Animation();
	runupAnimation.name = "runup";
	runupAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-up-1"));
	runupAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-up-3"));
	runupAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-up-4"));
	runupAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-up-6"));
	runupAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-up-7"));
	runupAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-up-8"));
	setAnimation(runupAnimation);

	Animation rundownAnimation = Animation();
	rundownAnimation.name = "rundown";
	rundownAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-down-1"));
	rundownAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-down-3"));
	rundownAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-down-4"));
	rundownAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-down-6"));
	rundownAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-down-7"));
	rundownAnimation.frames.push_back(getSpriteSheet()->getFrame("skel-down-8"));
	setAnimation(rundownAnimation);

}
