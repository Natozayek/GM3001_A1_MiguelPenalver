#include "SpaceShip.h"
#include "Util.h"
#include "Game.h"


Spaceship::Spaceship() :m_maxSpeed(10.0f), m_Orientation(glm::vec2(0.0f, -1.0f)), m_RotationAngle(0.0f), m_accelerationRate(10.0f), m_turnRate(10.0f)
{
	TextureManager::Instance()->load("../Assets/textures/bike.png", "spaceship");
	auto size = TextureManager::Instance()->getTextureSize("spaceship");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(400.f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SPACE_SHIP);
	setMaxSpeed(4.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
	setAccelerationRate(5.0f);
	setTurnRate(5.0f);
	SoundManager::Instance().load("../Assets/audio/arrive.mp3", "arrive", SOUND_SFX);
}

Spaceship::~Spaceship()
= default;

void Spaceship::draw()
{
	TextureManager::Instance()->draw("spaceship", getTransform()->position.x, getTransform()->position.y, m_RotationAngle, 255, true);
	Util::DrawLine(m_centerWhisker.Start(), m_centerWhisker.End());
	Util::DrawLine(m_rightWhisker.Start(), m_rightWhisker.End());
	Util::DrawLine(m_leftWhisker.Start(), m_leftWhisker.End());
}

void Spaceship::update()
{
	m_centerWhisker.setLine(getTransform()->position, getTransform()->position + set_Rotation2(m_RotationAngle) * 75.0f);
	m_rightWhisker.setLine(getTransform()->position, getTransform()->position + set_Rotation2(m_RotationAngle + -20) * 100.0f);
	m_leftWhisker.setLine(getTransform()->position, getTransform()->position + set_Rotation2(m_RotationAngle + 20) * 100.0f);
	m_Move();
}

void Spaceship::clean()
{
}
void Spaceship::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

void Spaceship::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

glm::vec2 Spaceship::getOrientation() const
{
	return m_Orientation;
}

void Spaceship::setOrientation(const glm::vec2 Orientation)
{
	m_Orientation = Orientation;
}

void Spaceship::setRotation(const float Angle)
{
	m_RotationAngle = Angle;
	const auto angle_in_radians = (Angle - 90.0f) * Util::Deg2Rad;

	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector
	setOrientation(glm::vec2(x, y));
}

float Spaceship::getRotation() const
{
	return m_RotationAngle;
}

float Spaceship::getTurnRate() const
{
	return m_turnRate;
}

void Spaceship::setTurnRate(const float rate)
{
	m_turnRate = rate;
}

float Spaceship::getAccelerationRate()const
{
	return m_accelerationRate;
}

void Spaceship::setAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}
glm::vec2 Spaceship::set_Rotation2(const float angle)
{
	const auto angle_in_radians = (angle - 90.0f) * Util::Deg2Rad;
	const auto dx = cos(angle_in_radians);
	const auto dy = sin(angle_in_radians);
	return glm::vec2(dx, dy);
}




void Spaceship::m_Move()
{
	/*SoundManager::Instance().playSound("seek", 0);*/
	int Radius = 100.0f;
	
	auto deltalTime = TheGame::Instance()->getDeltaTime();
	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);
	auto turn_sensitivity = 2.0f;
	auto deltaTime = TheGame::Instance()->getDeltaTime();
	if (fleeMove == false)
	{	
		// direction with magnitude
		m_targetDirection = m_destination - getTransform()->position;

		m_targetDirection = Util::normalize(m_targetDirection);
	}
	else if (fleeMove == true)
	{
		
		// direction with magnitude
		m_targetDirection = (getTransform()->position - m_destination) * m_maxSpeed;
		//opposite direction

		m_targetDirection = Util::normalize(m_targetDirection);
	}
	if (arrivalMove == true)
	{

		if (Util::distance(m_destination, getTransform()->position) < Radius)
		{
			getRigidBody()->velocity = Util::normalize(getRigidBody()->velocity) * m_maxSpeed * (distance(m_destination, getTransform()->position) / Radius);
			if (distance(m_destination, getTransform()->position) <= 5)
			{
				SoundManager::Instance().playSound("arrive", 0);
				m_maxSpeed = 0;
			}

		}
	}
	if(obstacleAvoid == true)
	{
		
		
		
		if (m_centerCollision)
		{
			
			setRotation(getRotation() + 180);
			getRigidBody()->velocity *= 0.0f;
			m_centerCollision = false;
		}
		if (m_rightCollision)
		{
			
			setRotation(getRotation() + 40);
			getRigidBody()->velocity *= 0.0f;
			m_rightCollision = false;
		}
		if (m_leftCollision)
		{
			getRigidBody()->velocity *= 0.0f;
			setRotation(getRotation() - 40);
			m_leftCollision = false;
		}

		if (abs(target_rotation) > turn_sensitivity)
		{
			if (target_rotation > 0.0f)
			{
				setRotation(getRotation() + getTurnRate());
			}
			else if (target_rotation < 0.0f)
			{
				setRotation(getRotation() - getTurnRate());
			}
		}
		m_targetDirection = m_destination - getTransform()->position;
		getRigidBody()->acceleration = getOrientation() * getAccelerationRate();
		// using the formula pf = pi + vi*t_0.5ai*t^2
		getRigidBody()->velocity += getOrientation() * (deltalTime)+0.5f * getRigidBody()->acceleration * (deltalTime);
		getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);
		getTransform()->position += getRigidBody()->velocity;
	}
	

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}
		
	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	// using the formula pf = pi + vi*t + 0.5ai*t^2
	getRigidBody()->velocity += getOrientation() * (deltaTime)+
		0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
	
}
