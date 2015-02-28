#include "Pch.h"
#include "Unit.h"

Unit::~Unit() {}

void Unit::updatePosition(const float dTime)
{
	setPosition(getPosition() + m_Velocity * dTime);
}