// Author : Lewis Ward
// Date: 29/08/2017
#include "Player.h"

Player::Player()
{
	PlayerTexture = new Texture("images/player.bmp");
}
Player::~Player()
{
	delete PlayerTexture;
}
void Player::Draw(SDL_Renderer* r)
{
	SDL_Rect destRect;
	destRect.w = 20;
	destRect.h = 20;
	destRect.x = Position.x * 20;
	destRect.y = Position.y * 20;
	SDL_RenderCopy(r, PlayerTexture->texture(), NULL, &destRect);
}
void Player::Update(float dt, vec2 newPosition)
{
		// movement speed
		float speed = 5.0f;

		// update player to move closer to the next waypoint
		float testX = (newPosition.x - Position.x) * speed * dt;
		float testY = (newPosition.y - Position.y) * speed * dt;
		Position.x += testX;
		Position.y += testY;
}
