//ID : 207723198
//Mail : yair852258@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Board.hpp"
#include "Player.hpp"
#include <unordered_set>


// Helper function to compare two vectors of Plots
bool comparePlots(const std::vector<Plot> &expected, const std::vector<Plot> &actual)
{
    if (expected.size() != actual.size())
    {
        return false;
    }

    // Comparing each element of the vectors
    for (size_t i = 0; i < expected.size(); ++i)
    {
        if (expected[i].getResource() != actual[i].getResource() ||
            expected[i].getNumber() != actual[i].getNumber() ||
            expected[i].getIndex() != actual[i].getIndex())
        {
            return false;
        }
    }

    return true;
}


TEST_CASE("Board Initialization")
{
    Player player1(1, "Yair");
    Player player2(2, "Ori");
    Player player3(3, "Ron");
    Board board(player1, player2, player3);

    SUBCASE("Plot Initialization Check")
    {
        vector<Plot> plots = board.getPlots();

        // Checking that plots are not empty
        REQUIRE_FALSE(plots.empty());

        // Validating each plot's index
        for (const Plot& plot : plots)
        {
            CHECK(plot.getIndex() >= 0);
        }

        vector<Plot> expectedPlots = {
            Plot("Mountains", 10, 0), Plot("Pasture", 2, 1),
            Plot("Forest", 9, 2), Plot("Agricultural", 12, 3),
            Plot("Hills", 6, 4), Plot("Pasture", 4, 5), Plot("Hills", 10, 6),
            Plot("Agricultural", 9, 7), Plot("Forest", 11, 8), Plot("Desert", 7, 9),
            Plot("Forest", 3, 10), Plot("Mountains", 8, 11), Plot("Forest", 8, 12),
            Plot("Mountains", 3, 13), Plot("Agricultural", 4, 14), Plot("Pasture", 5, 15),
            Plot("Hills", 5, 16), Plot("Agricultural", 6, 17), Plot("Pasture", 11, 18)};

        REQUIRE(comparePlots(expectedPlots, board.getPlots()));
    }

    SUBCASE("Player Setup Verification")
    {
        vector<Player*> players = {&player1, &player2, &player3};

        // Checking if the board's players match the expected players
        REQUIRE(board.getPlayers() == players);

        // Validating each player's ID
        for (const auto& player : players)
        {
            CHECK(player->getID() > 0);
        }
    }

    SUBCASE("Development Cards Setup Verification")
    {
        // Using an unordered_set to track unique card types
        unordered_set<string> cardTypes;

        // Inserting each card type into the set
        for (const auto& card : board.developmentCardsDeck)
        {
            cardTypes.insert(card.getType());
        }

        // Checking that there are more than one unique card type
        REQUIRE(cardTypes.size() > 1);

        unordered_set<string> expectedCards = {
            "Knight", "Victory Point", "Road Placement", "Year Of Plenty", "Monopoly"};

        // Checking that the set size matches the expected number of card types
        REQUIRE(cardTypes.size() == 5);

        // Checking that the set of card types matches the expected set
        REQUIRE(cardTypes == expectedCards);
    }
}


TEST_CASE("Player Initialization")
{
    Player player(1, "Yair");

    SUBCASE("Player ID Check")
    {
        REQUIRE(player.getID() == 1);
        CHECK(player.getID() != 0);
    }

    SUBCASE("Player Name Check")
    {
        REQUIRE(player.getName() == "Yair");
        CHECK(player.getName() != "Unknown");
    }

    SUBCASE("Initial Resources Check")
    {
        // Validating that each resource count is zero initially
        for (const auto& resource : player.getResources())
        {
            REQUIRE(resource.second == 0);
        }
    }
}


