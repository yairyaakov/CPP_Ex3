//ID : 207723198
//Mail : yair852258@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Board.hpp"
#include "Player.hpp"
#include <unordered_set>


// Helper function to compare two vectors of Plots
bool comparePlots(const vector<Plot> &expected, const vector<Plot> &actual)
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
            Plot("Agricultural", 9, 7), Plot("Forest", 11, 8), Plot("Desert", 0, 9),
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
        CHECK_THROWS_AS(gameBoard.canPlaceSettlement(player1.getID(), -2), out_of_range);

        // It is not possible to build a settlement on an intersection that does not lead to at least one road
        CHECK_THROWS_AS(gameBoard.canPlaceSettlement(player1.getID(), 0),runtime_error);
        CHECK_THROWS_AS(gameBoard.canPlaceSettlement(player2.getID(), 1), runtime_error);

        // Player1 build his an initail settlemant and road
        player1.placeInitialSettlementAndRoad(0, 1, gameBoard);

        // Check that it is not possible to build settlement due vertex already occupied
        CHECK_THROWS_AS(gameBoard.canPlaceSettlement(player1.getID(), 0), runtime_error);        //**********************************************

        // Check that it is not possible to build settlement due neighbor vertex occupied  //***************************************************
        CHECK_THROWS_AS(gameBoard.canPlaceSettlement(player1.getID(), 8), runtime_error);
    }

    SUBCASE("Road Placement Validation")
    {
        // A road segment can only be connected to a settlement (or city) owned by the player or to another road segment  //********************************
        CHECK_THROWS_AS(gameBoard.canPlaceRoad(player1.getID(), 0, 1), runtime_error);
        CHECK_THROWS_AS(gameBoard.canPlaceRoad(player2.getID(), 1, 2), runtime_error);
    }

    SUBCASE("City Placement Validation")  //******************************************************
    {
        // A city must replace an existing settlement
        CHECK_THROWS_AS(gameBoard.canPlaceCity(player1.getID(), 0), runtime_error);
        CHECK_THROWS_AS(gameBoard.canPlaceCity(player2.getID(), 1), runtime_error);

        // Player1 build his an initail settlemant and road
        player1.placeInitialSettlementAndRoad(0, 1, gameBoard);

        // Give to player 1 resources to upgrade a settlement to a city
        player1.addResource("Ore", 3);
        player1.addResource("Wheat", 2);

        // Upgrade the settlement to city
        player1.upgradeToCity(0, gameBoard);

        // Check that it is not possible to build city becouse city already exists at this vertex
        CHECK_THROWS_AS(gameBoard.canPlaceSettlement(player1.getID(), 0), runtime_error);
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

        // Check if player1 get 2 "wood" resources
        CHECK(player1.getResources()[0].second == 2);
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
        CHECK_THROWS(gameBoard.canPlaceCity(player1.getID(), 0));

        player1.placeInitialSettlementAndRoad(0, 1, gameBoard);
        player1.upgradeToCity(0, gameBoard);

        // Checks the replacement of a settlement in city
        CHECK(player1.getOwnedCities(gameBoard).size() == 1);
        CHECK(player1.getOwnedSettlements(gameBoard).size() == 0);

        // Chack the player get 2 resources due he upgrade to city

        // The rusult of rolling the dice is 10
        gameBoard.giveResources(gameBoard.getPlayers(), 10);
       
        CHECK_FALSE(player1.getResources()[4].second == 1);
        CHECK(player1.getResources()[4].second == (2+1));
    }

    SUBCASE("Road Placement Verification")
    {
        // Can not construct road without resources
        CHECK_THROWS(player1.constructRoad(0, 1, gameBoard));

        // Check construct road after place settlement
        player1.placeInitialSettlementAndRoad(0, 8, gameBoard);

        // Give to player 1 resources to construct road
        player1.addResource("Wood", 1);
        player1.addResource("Brick", 1);

        player1.constructRoad(0, 1, gameBoard);
        CHECK(player1.getOwnedRoads(gameBoard).size() == 2);
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
        player1.addResource("Wool", 1);
        player1.addResource("Wheat", 1);
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
        CHECK_FALSE(player1.canBuyRoad());
        player1.addResource("Wood", 1);
        player1.addResource("Brick", 1);
        CHECK(player1.canBuyRoad());
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
        player1.addResource("Wool", 1);
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
        player3.setOwnedDevelopmentCard(gameBoard, "Knight");
        player3.useKnight(gameBoard);
        player3.setOwnedDevelopmentCard(gameBoard, "Knight");
        player3.useKnight(gameBoard);
        player3.setOwnedDevelopmentCard(gameBoard, "Knight");
        player3.useKnight(gameBoard);

        // Checks if the player get 2 'victory point' after using knight card 3 times
        CHECK(player3.knightsPlayed == 3);
        CHECK(player3.victoryPoints == 2+2); // 2 victory points at the first and 2 more for the biggest army card
    }

    SUBCASE("Year Of Plenty Usage Check")
    {
        //Add to player 1 "Year Of Plenty" card
        player1.setOwnedDevelopmentCard(gameBoard, "Year of Plenty");
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
        CHECK(player1.getResources()[3].second == 3);
        CHECK(player1.getResources()[4].second == 3);
    }

    SUBCASE("Monopoly card usage Check")
    {
        // Check about try of the player to use card he does not have
        CHECK_THROWS_AS(player1.useMonopoly(gameBoard, "Wheat");, runtime_error);

        player2.addResource("Ore", 2);
        player3.addResource("Ore", 2);

        //Add to player 1 "Monopoly card" card
        player1.setOwnedDevelopmentCard(gameBoard, "Monopoly");
        player1.useMonopoly(gameBoard, "Ore");

        // Check if 4 ore resource has been added to player 1
        CHECK(player1.getResources()[4].second == 4);

        // Check if the other players have lost all the ore resources they have
        CHECK(player2.getResources()[4].second == 0);
        CHECK(player3.getResources()[4].second == 0);
    }

    SUBCASE("Road Placement card usage Check")
    {
        // Check about try of the player to use card he does not have
        CHECK_THROWS_AS(player1.useRoadBuilding(gameBoard, 52, 51, 53, 45), runtime_error);

        //Add to player 1 "Monopoly card" card
        player1.setOwnedDevelopmentCard(gameBoard, "Road Placement");

        player1.placeInitialSettlementAndRoad(53, 52, gameBoard);
        player1.useRoadBuilding(gameBoard, 52, 51, 53, 45);
        CHECK(player1.getOwnedRoads(gameBoard).size() == 3);
    }
}

