#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"
#include "glm/gtx/string_cast.hpp"
#include "SoundManager.h"


// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
	SoundManager::Instance().load("../Assets/audio/avoid.ogg", "avoid", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/flee.wav", "flee", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/seek.wav", "seek", SOUND_SFX);
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
	if(m_pSpaceship->obstacleAvoid == true){
		if (CollisionManager::lineRectCheck(m_pSpaceship->m_centerWhisker.Start(), m_pSpaceship->m_centerWhisker.End(), m_pObstacle->getTransform()->position - glm::vec2(100.0f, 50.0f), 200.0f, 100.0f))
		{

			m_pSpaceship->m_centerCollision = true;
			m_pSpaceship->fleeMove = true;

		}
		else if (!CollisionManager::lineRectCheck(m_pSpaceship->m_centerWhisker.Start(), m_pSpaceship->m_centerWhisker.End(), m_pObstacle->getTransform()->position - glm::vec2(100.0f, 50.0f), 200.0f, 100.0f))
		{
			m_pSpaceship->fleeMove = false;
		}
		if (CollisionManager::lineRectCheck(m_pSpaceship->m_leftWhisker.Start(), m_pSpaceship->m_leftWhisker.End(), m_pObstacle->getTransform()->position, 200.0f, 100.0f))
		{

			m_pSpaceship->m_leftCollision = true;
			m_pSpaceship->fleeMove = true;
		}
		else if (!CollisionManager::lineRectCheck(m_pSpaceship->m_leftWhisker.Start(), m_pSpaceship->m_leftWhisker.End(), m_pObstacle->getTransform()->position, 200.0f, 100.0f))
		{

			m_pSpaceship->fleeMove = false;
		}
		if (CollisionManager::lineRectCheck(m_pSpaceship->m_rightWhisker.Start(), m_pSpaceship->m_rightWhisker.End(), m_pObstacle->getTransform()->position - glm::vec2(100.0f, 50.0f), 200.0f, 100.0f))
		{

			m_pSpaceship->m_rightCollision = true;
			m_pSpaceship->fleeMove = true;
		}
		else if (!CollisionManager::lineRectCheck(m_pSpaceship->m_rightWhisker.Start(), m_pSpaceship->m_rightWhisker.End(), m_pObstacle->getTransform()->position - glm::vec2(100.0f, 50.0f), 200.0f, 100.0f))
		{

			m_pSpaceship->fleeMove = false;
		}
	}
	
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		m_pSpaceship->arrivalMove = false;
		m_pSpaceship->fleeMove = false;
		m_pSpaceship->obstacleAvoid = false;
		m_pSpaceship->setDestination((m_pTarget)->getTransform()->position);
		m_pSpaceship->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceship->setEnabled(true);
		m_pSpaceship->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceship->setMaxSpeed(3);
		SoundManager::Instance().playSound("seek", 0);
		SoundManager::Instance().setSoundVolume(1);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		m_pSpaceship->fleeMove = true;
		m_pSpaceship->obstacleAvoid = false;
		m_pSpaceship->arrivalMove = true;
		m_pSpaceship->setDestination((m_pTarget)->getTransform()->position);
		m_pSpaceship->getTransform()->position = glm::vec2(500.0f, 400.0f);
		m_pSpaceship->setEnabled(true);
		m_pSpaceship->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceship->setMaxSpeed(3);
		m_pTarget->getTransform()->position = glm::vec2(600.0f, 400.0f);
		SoundManager::Instance().playSound("flee", 0);
		SoundManager::Instance().setSoundVolume(1);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		m_pSpaceship->fleeMove = false;
		m_pSpaceship->arrivalMove = true;
		m_pSpaceship->obstacleAvoid = false;
		m_pSpaceship->setDestination((m_pTarget)->getTransform()->position);
		m_pSpaceship->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceship->setEnabled(true);
		m_pSpaceship->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceship->setMaxSpeed(3);

	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4))
	{
		m_pSpaceship->fleeMove = false;
		m_pSpaceship->arrivalMove = false;
		m_pSpaceship->obstacleAvoid = true;
		m_pSpaceship->setDestination((m_pTarget)->getTransform()->position);
		m_pSpaceship->getTransform()->position = glm::vec2(300.0f, 100.0f);
		m_pSpaceship->setEnabled(true);
		m_pSpaceship->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceship->setMaxSpeed(2);
		m_pSpaceship->setTurnRate(1.2f);
		m_pTarget->getTransform()->position = glm::vec2(500.0f, 500.0f);
		SoundManager::Instance().playSound("avoid", 0);
		SoundManager::Instance().setSoundVolume(1);

	}
}
void PlayScene::start()
{
	const SDL_Color black = { 0, 0, 0, 0 };
	// Set GUI Title
	m_guiTitle = "Play Scene";
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(750.0f, 550.0f);
	addChild(m_pTarget);

	m_pObstacle = new Obstacle();
	m_pObstacle->getTransform()->position = glm::vec2(400.0f, 300.0f);
	m_pObstacle->setEnabled(true);
	addChild(m_pObstacle);

	m_pSpaceship = new Spaceship();
	m_pSpaceship->getTransform()->position = glm::vec2(100.0f, 100.0f);
	m_pSpaceship->setEnabled(false);
	m_pSpaceship->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pSpaceship);
	m_pLabelforInstr = new Label("Simulation Mode - 1.Seek 2.Flee 3.Arrive 4.Avoid Obstacle", "W95", 30, black, glm::vec2(400.0f, 100.0f));
	addChild(m_pLabelforInstr);
	SoundManager::Instance().load("../Assets/audio/allRight.mp3", "allRight", SOUND_MUSIC);
	SoundManager::Instance().setMusicVolume(15);
	SoundManager::Instance().playMusic("allRight", -1);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	

	ImGui::Begin("GAME3001 - Lab 2", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static float speed = 10.0f;
	if (ImGui::SliderFloat("MaxSpeed", &speed, 0.0f, 100.0f))
	{
		m_pSpaceship->setMaxSpeed(speed);
	}

	static float acceleration_rate = 2.0f;
	if (ImGui::SliderFloat("Acceleration Rate", &acceleration_rate, 0.0f, 50.0f))
	{
		m_pSpaceship->setAccelerationRate(acceleration_rate);
	}

	static float angleInRadians = m_pSpaceship->getRotation();
	if (ImGui::SliderAngle("Orientation Angle", &angleInRadians))
	{
		m_pSpaceship->setRotation(angleInRadians * Util::Rad2Deg);
	}

	static float turn_rate = 5.0f;
	if (ImGui::SliderFloat("Turn Rate", &turn_rate, 0.0f, 20.0f))
	{
		m_pSpaceship->setTurnRate(turn_rate);
	}

	if (ImGui::Button("Start"))
	{
		m_pSpaceship->setEnabled(true);
	}

	ImGui::SameLine();

	if (ImGui::Button("Reset"))
	{
		m_pSpaceship->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceship->setEnabled(false);
		m_pSpaceship->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceship->setRotation(0.0f); // set Angle to 0 degrees
		turn_rate = 5.0f;
		acceleration_rate = 2.0f;
		speed = 10.0f;
		angleInRadians = m_pSpaceship->getRotation();
	}

	ImGui::Separator();

	static float targetPosition[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y };
	if (ImGui::SliderFloat2("Target", targetPosition, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(targetPosition[0], targetPosition[1]);
		m_pSpaceship->setDestination(m_pTarget->getTransform()->position);
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
