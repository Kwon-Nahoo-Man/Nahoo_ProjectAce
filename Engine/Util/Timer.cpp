#include "Timer.h"

UTIL::C_TIMER::C_TIMER(float targetTime)
	: m_targetTime(targetTime)
{

}

void UTIL::C_TIMER::Tick(float deltaTime)
{
	m_elapsedTime += deltaTime;
}

void UTIL::C_TIMER::Reset()
{
	m_elapsedTime = 0.0f;
}

bool UTIL::C_TIMER::IsTimeOut() const
{
	return m_elapsedTime >= m_targetTime;
}

void UTIL::C_TIMER::SetTargetTime(float targetTime)
{
	m_targetTime = targetTime;
}
