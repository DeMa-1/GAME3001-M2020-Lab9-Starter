#pragma once
#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Transform.h"
#include "RigidBody.h"
#include <string>
#include "GameObjectType.h"
#include <vector>

class GameObject 
{
public:
	GameObject();
	virtual ~GameObject();

	// Draw the object
	virtual void draw() = 0;

	// Update the object
	virtual void update() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	Transform* getTransform();

	// getters and setters for physics properties
	RigidBody* getRigidBody();

	// getters and setters for game object properties
	int getWidth() const;
	int getHeight() const;
	int getPosx() const;
	int getPosY() const;
	int getAngle() const;
	void setWidth(int new_width);
	void setHeight(int new_height);
	void setPosX(int new_posX);
	void setPosY(int new_posY);
	void getAngle(int new_angle);
	GameObjectType getType() const;
	void setType(GameObjectType new_type);

protected:
	// transform component
	Transform m_transform;

	// rigid body component
	RigidBody m_rigidBody;

	// size variables
	int m_width;
	int m_height;
	int m_posX;
	int m_posY;
	int m_angle;
	int m_pLife;
	int m_pDamage;
	GameObject* m_currentObject;
	GameObjectType m_type;


};

#endif /* defined (__GAME_OBJECT__) */