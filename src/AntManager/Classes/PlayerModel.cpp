#include "Pch.h"
#include "PlayerModel.h"


PlayerModel::PlayerModel()
	:m_Money(0)
{
}

PlayerModel::~PlayerModel()
{

}

bool PlayerModel::init()
{
	m_Money = 100;
	return true;
}
