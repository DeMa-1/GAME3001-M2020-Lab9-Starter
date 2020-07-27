#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"
#include <array>
#include <map>

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();

	if (m_bDebugMode)
	{
		//Line used to show if collision between obstacle and player
		Util::DrawLine(m_pPlayer->getTransform()->position, m_pObstacle->getTransform()->position);

		//Line used to show if collision between ship and player
		Util::DrawLine(m_pPlayer->getTransform()->position, m_pPlaneSprite->getTransform()->position);

		//Below is Debug box for the player
		Util::DrawRect(m_pPlayer->getTransform()->position - glm::vec2(m_pPlayer->getWidth() * 0.5f, m_pPlayer->getHeight() * 0.5f), m_pPlayer->getWidth(), m_pPlayer->getHeight());

		////Below is Debug box for the plane
		Util::DrawLine(m_pPlaneSprite->getTransform()->position, m_pPlaneSprite->getTransform()->position);
		Util::DrawRect(m_pPlaneSprite->getTransform()->position - glm::vec2(m_pPlaneSprite->getWidth() * 0.5f, m_pPlaneSprite->getHeight() * 0.5f), m_pPlaneSprite->getWidth(), m_pPlaneSprite->getHeight());

		//Below is Dubeg box for the Obstacle
		Util::DrawLine(m_pObstacle->getTransform()->position, m_pObstacle->getTransform()->position);
		Util::DrawRect(m_pObstacle->getTransform()->position - glm::vec2(m_pObstacle->getWidth() * 0.5f, m_pObstacle->getHeight() * 0.5f), m_pObstacle->getWidth(), m_pObstacle->getHeight());

		m_displayGrid();
		m_displayGridLOS();
		
	}
	
	
}

