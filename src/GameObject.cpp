#include "GameObject.h"

GameObject::GameObject() :
	m_width(0), m_height(0), m_type(NONE)
{
}

GameObject::~GameObject()
= default;

Transform* GameObject::getTransform()
{
	return &m_transform;
}

RigidBody* GameObject::getRigidBody()
{
	return &m_rigidBody;
}

int GameObject::getWidth() const
{
	return m_width;
}

int GameObject::getHeight() const
{
	return m_height;
}

GameObjectType GameObject::getType() const
{
	return m_type;
}

void GameObject::setWidth(const int new_width)
{
	m_width = new_width;
}

void GameObject::setHeight(const int new_height)
{
	m_height = new_height;
}

void GameObject::setPosX(int new_posX)
{
	m_posX = new_posX;
}

void GameObject::setPosY(int new_posY)
{
	m_posY = new_posY;
}

void GameObject::setType(const GameObjectType new_type)
{
	m_type = new_type;
}