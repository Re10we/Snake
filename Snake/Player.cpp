#include "Player.h"

Player::Player()
{
	Score = 0;
	Speed = 200;
}

bool Player::IsTail() const
{
	if (AllSegments.size() >= 3)
	{
		return true;
	}

	return false;
}

void Player::PushHead(int XValue, int YValue)
{
	if (AllSegments.empty() == false)
	{
		// Pushed new element(HEAD) depending on past coordinates to array segments of snake
		AllSegments.push_back
		({ AllSegments.back().first + XValue,AllSegments.back().second + YValue });
	}
	else
	{
		// Pushed new element(HEAD) to array segments of snake
		AllSegments.push_back({ XValue,YValue });
	}
}

void Player::PopTail()
{
	AllSegments.pop_front();
}

std::pair<uint32_t, uint32_t> Player::GetHeadCoordinate() const
{
	return AllSegments.back();
}

std::pair<uint32_t, uint32_t> Player::GetTailCoordinate() const
{
	return AllSegments.front();
}

bool Player::IsCollisionWithTail(std::pair<uint32_t, uint32_t> DesiredCoordinates, uint32_t CountAllowedMatches) const
{
	int64_t CountHeadElement = std::count(AllSegments.begin(), AllSegments.end(), DesiredCoordinates);

	if (CountHeadElement > CountAllowedMatches && IsTail() == true)
	{
		return true;
	}

	return false;
}

void Player::AddScore(uint32_t Value)
{
	Score += Value;
}

uint32_t Player::GetScore() const
{
	return Score;
}

uint32_t Player::GetSpeed() const
{
	return Speed;
}

void Player::SetSpeed(uint32_t NewValue)
{
	Speed = NewValue;
}
