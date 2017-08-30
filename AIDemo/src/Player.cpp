// Author : Lewis Ward
// Date: 29/08/2017
#include "Player.h"

Player::Player()
{
	m_texture = new Texture("images/player.bmp");
}
Player::~Player()
{
	delete m_texture;
}
void Player::draw(SDL_Renderer* r)
{
	SDL_Rect destRect;
	destRect.w = 20;
	destRect.h = 20;
	destRect.x = m_position.x * 20;
	destRect.y = m_position.y * 20;
	SDL_RenderCopy(r, m_texture->texture(), NULL, &destRect);
}
void Player::update(float dt, vec2 newPosition)
{
		// movement speed
		float speed = 5.0f;

		// update player to move closer to the next waypoint
		float testX = (newPosition.x - m_position.x) * speed * dt;
		float testY = (newPosition.y - m_position.y) * speed * dt;
		m_position.x += testX;
		m_position.y += testY;
}
