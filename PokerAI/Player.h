#pragma once

#include <string>
#include <vector>

class Player
{
public:
	Player();		// Constructor
	~Player();		// Destructor
	void check();		// Function to handle if player selects check
	int bet(int smallblind, int bigblind, int stack);			// Function to handle betting
	void fold();		// Function for folding
	void recieveHand(std::string DrawnCard);		// Function to give player their hand
	void showHand();
	int stack = 5000;
	bool IsBigBlind;
	bool IsSmallBlind;
	bool IsButton;
	std::vector <std::string> hand;			// Current Cards in Hand
private:
	int numOfPlayers;
};

