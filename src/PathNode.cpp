#include "PathNode.h"
#include "CollisionManager.h"

PathNode::PathNode()
	:m_bLOS(false)
{
	setWidth(Config::TILE_SIZE);
	setHeight(Config::TILE_SIZE);
	setType(PATH_NODE);
}

PathNode::~PathNode()
= default;

void PathNode::draw()
{
}

void PathNode::update()
{
	/*CollisionManager::LOSCheck()*/
}

void PathNode::clean()
{
}

void PathNode::setLOS(const bool LOS)
{
	m_bLOS = LOS;
}

const bool PathNode::getLOS()
{
	return m_bLOS;
}

