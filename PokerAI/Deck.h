#pragma once

#include <string>
#include <vector>

//declare variables    
const int SuitNum = 4;		// Number of suits in a deck
const int FacesNum = 13;		// Number of cards in each suit
const int maxCards = 2;		// Maximum number of cards a player can have
const int CardNum = 52;		// Maximum number of cards there are

//create arrays for card labels
const std::string suits[] = { "Hearts", "Clubs", "Diamonds", "Spades" };
const std::string face[] = { "2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace" };

class Deck
{
public:
	Deck();			// Constructor
	~Deck();		// Destructor
	std::string dealCard();		// Deal a card
	void generateDeck();		// Generate a Deck
	void shuffle();		// Shuffle generated deck
private:
	int tempCardNum = 0;		// variable to keep track of number of cards in deck
	std::string card = "";		//variable to hold array combos being assigned to vector
	std::vector<std::string> Cards;			//Create vector to store deck in.
	std::vector<std::string> shuffleCards;		//Create vector to store shuffled cards in deck
};