void PlayScene::update()
{
	updateDisplayList();

	CollisionManager::LOSCheck(m_pPlayer, m_pPlaneSprite, m_pObstacle);
	CollisionManager::AABBCheck(m_pPlayer, m_pPlaneSprite);
	CollisionManager::AABBCheck(m_pPlayer, m_pObstacle);

	m_setGridLOS();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				/*m_pPlayer->getRigidBody()->velocity = glm::vec2(5.0f, 0.0f);*/
				m_pPlayer->getTransform()->position.x += m_pPlayer->getRigidBody()->velocity.x;
				m_pPlayer->getRigidBody()->velocity.x *= m_pPlayer->getRigidBody()->velocity.x * 0.9f;
				m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				/*m_playerFacingRight = true;*/
				
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < deadZone)
			{
			/*	m_pPlayer->getRigidBody()->velocity = glm::vec2(-5.0f, 0.0f);*/
				m_pPlayer->getTransform()->position.x += m_pPlayer->getRigidBody()->velocity.x;
				m_pPlayer->getRigidBody()->velocity.x *= m_pPlayer->getRigidBody()->velocity.x * 0.9f;
				m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				/*m_playerFacingRight = false;*/
			}
			else
			{
				if (m_playerFacingRight)
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}
			
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y > deadZone)
			{
				/*m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, -5.0f);*/
				m_pPlayer->getTransform()->position.y += m_pPlayer->getRigidBody()->velocity.y;
			    m_pPlayer->getRigidBody()->velocity.y *= m_pPlayer->getRigidBody()->velocity.y * 0.9f;
				m_pPlayer->setAnimationState(PLAYER_RUN_UP);
				/*m_playerFacingRight = true;*/

			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y < deadZone)
			{
				/*m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, 5.0f);*/
				m_pPlayer->getTransform()->position.y += m_pPlayer->getRigidBody()->velocity.y;
				m_pPlayer->getRigidBody()->velocity.y *= m_pPlayer->getRigidBody()->velocity.y * 0.9f;
				m_pPlayer->setAnimationState(PLAYER_RUN_DOWN);
				/*m_playerFacingRight = false;*/
			}
		}
	}
	
	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;

			m_pPlayer->getRigidBody()->velocity = glm::vec2(-5.0f, 0.0f);
			m_pPlayer->getTransform()->position += m_pPlayer->getRigidBody()->velocity;
			m_pPlayer->getRigidBody()->velocity *= m_pPlayer->getRigidBody()->velocity * 0.9f;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;

			m_pPlayer->getRigidBody()->velocity = glm::vec2(5.0f, 0.0f);
			m_pPlayer->getTransform()->position += m_pPlayer->getRigidBody()->velocity;
			m_pPlayer->getRigidBody()->velocity *= m_pPlayer->getRigidBody()->velocity * 0.9f;
		}
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				m_playerFacingRight = true;

			}
			else
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				m_playerFacingRight = false;
			}
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_UP);
			m_playerFacingUp = true;

			m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, -5.0f);
			m_pPlayer->getTransform()->position += m_pPlayer->getRigidBody()->velocity;
			m_pPlayer->getRigidBody()->velocity *= m_pPlayer->getRigidBody()->velocity * 0.9f;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_DOWN);
			m_playerFacingUp = false;

			m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, 5.0f);
			m_pPlayer->getTransform()->position += m_pPlayer->getRigidBody()->velocity;
			m_pPlayer->getRigidBody()->velocity *= m_pPlayer->getRigidBody()->velocity * 0.9f;
		}
	
		
	}

	//Change Ability
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_N))
	{
			m_pPlayer->changeAbility();
	}
	//Use Current Ability
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_M))
	{
		m_pPlayer->useCurrentAbility(1);
	}

	//H Key Section
	if (!m_bDebugKeys[H_KEY])
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_H))
		{
			//Toggles debugmode
			m_bDebugMode = !m_bDebugMode;
			m_bDebugKeys[H_KEY] = true;

			if (m_bDebugMode)
			{
				std::cout << "DEBUG MODE: ON" << std::endl;
			}
			else
			{
				std::cout << "DEBUG MODE: OFF" << std::endl;
			}

		}
	}
	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_H))
	{
		m_bDebugKeys[H_KEY] = false;
	}

	// K Key Section 
	if (!m_bDebugKeys[K_KEY])
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_K))
		{
			std::cout << "DEBUG: Enemies taking damage" << std::endl;
			m_bDebugKeys[K_KEY] = true;
		}
	}
	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_K))
	{
		m_bDebugKeys[K_KEY] = false;
	}

	// P Key Section
	if (!m_bDebugKeys[P_KEY])
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_P))
		{
			//Toggles Patrolmode
			m_bPatrolMode = !m_bPatrolMode;
			m_bDebugKeys[P_KEY] = true;

			if (m_bPatrolMode)
			{
				std::cout << "DEBUG: PATROL MODE ON" << std::endl;
			}
			else
			{
				std::cout << "DEBUG: PATROL MODE OFF" << std::endl;
			}

		}
	}
	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_P))
	{
		//movePlanetoTargetNode must be in here because when key pressed and released the plane animation will play as long as P is not pressed again. 
		//If in isKeyDown then it will only show 1 frame for each button press
		m_movePlanetoTargetNode();
		m_bDebugKeys[P_KEY] = false;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		Game::Instance()->changeSceneState(END_SCENE);
	}
}


void PlayScene::m_movePlanetoTargetNode()
{
	if (m_bPatrolMode)
	{
		m_pTargetPathNode = m_pPatrolPath[m_targetPathNodeIndex];
		auto targetVector = Util::normalize(m_pTargetPathNode->getTransform()->position - m_pPlaneSprite->getTransform()->position);

		//rotate Plane according to the direction of travel
		//x-axis
		if (targetVector.x == 1)
		{
			m_pPlaneSprite->setAngle(90.0f);
		}
		else if (targetVector.x == -1)
		{
			m_pPlaneSprite->setAngle(-90.0f);
		}
		//y-axis
		if (targetVector.y == 1)
		{
			m_pPlaneSprite->setAngle(180.0f);
		}
		else if (targetVector.y == -1)
		{
			m_pPlaneSprite->setAngle(0.0f);
		}

		m_pPlaneSprite->getRigidBody()->velocity = targetVector;
		m_pPlaneSprite->getTransform()->position += m_pPlaneSprite->getRigidBody()->velocity * m_pPlaneSprite->getRigidBody()->maxSpeed;
		if (m_pPlaneSprite->getTransform()->position == m_pTargetPathNode->getTransform()->position)
		{
			m_targetPathNodeIndex++;
			if (m_targetPathNodeIndex > m_pPatrolPath.size() - 1)
			{
				m_targetPathNodeIndex = 0;
			}
		}
	}
}

