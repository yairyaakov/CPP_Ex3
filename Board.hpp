// 207723198
// yair852258@gmail.com

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Player.hpp"
#include "Plot.hpp"
#include <vector>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "DevelopmentCard.hpp"

// Forward declaration of Player class
class Player;

using namespace std;

class Board {
public:
    Board(Player &player1, Player &player2, Player &player3);

    // Get the vector that hold the players
    vector<Player*>& getPlayers();

    // Get the plots of the board
    const vector<Plot>& getPlots() const;

    // Get the vertices of the board
    vector<Vertex>& getVertices();

    // Print the board configuration
    void printBoard() const;

    // Function to get the edge index between two vertices
    int getEdgeIndex(size_t vertexIndex1, size_t vertexIndex2) const;

    // Get the number of the development cards in the deck
    size_t getDeckSize() const;

    // Function to check if a player can place his initial settlements
    bool canPlaceInitialSettlementAndRoad(Player& player, size_t vertexIndex, size_t vertexIndex2);

    // Check if a settlement can be placed on a vertex
    bool canPlaceSettlement(int playerId, size_t vertexIndex);

    // Check if a city can be placed on a vertex
    bool canPlaceCity(int playerId, size_t vertexIndex);

    // Check if a road can be placed between two vertices
    bool canPlaceRoad(int playerId, size_t vertexIndex1, size_t vertexIndex2);

    // Function to give resources to the players based on the dice roll
    void giveResources(vector<Player*>& players, int diceRoll);

    // Function to draw a random development card
    void drawDevelopmentCard(int playerId);

    // Vector to hold the Development Cards
    vector<DevelopmentCard> developmentCardsDeck;

    // The winner's ID
    int winnerIndex = -1;

    // The ID of the player with the biggest army
    int biggestArmyID = -1;

    // The number of knights played by the player with the biggest army
    int biggestArmy = 2;

private:
    // Vector to hold the players
    vector<Player*> players;

    // Vector to hold the plots
    vector<Plot> plots;

    // Vector to hold the vertices
    vector<Vertex> vertices;

    // Vector to hold the edges
    vector<Edge> edges;



};



#endif //BOARD_HPP
