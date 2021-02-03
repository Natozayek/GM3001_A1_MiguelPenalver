#pragma once
#ifndef __WHISKER_H__
#define __WHISKER_H_
#include <GLM/vec2.hpp>
struct Whisker
{
public:
	Whisker()
	{}
	void setLine(glm::vec2 s, glm::vec2 e)
	{
		m_start = s;
		m_end = e;
	}
	glm::vec2 Start() const
	{
		return m_start;
	}
	glm::vec2 End() const
	{
		return m_end;
	}

private:
	glm::vec2 m_start;
	glm::vec2 m_end;
};
#endif // !__LINE_H__
