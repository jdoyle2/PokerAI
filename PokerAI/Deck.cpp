#include "Deck.h"

#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <cstdlib>

Deck::Deck()
{
	std::cout << "NEW DECK OBJECT" << std::endl;
}

Deck::~Deck()
{
	std::cout << "DECK OBJECT DESTROYED" << std::endl;
}

void Deck::generateDeck()
{
	//Generate the deck
	for (int i = 0; i < SuitNum; i++) { //iterate through suits

		for (int j = 0; j < FacesNum; j++) {//iterate through faces

			card = face[j] + " of " + suits[i]; //declare card

			Cards.push_back(card);			// add card to vector
			tempCardNum++;		// raise card number for every card added to deck
		}
	}
}

void Deck::shuffle()
{
	srand(time(0));		//Shuffle the deck
	for (int i = 0; i < tempCardNum; tempCardNum--)
	{
		std::string tempCard;
		int RCard = rand() % tempCardNum;		// Generate a random number based on number of cards left in deck
		tempCard = Cards.at(RCard);			// Put random card into temp variable
		shuffleCards.push_back(tempCard);		// Put random card into shuffled deck
		Cards.erase(Cards.begin() + RCard);		// Remove that element from original deck
		;
	}
	tempCardNum = 52;		// Reset the total number of cards to 52
}

std::string Deck::dealCard()
{
	std::string DrawnCard = shuffleCards.front();		// Draw card from the top of the deck
	shuffleCards.erase(shuffleCards.begin());		// Remove cards from vector so they cant be called twice
	tempCardNum--;		// Lower available cards

	return DrawnCard;
}