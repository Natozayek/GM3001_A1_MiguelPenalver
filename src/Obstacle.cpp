#include "Obstacle.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Util.h"

Obstacle::Obstacle()
{
	TextureManager::Instance()->load("../Assets/textures/obstacle.png", "obstacle");

	auto size = TextureManager::Instance()->getTextureSize("obstacle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(300.0f, 300.0f);
	getRigidBody()->isColliding = false;
	setType(OBSTACLE);
	SoundManager::Instance().load("../Assets/audio/thunder.ogg", "thunder", SOUND_SFX);
}

Obstacle::~Obstacle()
= default;

void Obstacle::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	TextureManager::Instance()->draw("obstacle",
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);
	Util::DrawRect(getTransform()->position - glm::vec2(getWidth() * 0.5, getHeight() * 0.5), getWidth() * 1, getHeight() * 1);
	
	//TextureManager::Instance()->draw("obstacle", x, y, 0, 255, true);
	//Util::DrawRect(getTransform()->position - glm::vec2(getWidth()* 0.5, getHeight() * 0.5),getWidth() *1,getHeight()*1);

}

void Obstacle::update()
{
}

void Obstacle::clean()
{
}