TEST_CASE("Board Functionalities")
{
    Player player1(1, "Yair");
    Player player2(2, "Ori");
    Player player3(3, "Ron");
    Board gameBoard(player1, player2, player3);

    SUBCASE("Plot Resource Check")
    {
        // Expected plot for comparison
        Plot expected("Mountains", 10, 0);
        Plot actual = gameBoard.getPlots()[0];

        // Validating that actual plot matches expected plot
        REQUIRE(actual.getResource() == expected.getResource());
        REQUIRE(actual.getNumber() == expected.getNumber());
        REQUIRE(actual.getIndex() == expected.getIndex());
    }

    SUBCASE("Settlement Placement Validation")
    {
        // Invalid vertex
        REQUIRE_FALSE(gameBoard.canPlaceSettlement(player1.getID(), -2));

        // It is not possible to build a settlement on an intersection that does not lead to at least one road
        REQUIRE_FALSE(gameBoard.canPlaceSettlement(player1.getID(), 0));
        REQUIRE(gameBoard.canPlaceSettlement(player2.getID(), 1) == false);

        // Player1 build his an initail settlemant and road
        player1.placeInitialSettlementAndRoad(0, 1, gameBoard);

        // Check that it is not possible to build settlement due vertex already occupied
        REQUIRE_FALSE(gameBoard.canPlaceSettlement(player1.getID(), 0));        //**********************************************

        // Check that it is not possible to build settlement due neighbor vertex occupied  //***************************************************
        REQUIRE_FALSE(gameBoard.canPlaceSettlement(player1.getID(), 8));
    }

    SUBCASE("Road Placement Validation")
    {
        // A road segment can only be connected to a settlement (or city) owned by the player or to another road segment  //********************************
        REQUIRE_FALSE(gameBoard.canPlaceRoad(player1.getID(), 0, 1));
        REQUIRE(gameBoard.canPlaceRoad(player2.getID(), 1, 2) == false);
    }

    SUBCASE("City Placement Validation")  //******************************************************
    {
        // A city must replace an existing settlement
        REQUIRE_FALSE(gameBoard.canPlaceCity(player1.getID(), 0));
        REQUIRE(gameBoard.canPlaceCity(player2.getID(), 1) == false);

        // Player1 build his an initail settlemant and road
        player1.placeInitialSettlementAndRoad(0, 1, gameBoard);

        // Upgrade the settlement to city
        player1.upgradeToCity(0, gameBoard);

        // Check that it is not possible to build city becouse city already exists at this vertex
        REQUIRE_FALSE(gameBoard.canPlaceSettlement(player1.getID(), 0));
    }

    SUBCASE("Edge Validation")
    {
        REQUIRE(gameBoard.getEdgeIndex(0, 1) == 0);
        REQUIRE(gameBoard.getEdgeIndex(1, 2) != -1);
    }

    SUBCASE("Resource Allocation Check")
    {
        // Player1 build his initail settlement in 18 vertex and his initail road in 25 edge
        player1.placeInitialSettlementAndRoad(18, 19, gameBoard);

        // The rusult of rolling the dice is 11
        gameBoard.giveResources(gameBoard.getPlayers(), 11);
        // The rusult of rolling the dice is 12
        gameBoard.giveResources(gameBoard.getPlayers(), 12);

        // Check if player1 get "wood" and "wheat" resources
        CHECK(player1.getResources()[0].second == 1);
        CHECK(player1.getResources()[3].second == 1);
    }

    SUBCASE("Development Card Drawing Validation")
    {
        // Checks the player get the same number of cards he drawed
        for (size_t i=0; i<gameBoard.developmentCardsDeck.size(); i++)
        {
            gameBoard.drawDevelopmentCard(player1.getID());
        }
        CHECK(player1.ownedDevelopmentCards.size() == 25);

        // Chack the print if the player try to draw a card and the deck is empty
        stringstream buffer;
        streambuf* oldCout = cout.rdbuf(buffer.rdbuf()); //********************************************************88

        player1.chooseDevelopmentCard(gameBoard);
        cout.rdbuf(oldCout);

        // Check the output
        REQUIRE(buffer.str() == "No more development cards in the deck\n");
    }
}


