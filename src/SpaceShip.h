#pragma once
#ifndef __SPACE_SHIP__
#define __SPACE_SHIP__
#include "DisplayObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Label.h"
#include "Whisker.h"
//#include "Game.h"

class Spaceship : public DisplayObject
{
public:
	Spaceship();
	~Spaceship();
	void draw() override;
	void update() override;
	void clean() override;

	void setDestination(const glm::vec2 destination);
	void setMaxSpeed(float speed);
	glm::vec2 getOrientation()const;
	void setOrientation(glm::vec2 Orientation);
	void setRotation(float Angle);
	float getRotation()const;
	float getTurnRate()const;
	void setTurnRate(float rate);
	float getAccelerationRate()const;
	void setAccelerationRate(float rate);
	glm::vec2 set_Rotation2(const float angle);
	friend class PlayScene;
	
	
private:

	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_Orientation;
	float m_RotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	void m_Move();
	bool fleeMove = false;
	bool arrivalMove = false;
	bool obstacleAvoid = false;
	bool m_leftCollision, m_rightCollision, m_centerCollision;
	Whisker m_centerWhisker, m_leftWhisker, m_rightWhisker;
	
};
#endif // !__SPACE_SHIP__
