// 207723198
// yair852258@gmail.com

#include <iostream>
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

using namespace std;

int main() {
    Player player1(1, "Ori");
    Player player2(2, "Ron");
    Player player3(3, "Yair");
    Board board(player1, player2, player3);

    // the starting placements for every player

    //Ori builds settlements on vertex id: 2,13.  and roads on edges id: 7,15
    player1.placeInitialSettlementAndRoad(2, 10, board);
    player1.placeInitialSettlementAndRoad(13, 12, board);

    //Ron builds settlements on vertex id: 49,51.  and roads on edges id: 63,64.
    player2.placeInitialSettlementAndRoad(49, 41, board);
    player2.placeInitialSettlementAndRoad(51, 43, board);

    //yair builds settlements on vertex id: 29,35.  and roads on edges id: 34,37.
    player3.placeInitialSettlementAndRoad(29,18, board);
    player3.placeInitialSettlementAndRoad(35,24, board);



         //start of the game!!!!!!!!!!!!!

    // Ori roll the dice
    player1.rollDice(board);
    player1.constructRoad(11, 12, board);

    //Ron roll the dice
    player2.rollDice(board);

    //Yair roll the dice
    player3.rollDice(board);


    //Ori roll the dice and do a trade
    player1.rollDice(board);
    player1.tradeResources(board, "Wheat", 1, 2, "Ore", 1);


    //Ron roll the dice and buy a development card
    player2.rollDice(board);
    player2.chooseDevelopmentCard(board);


    //Yair roll the dice and try to trade and build city(this will work or not based on the dice results)
    player3.rollDice(board);

    //Yair try to trade - give 1 wood get 1 ore
    try {
        player3.tradeResources(board, "Ore", 1, 1, "Wood", 1);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    //Yair try to build city
    try {
        player3.upgradeToCity(29,board);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    try {
        player3.useYearOfPlenty("Wheat", "Ore");
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}