TEST_CASE("Player Functionalities")
{
    Player player1(1, "Yair");
    Player player2(2, "Ori");
    Player player3(3, "Ron");
    Board gameBoard(player1, player2, player3);

    SUBCASE("Initial Settlement and Road Placement Check")
    {
        // Checking that player1 owns 1 road and 1 settlement
        player1.placeInitialSettlementAndRoad(0, 1, gameBoard);
        CHECK(player1.getOwnedRoads(gameBoard).size() == 1);
        CHECK(player1.getOwnedSettlements(gameBoard).size() == 1);
    }

    SUBCASE("City Upgrade Check")    //******************************************************
    {
        player1.addResource("Ore", 3);
        player1.addResource("Wheat", 2);

        // The player can not place a city if there is no settlement on this vertex
        REQUIRE_FALSE(gameBoard.canPlaceCity(player1.getID(), 0));

        player1.placeInitialSettlementAndRoad(0, 1, gameBoard);
        player1.upgradeToCity(0, gameBoard);

        // Checks the replacement of a settlement in city
        CHECK(player1.getOwnedCities(gameBoard).size() == 1);
        CHECK(player1.getOwnedSettlements(gameBoard).size() == 0);

        // Chack the player get 2 resources due he upgrade to city

        // The rusult of rolling the dice is 10
        gameBoard.giveResources(gameBoard.getPlayers(), 10);
       
        CHECK_FALSE(player1.getResources()[4].second == 1);
        CHECK(player1.getResources()[4].second == 2);
    }

    SUBCASE("Road Placement Verification")
    {
        player1.constructRoad(0, 1, gameBoard);
        CHECK(player1.getOwnedRoads(gameBoard).size() == 1);
    }

    SUBCASE("Resource Addition Check")
    {
        player1.addResource("Wood", 1);
        CHECK(player1.getResources()[0].second == 1);
    }

    SUBCASE("Settlement Purchase Check")
    {
        // Checking the player's inability to build a settlement in the absence of resources
        CHECK_FALSE(player1.canBuySettlement());
        player1.addResource("Wood", 1);
        player1.addResource("Brick", 1);
        player1.addResource("Wheat", 1);
        player1.addResource("Sheep", 1);
        CHECK(player1.canBuySettlement());
    }

    SUBCASE("City Purchase Check")
    {
        // Checking the player's inability to build a city in the absence of resources
        CHECK_FALSE(player1.canBuyCity());
        player1.addResource("Ore", 3);
        player1.addResource("Wheat", 2);
        CHECK(player1.canBuyCity());
    }

    SUBCASE("Road Purchase Check")
    {
        //Checking the player's inability to build a road in the absence of resources
        CHECK_FALSE(player1.canBuyCity());
        player1.addResource("Wood", 1);
        player1.addResource("Brick", 1);
        CHECK(player1.canBuyCity());
    }

    SUBCASE("Dice Roll Validation")
    {
        player1.rollDice(gameBoard);

        // Check each resource of each player validity
        for (const auto& player : gameBoard.getPlayers())
        {
            for (const auto& resource : player->getResources())
            {
                CHECK(resource.second >= 0);
            }
        }
    }

    SUBCASE("Development Card Selection Check")
    {
        player1.addResource("Ore", 1);
        player1.addResource("Wheat", 1);
        player1.addResource("Sheep", 1);
        player1.chooseDevelopmentCard(gameBoard);
        CHECK(player1.ownedDevelopmentCards.size() == 1);
    }

    SUBCASE("Resource Trading Validation")  //*********************************************************
    {
        // Checks the trade between player1 to player 2
        player1.addResource("Wood", 1);
        player2.addResource("Brick", 1);
        player1.tradeResources(gameBoard,  "Brick", 1, player2.getID(), "Wood", 1);
        CHECK(player1.getResources()[0].second  == 0);
        CHECK(player1.getResources()[1].second == 1);
        CHECK(player2.getResources()[0].second == 1);
        CHECK(player2.getResources()[1].second == 0);

        //Checking the players's inability to trade due lack of resources
        stringstream buffer;
        streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

        player1.tradeResources(gameBoard,  "Brick", 1, player2.getID(), "Wood", 1);
        cout.rdbuf(oldCout);

        // Check the output
        REQUIRE(buffer.str() == "Player Yair cannot trade 1 Brick with player Ori for 1 Wood\n");
    }

    SUBCASE("Knight Usage Check")  //******************************************************************
    {
        // Checks the biggest army cards - if the player use the knight card more than any of the other players use he get 2 victory point
        player1.useKnight(gameBoard);
        player1.useKnight(gameBoard);
        player1.useKnight(gameBoard);
        CHECK(player1.knightsPlayed == 3);
        CHECK(player1.victoryPoints == 2);
    }

    SUBCASE("Year Of Plenty Usage Check")
    {
        // Checks if the player get the two resources he chose
        player1.useYearOfPlenty("Wood", "Brick");
        CHECK(player1.getResources()[0].second == 1);
        CHECK(player1.getResources()[1].second == 1);
    }

    SUBCASE("Resource Discarding Check")      //********************************************************************888
    {
        // Checks the player loose half of his resources if he have less than 7 resources
        player1.addResource("Wood", 2);
        player1.addResource("Brick", 2);
        player1.discardResources(gameBoard);
        CHECK(player1.getResources()[0].second == 2);
        CHECK(player1.getResources()[1].second == 2);

        // Checks the player loose half of his resources if he have more than 7 resources
        player1.addResource("Ore", 6);
        player1.addResource("Wheat", 6);
        player1.discardResources(gameBoard);
        player1.addResource("Ore", 3);
        player1.addResource("Wheat", 3);
    }
}

