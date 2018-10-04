#include "Player.h"

#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <cstdlib>

Player::Player()
{
	std::cout << "NEW PLAYER OBJECT" << std::endl;
}

Player::~Player()
{
	std::cout << "PLAYER OBJECT DESTROYED" << std::endl;
}

void Player::recieveHand(std::string DrawnCard)
{
	this->hand.push_back(DrawnCard);
}

int Player::bet(int smallblind, int bigblind, int stack)
{
	int initialbet;
	while (int i = 0)
	{
		std::cout << "Please input bet: ";
		std::cin >> initialbet;
		if (initialbet / bigblind == 0 && initialbet <= stack)
		{
			i = 1;
		}
		else;
	}

	int finalbet = initialbet;

	return finalbet;
}

void Player::check()
{
	// Do nothing
}

void Player::showHand()
{
	std::cout << hand.at(0) << " and " << hand.at(1) << std::endl;
}