#include "GameSession.h"

int main()
{
	GameSession* GameSession = GameSession::GetInstance();
	GameSession->SetWindowSession(640, 480);
	
	std::thread t1(&GameSession::HandleInput, GameSession);
	std::thread t2(&GameSession::StartSession, GameSession);

	t1.join();
	t2.join();

	return 0;
}