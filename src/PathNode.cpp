#include "PathNode.h"
#include "CollisionManager.h"

PathNode::PathNode()
	:m_bLOS(false)
{
	setWidth(40);
	setHeight(40);
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

