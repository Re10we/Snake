#pragma once
#include <deque>
#include <algorithm>

class Player
{
public:

	Player();

	// Push back new element (i`ts new HEAD of snake)
	void PushHead(int XValue, int YValue);

	// Delete last element
	void PopTail();

	// Is there a tail
	bool IsTail() const;

	//Getters for last element (HEAD) & first element (TAIL)
	std::pair<uint32_t, uint32_t> GetHeadCoordinate() const;
	std::pair<uint32_t, uint32_t> GetTailCoordinate() const;

	// Collision check with the tail
	bool IsCollisionWithTail(std::pair<uint32_t, uint32_t> DesiredCoordinates, uint32_t CountAllowedMatches = 0) const;

	//System score
	void AddScore(uint32_t Value);
	uint32_t GetScore() const;

	//Getter & setter for speed
	uint32_t GetSpeed() const;
	void SetSpeed(uint32_t NewValue);

private:

	uint32_t Score;
	uint32_t Speed;

	std::deque<std::pair<uint32_t,uint32_t>> AllSegments;

};