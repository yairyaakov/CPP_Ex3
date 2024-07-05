// 207723198
// yair852258@gmail.com

#include <iostream>
#include <ctime>
#include "Player.hpp"
#include "Board.hpp"

using namespace std;

int main()
{
    srand(time(0)); // use current time as seed for random generator

    Player player(1, "Yair");
    Player player2(2, "Ori");
    Player player3(3, "Ron");

    Board board(player, player2, player3);

    // Set the initial settlements and roads
    player.placeInitialSettlementAndRoad(19, 18, board);
    player2.placeInitialSettlementAndRoad(44, 34, board);
    player3.placeInitialSettlementAndRoad(42, 43, board);
    player3.placeInitialSettlementAndRoad(13, 12, board);
    player2.placeInitialSettlementAndRoad(40, 41, board);
    player.placeInitialSettlementAndRoad(35, 24, board);

    cout << "\nInitial settlements and roads placed.\n"
         << endl;

    // Simulate the first 2-3 rounds

    // Round 1
    cout << "Round 1:\n" << endl;

    player.rollDice(board);
    player.constructRoad(25, 24, board);
    player.tradeResources(board, "Brick", 2, 2, "Ore", 1);
    player.establishSettlement(25, board);

    player2.rollDice(board);
    player2.tradeResources(board, "Brick", 3, 1, "Ore", 1);
    player2.constructRoad(33, 34, board);
    player2.chooseDevelopmentCard(board);
    player2.establishSettlement(33, board); // Should not be able to place a settlement here

    player3.rollDice(board);
    player3.chooseDevelopmentCard(board);
    player3.upgradeToCity(13, board); // Should not be able to upgrade to a city here

    // Round 2
    cout << "\nRound 2:\n" << endl;

    player.rollDice(board);
    player.chooseDevelopmentCard(board);
    player.tradeResources(board, "Wool", 2, 2, "Brick", 1);

    player2.rollDice(board);
    player2.constructRoad(32, 33, board);
    player2.useKnight(board);

    player3.rollDice(board);
    player3.tradeResources(board, "Wheat", 1, 1, "Ore", 1);
    player3.establishSettlement(14, board);

    // Round 3
    cout << "\nRound 3:\n" << endl;

    player.rollDice(board);
    player.constructRoad(26, 25, board);
    player.upgradeToCity(35, board);

    player2.rollDice(board);
    player2.chooseDevelopmentCard(board);
    player2.establishSettlement(34, board);

    player3.rollDice(board);
    player3.useYearOfPlenty("Wheat", "Ore");

    return 0;
}

