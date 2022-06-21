#include "Player.hh"

Player::Player() : 	posWidth(GetScreenWidth() / 2 - texture.width),
					posHeight(GetScreenHeight() / 2 - texture.height)
{
}

Player::~Player()
{
	UnloadTexture(texture);
}

void Player::setTexture(const char* path)
{
	texture = LoadTexture(path);
}

