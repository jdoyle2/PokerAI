#pragma once

#include "Deck.h"
#include "Player.h"

#include <string>
#include <vector>



class Poker
{
public:
	Poker();		// Constructor
	~Poker();		// Destructor
	void flop();		// Function to deal the flop
	void turn();		// Function to deal the turn
	void river();		// Function to deal the river
	int smallBlind(int bigBlindPos, int numOfPlayers);
	int bigBlind(int numOfPlayers);
	void addBettoPot(int finalbet);
	int playerButton(int numOfPlayers, int smallBlindPos);
	void preflop();
	void players();
private:
	std::string card;		// Current Card
	std::vector<std::string> tableCards;		// Cards on the table
	int smallblind = 10;		// Small Blind
	int bigblind = 20;		// Big Blind
	int smallBlindPos = 2;		// Small Blind Position
	int bigBlindPos = 3;		// Big Blind Position
	int pot;
	int turnNumber;
	Deck* currentDeck;
	int button = 1;
	int numOfPlayers;
	Player* player;
	std::string sentCard;
	int lastPlayer;
};
