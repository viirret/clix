#include "Player.hh"

Player::Player(const char* path, int width, int height) : 	
					posWidth(width),
					posHeight(height)
{
	texture = LoadTexture(path);
}

Player::~Player()
{
	UnloadTexture(texture);
}

void Player::setTexture(const char* path)
{
	texture = LoadTexture(path);
}

//int Player::getWidth() { return width; }
//int Player::getHeight() { return height; }

