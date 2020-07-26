#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Player.h"
#include "Plane.h"
#include "Button.h"
#include "Obstacle.h"
#include "DebugKeys.h"
#include "PathNode.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	//PRIVATE FUNCTIONS
	void m_buildGrid();
	void m_displayGrid();
	void m_displayGridLOS();
	void m_setGridLOS();

	//MEMBER VARIABLES
	glm::vec2 m_mousePosition;

	Plane* m_pPlaneSprite;
	Player* m_pPlayer;
	bool m_playerFacingRight;
	bool m_playerFacingUp;
	Obstacle* m_pObstacle;

	bool m_bDebugMode;
	bool m_bPatrolMode;
	bool m_bDebugKeys[NUM_OF_DEBUG_KEYS];

	std::vector<PathNode*> m_pGrid;
	//Lab 9 code above. Lab 10 added code below
	std::vector<PathNode*> m_pPatrolPath;
	void m_buildPatrolPath();
	void m_displayPatrolPath();
	void m_movePlanetoTargetNode();
	int m_targetPathNodeIndex;
	PathNode* m_pTargetPathNode;
	

};

#endif