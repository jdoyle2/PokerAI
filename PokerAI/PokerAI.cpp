// Poker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <cstdlib>

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


int main()
{
	Poker* game = new Poker;
	delete game;
}


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