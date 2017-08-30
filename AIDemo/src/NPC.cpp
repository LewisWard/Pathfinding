// Author : Lewis Ward
// Date: 29/08/2017
#include "NPC.h"

NPC::NPC()
{
	// set seed
	srand(time(0));

	// load texture
	m_texture = new Texture("images/bot.bmp");

	m_moving = false;
}

NPC::NPC(vec2 startPosition)
{
	// set seed
	srand(time(0));

	//set start position
	m_position = startPosition;

	// load texture
	m_texture = new Texture("images/bot.bmp");

	m_moving = false;
}

NPC::~NPC()
{
	delete m_texture;
}

void NPC::loadNewTexture(const char* texture)
{
	// delete old texture and load the new one
	delete m_texture;
	m_texture = new Texture(texture);
}

void NPC::draw(SDL_Renderer* r)
{
	SDL_Rect destRect;
	destRect.w = 20;
	destRect.h = 20;
	destRect.x = m_position.x * 20;
	destRect.y = m_position.y * 20;
	SDL_RenderCopy(r, m_texture->texture(), NULL, &destRect);
}

void NPC::update(float dt, vec2 newPosition)
{
	m_moving = true;
	// movement speed
	float speed = 5.25f;
	// move closer to the next waypoint
	float xMove = (newPosition.x - m_position.x) * speed * dt;
	float yMove = (newPosition.y - m_position.y) * speed * dt;
	m_position.x += xMove;
	m_position.y += yMove;
}

vec2 NPC::genMoveTo()
{
	m_moveToPosition.x = (rand() % 545) + 1;
	m_moveToPosition.y = (rand() % 545) + 1;

	return m_moveToPosition;
}
