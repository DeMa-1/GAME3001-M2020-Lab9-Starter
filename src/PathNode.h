#pragma once
#ifndef _PATH_NODE_
#define _PATH_NODE_

#include "GameObject.h"

class PathNode : GameObject
{
public:
	PathNode();
	~PathNode();

	// Inherited via GameObject
	//LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setLOS(bool LOS);
	bool const getLOS();

private:
	bool m_bLOS;
};
#endif