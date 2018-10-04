#include "Poker.h"

#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <cstdlib>

Poker::Poker()
{
	std::cout << "NEW POKER OBJECT" << std::endl;

	currentDeck = new Deck;
	currentDeck->generateDeck();
	currentDeck->shuffle();

	players();

	preflop();

	flop();

	turn();

	river();

	delete currentDeck;
}

Poker::~Poker()
{
	std::cout << "POKER OBJECT DESTROYED" << std::endl;
}

void Poker::players()
{
	std::cout << "Please enter the amount of players: ";
	std::cin >> numOfPlayers;
	player = new Player[numOfPlayers];
}

void Poker::preflop()
{
	// Preflop
	turnNumber = 0;
	bigBlindPos = this->bigBlind(numOfPlayers);
	smallBlindPos = this->smallBlind(bigBlindPos, numOfPlayers);
	button = this->playerButton(numOfPlayers, smallBlindPos);

	lastPlayer = button - 1;
	for (int i = button; i != lastPlayer; i++)
	{
		if (smallBlindPos == i)
		{
			player[i].stack -= smallblind;
			pot += smallblind;
		}

		if (bigBlindPos == i)
		{
			player[i].stack -= bigblind;
			pot += bigblind;
		}

		player[i].recieveHand(currentDeck->dealCard());
		player[i].recieveHand(currentDeck->dealCard());
		std::cout << "Player " << i << ": ";
		player[i].showHand();
		if (i == numOfPlayers - 1)
		{
			for (int j = 0; j != button; j++)
			{
				player[j].recieveHand(currentDeck->dealCard());
				player[j].recieveHand(currentDeck->dealCard());
				std::cout << "Player " << j << ": ";
				player[j].showHand();
			}
			i = lastPlayer - 1;
		}
	}

	for (int i = button; i != lastPlayer; i++)
	{

	}

	delete[] player;
}

void Poker::flop()
{
	std::cout << std::endl;
	std::cout << "Flop:" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		tableCards.push_back(currentDeck->dealCard());
		std::cout << tableCards.at(i) << std::endl;
	}
}

void Poker::turn()
{
	std::cout << std::endl;
	std::cout << "Turn:" << std::endl;

	tableCards.push_back(currentDeck->dealCard());
	std::cout << tableCards.at(3) << std::endl;
}

void Poker::river()
{
	std::cout << std::endl;
	std::cout << "River:" << std::endl;

	tableCards.push_back(currentDeck->dealCard());
	std::cout << tableCards.at(4) << std::endl;
	std::cout << std::endl;
}

int Poker::smallBlind(int bigBlindPos, int numOfPlayers)
{
	smallBlindPos = bigBlindPos - 1;
	if (smallBlindPos < 0)
	{
		smallBlindPos = numOfPlayers;
	}

	return smallBlindPos;
}

int Poker::bigBlind(int numOfPlayers)
{
	if (turnNumber == 0)
	{
		if (bigBlindPos > numOfPlayers)
		{
			bigBlindPos = 0;
		}
		bigBlindPos++;
	}

	return bigBlindPos;
}

void Poker::addBettoPot(int finalbet)
{
	pot = finalbet;
}

int Poker::playerButton(int numOfPlayers, int smallBlindPos)
{
	button = smallBlindPos - 1;
	if (button < 0)
	{
		button = numOfPlayers;
	}

	return button;
}