void PlayScene::start()
{
	m_buildGrid();
	m_buildPatrolPath();
	m_displayPatrolPath();

	m_targetPathNodeIndex = 1;

	m_bDebugMode = false;
	m_bPatrolMode = false;
	
	//Plane Sprite
	m_pPlaneSprite = new Plane();
	m_pPlaneSprite->getTransform()->position = m_pPatrolPath[0]->getTransform()->position;
	m_pPlaneSprite->getRigidBody()->maxSpeed = 4.0f;
	addChild(m_pPlaneSprite);

	// Player Sprite
	m_pPlayer = new Player(glm::vec2(600.0f, 400.0f));
	m_pPlayer->getTransform()->position = glm::vec2(600.0f, 400.0f);
	addChild(m_pPlayer);
	m_playerFacingRight = false;

	// Obstacle Texture
	m_pObstacle = new Obstacle();
	addChild(m_pObstacle);

	//Music
	SoundManager::Instance().load("../Assets/audio/StartScenemusic.mp3", "StartScenemusic", SOUND_MUSIC);
	SoundManager::Instance().playMusic("StartScenemusic");
	SoundManager::Instance().setAllVolume(10);
	//Sound-FX
	SoundManager::Instance().load("../Assets/audio/Grunting-sound.mp3", "Grunt", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/sword-1b.wav", "Sword", SOUND_SFX);
}

void PlayScene::m_buildGrid()
{
	//Logic to add Path nodes
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			PathNode* pathNode = new PathNode();
			pathNode->getTransform()->position = glm::vec2(pathNode->getWidth() * col + Config::TILE_SIZE * 0.5, pathNode->getHeight() * row + Config::TILE_SIZE * 0.5);
			m_pGrid.push_back(pathNode);

			/*std::cout << "grid position: " << row * Config::COL_NUM + col << std::endl;*/
		}
	}
	std::cout << "number of nodes: " << m_pGrid.size() << std::endl;
}

void PlayScene::m_displayGrid()
{
	//Logic to add Path nodes to the scene
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			/*Util::DrawRect(m_pGrid[row * Config::COL_NUM + col]->getTransform()->position + glm::vec2(m_pGrid[row * Config::COL_NUM + col]->getWidth() * 0.5f, 0.0f)*/
				/*m_pGrid[row * Config::COL_NUM + col]->getHeight() * 0.5f), 5, 5);*/
				
			/*std::cout << "grid display position: " << row * Config::COL_NUM + col << std::endl;*/
			auto colour = glm::vec4(0, 0, 1, 1);
			Util::DrawLine(m_pPlaneSprite->getTransform()->position, m_pPlayer->getTransform()->position, colour);

			Util::DrawRect(m_pGrid[row * Config::COL_NUM + col]->getTransform()->position - glm::vec2(m_pGrid[row * Config::COL_NUM + col]->getWidth() * 0.5f), 40, 40);

			Util::DrawRect(m_pGrid[row * Config::COL_NUM + col]->getTransform()->position, 5, 5);

			
		}
	}
}

void PlayScene::m_displayGridLOS()
{
	for (auto node : m_pGrid)
		if (!node->getLOS())
		{
			{
				auto colour = glm::vec4(1, 0, 1, 1);

				Util::DrawLine(node->getTransform()->position, m_pPlayer->getTransform()->position, colour);
			}
		}
}

void PlayScene::m_setGridLOS()
{
	for (auto node : m_pGrid)
	{
		node->setLOS(CollisionManager::LOSCheck(node, m_pPlayer, m_pObstacle));
	}
	
}

void PlayScene::m_buildPatrolPath()
{
	//Plane moves right
	for (auto i = 0; i < Config::COL_NUM; i++)
	{
		m_pPatrolPath.push_back(m_pGrid[i]);
	}
	//Plane moves down
	for (auto i = 1; i < Config::ROW_NUM; i++)
	{
		m_pPatrolPath.push_back(m_pGrid[i * Config::COL_NUM + Config::COL_NUM - 1]);
	}

	//Plane moves left
	for (auto i = 1; i < Config::COL_NUM; i++)
	{
		m_pPatrolPath.push_back(m_pGrid[Config::COL_NUM * Config::ROW_NUM - 1 - i]);
	}
	//Plane Moves up
	for (auto i = Config::ROW_NUM - 2; i > 0; i--)
	{
		m_pPatrolPath.push_back(m_pGrid[i * Config::COL_NUM]);
	}
}

void PlayScene::m_displayPatrolPath()
{
	for (auto node : m_pPatrolPath)
	{
		std::cout << "(" << node->getTransform()->position.x << ", " << node->getTransform()->position.y << ")" << std::endl;
	}
}

