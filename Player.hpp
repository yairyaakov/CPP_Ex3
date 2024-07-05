// 207723198
// yair852258@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Board.hpp"
#include <string>
#include <vector>

// Forward declaration of Board class
class Board;

using namespace std;

class Player {
public:
    Player(int id, const string &name);

    //Get the ID of the current player
    int getID() const;

    //Get the name of the current player
    string getName() const;

    // Get the resources and the amount of each resource owned by the current player
    vector<pair<string, int>> getResources() const;

    // //Print the resources and the amount of each resource owned by the current player
    // void printResources() const;

    // Add resource to the current player
    void addResource(const string &resourceType, int amount);

    //Get the settlements owned by the player
    const vector<int> getOwnedSettlements(Board &board) const;

    //Get the settlements owned by the player
    const vector<int> getOwnedCities(Board &board) const;

    //Get the settlements owned by the player
    const vector<int> &getOwnedRoads(Board &board) const;

    // Function to place the initial settlements
    void placeInitialSettlementAndRoad(int vertexIndex, int vertexIndex2, Board &gameBoard);

    // Chack if the player won the game
    void chackingGameWin(Board &gameBoard) const;

    // Print the amounts of resources the player currently owns
    void displayResourcesInfo() const;

    // Check if the player can buy a settlement with the resource he owned
    bool canBuySettlement() const;

    // Checking if it is possible to build a settlement. If possible, build a settlement
    void establishSettlement(int vertexIndex, Board &gameBoard);

    // Check if the player can buy a city with the resource he owned
    bool canBuyCity() const;

    // Checking if it is possible to upgrade a city. If possible, upgrade to city
    void upgradeToCity(int vertexIndex, Board &gameBoard);

    // Check if the player can buy a road with the resource he owned
    bool canBuyRoad() const;

    // Checking if it is possible to construct a road. If possible, construct a road
    void constructRoad(int vertexIndex1, int vertexIndex2, Board &gameBoard);

    // Chack if the player can buy development card
    bool canBuyDevelopmentCard();

    // Function to discard half of the resources of a player if the roll total is 7
    void discardResources(Board &gameBoard) const;

    // Function to roll two dice
    void rollDice(Board &gameBoard) const;

    // A function that took the top development card from the shuffled deck and gave it to the player. the card will be deleted from the deck.
    void chooseDevelopmentCard(Board &gameBoard);

    // Function to use 'Monopoly' Development Card - the player chooses some resource and all other players are obliged to transfer this resource to him
    void useMonopoly(Board &gameBoard, string resource);

    // Function to use 'Road Building' Development Card - the player can build 2 roads on the map at no cost
    void useRoadBuilding(Board &gameBoard, int vertexIndex1, int vertexIndex2, int vertexIndex3, int vertexIndex4);

    // Function to use 'Year of Plenty' Development Card - the player gets to receive from the bank two resource cards of his choice and use them in the same turn
    void useYearOfPlenty(const string& resource1, const string& resource2);

    // Function to use 'Knight' Development Card - a player holding 3 such cards receives the largest army card which gives him 2 victory points
    void useKnight(Board &gameBoard);

    // Function for trade resources with other players
    void tradeResources(Board &gameBoard, string wantedResource ,int wantedResourceAmount, int otherPlayerID, string otherPlayerWantedResource, int otherPlayerWantedResourceAmount);

    // Vector to hold the development cards
    vector<string> ownedDevelopmentCards;

    // Number of victory points the player has
    size_t victoryPoints;

    // number of knights played
    int knightsNum;

    // Get the winner of the game
    bool winner;

    // int for the number of knights played
    int knightsPlayed = 0;

private:

    // ID of the player
    int ID;

    // Name of the player
    string name;

    // Vector to hold the amount of each resource of the player
    vector<pair<string, int>> resources;

    // Number of development cards
    int ownedDevelopmentCardsNum;

    // Vector to hold the settlements
    vector<int> ownedSettlements;

    // Vector to hold the cities
    vector<int> ownedCities;

    // Vector to hold the roads
    vector<int> ownedRoads;
};



#endif //PLAYER_HPP
