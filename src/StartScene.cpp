#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
	SoundManager::Instance().load("../Assets/audio/arrive.mp3", "arrive", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/avoid.ogg", "avoid", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/flee.wav", "flee", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/seek.wav", "seek", SOUND_SFX);
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}

}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color green = { 0,100,0,0 };
	const SDL_Color black = { 0, 0, 0, 0 };
	const SDL_Color Red = { 200,0, 0,0 };
	m_pStartLabel = new Label("START SCENE", "W95", 90, black, glm::vec2(400.0f, 100.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pIdStudent = new Label("MIGUEL PENALVER  101280939", "W95", 60, black, glm::vec2(400.0f, 300.0f));
	m_pIdStudent->setParent(this);
	addChild(m_pIdStudent);

	m_pInstructionsLabel = new Label("Press 'Space' to start app or click button", "W95", 50, Red, glm::vec2(400.0f, 520.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);
	SoundManager::Instance().load("../Assets/audio/W95.mp3", "W95", SOUND_MUSIC);
	SoundManager::Instance().setMusicVolume(15);
	SoundManager::Instance().playMusic("W95", -1);

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	
}

