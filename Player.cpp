// 207723198
// yair852258@gmail.com

#include "Player.hpp"
#include <iostream>

Player::Player(int id, const string &name)
    : ID(id), name(name)
{
    resources.resize(5); //for specified number of elements
    resources[0] = make_pair("Wood", 0);
    resources[1] = make_pair("Brick", 0);
    resources[2] = make_pair("Wool", 0);
    resources[3] = make_pair("Wheat", 0);
    resources[4] = make_pair("Ore", 0);

    victoryPoints = 2; // Each player start the game with 2 victory points
    ownedDevelopmentCardsNum = 0;
    knightsNum = 0;
    winner = -1;
}

//Get the ID of the current player
int Player::getID() const
{
    return ID;
}

//Get the name of the current player
string Player::getName() const
{
    return name;
}


// Get the resources and the amount of each resource owned by the current player
vector<pair<string, int>> Player::getResources() const
{
    return resources;
}


// //Get the resources and the amount of each resource owned by the current player
// void Player::getResources() const
// {
//     cout << "The resources that the player " << this->getName() << " owns are: \n";
//     for (int i = 0; i < 5; i++)
//     {
//         cout << resources[i].first << ": " << resources[i].second << " \n";
//     }
// }


void Player::addResource(const string &resourceType, int quantity)
{
    for (auto & resource : resources)
    {
        if (resource.first == resourceType)
        {
            cout << "Player " << this->getName() << " got " << quantity << " " << resourceType << "." << endl;
            resource.second += quantity;
            cout << "Player " << this->getName() << " now has " << resource.second << " " << resourceType << "." << endl;
        }
    }
    // Display the total resources the player has:
    cout << "Player " << this->getName() << " currently holds the following resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << "." << endl;
}


//Get the settlements owned by the player
const vector<int> Player::getOwnedSettlements(Board &board) const
{
    return ownedSettlements;
}

//Get the settlements owned by the player
const vector<int> Player::getOwnedCities(Board &board) const
{
    return ownedCities;
}

//Get the settlements owned by the player
const vector<int> &Player::getOwnedRoads(Board &board) const
{
    return ownedRoads;
}


// Function to place the initial settlements
void Player::placeInitialSettlementAndRoad(int vertexIndex1, int vertexIndex2, Board &gameBoard)
{
    if (gameBoard.canPlaceInitialSettlementAndRoad(*this, vertexIndex1, vertexIndex2))
    {
        ownedSettlements.push_back(vertexIndex1);
        ownedRoads.push_back(gameBoard.getEdgeIndex(vertexIndex1, vertexIndex2));
        cout << this->getName() << " placed an initial settlement on vertex " << vertexIndex1 << " and a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << "\n"
             << endl;
    }
    else
    {
        cout << this->getName() << " cannot place an initial settlement on vertex " << vertexIndex1 << " and a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << endl;
    }
}


// Chack if the player won the game
void Player::chackingGameWin(Board &gameBoard) const
{
    // Ensure the player has an amount of victory points that greater than 10 and no other player has won the game
    if (victoryPoints >= 10 && gameBoard.winnerIndex == -1)
    {
        gameBoard.winnerIndex = this->getID();
        cout << "Player " << getName() << " has won the game!" << endl;
    }
}


// Print the amounts of resources the player currently owns
void Player::displayResourcesInfo() const
{
    cout << "Player " << getName() << " now has the following resources: "
             << "Wood: " << resources[0].second << ", "
             << "Brick: " << resources[1].second << ", "
             << "Wool: " << resources[2].second << ", "
             << "Wheat: " << resources[3].second << ", "
             << "Ore: " << resources[4].second << "." << endl;
}


// Check if the player can buy a settlement with the resource he hase
bool Player::canBuySettlement() const
{
    if (resources[0].second >= 1 && resources[1].second >= 1 && resources[2].second >= 1 && resources[3].second >= 1)
    {
        return true;
    }
    return false;
}


// Checking if it is possible to build a settlement. If possible, build a settlement
void Player::establishSettlement(int vertexIndex, Board &gameBoard)
{
    //Check if the player can buy a settlement with the resources he owned
    if (!canBuySettlement())
    {
        cout << "Player " << getName() << " is unable to establish a settlement due lack of resources." << endl;
        return;
    }

    //Check if the player can buy a settlement considering the state of the game board
    if (gameBoard.canPlaceSettlement(getID(), vertexIndex))
    {
        ownedSettlements.push_back(vertexIndex);
        cout << "Player " << getName() << " has established a settlement at vertex " << vertexIndex << "." << endl;

        //One resource of each type needed to build a settlement will be missing
        for (int i = 0; i < 4; i++)
        {
            resources[i].second -= 1;
        }

        //Building a sattlement gives the player one victory point
        victoryPoints++;

        // Display player's resources after establishing the settlement
        displayResourcesInfo();

        // Display player's points after establishing the settlement
        cout << "Player " << getName() << " now has " << victoryPoints << " victory points." << endl;

        // Check for victory condition
        chackingGameWin(gameBoard);
    }
    else
    {
        cout << "Player " << getName() << " cannot establish a settlement at vertex " << vertexIndex << "." << endl;
    }
}


// Check if the player can buy a city with the resources he owned
bool Player::canBuyCity() const
{
    if (resources[3].second >= 2 && resources[4].second >= 3)
    {
        return true;
    }
    return false;
}


// Checking if it is possible to upgrade a city. If possible, upgrade to city
void Player::upgradeToCity(int vertexIndex, Board &gameBoard)
{
    //Check if the player can buy a city with the resources he owned
    if (!canBuyCity())
    {
        cout << "Player " << this->getName() << " lacks the resources to upgrade a settlement to a city at vertex " << vertexIndex << endl;
        return;
    }

    //Check if the player can buy a city considering the state of the game board
    if (gameBoard.canPlaceCity(this->getID(), vertexIndex))
    {
        ownedCities.push_back(vertexIndex);
        cout << "Player " << this->getName() << " has upgraded a settlement to a city at vertex " << vertexIndex << endl;

        //One resource of each type needed to construct a road will be missing
        resources[3].second -= 2; // Reduce wheat
        resources[4].second -= 3; // Reduce ore

        // As soon as a settlement is upgraded to a city, the player loses the point of the settlement and receives 2 points for the construction
        victoryPoints += 1;

        // Display player's resources after establishing the settlement
        displayResourcesInfo();

        // Display points after city upgrade
        cout << "Player " << this->getName() << " now has " << victoryPoints << " points." << endl;

        // Check for victory condition
        chackingGameWin(gameBoard);
    }
    else
    {
        cout << "Player " << this->getName() << " cannot upgrade a settlement to a city at vertex " << vertexIndex << endl;
    }
}

// Check if the player can buy a road with the resources he owned
bool Player::canBuyRoad() const
{
    if (resources[1].second >= 1 && resources[2].second >= 1)
    {
        return true;
    }
    return false;
}


// Checking if it is possible to construct a road. If possible, construct a road
void Player::constructRoad(int vertexIndex1, int vertexIndex2, Board &gameBoard)
{
    //Check if the player can buy a settlement with the resources he owned
    if (!canBuyRoad())
    {
        cout << "Player " << this->getName() << " cannot construct a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << " due lack of resources." << endl;
        return;
    }

    //Check if the player can buy a road considering the state of the game board
    if (gameBoard.canPlaceRoad(this->getID(), vertexIndex1, vertexIndex2))
    {
        ownedRoads.push_back(gameBoard.getEdgeIndex(vertexIndex1, vertexIndex2));
        cout << "Player " << this->getName() << " has successfully constructed a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << "." << endl;

        //One resource of each type needed to construct a road will be missing
        resources[0].second -= 1; // Deduct wood
        resources[1].second -= 1; // Deduct brick

        // Display player's resources after establishing the settlement
        displayResourcesInfo();
    }
    else
    {
        cout << "Player " << this->getName() << " is unable to construct a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << "." << endl;
    }
}


// Chack if the player can buy development card with the resources he owned
bool Player::canBuyDevelopmentCard()
{
    if (resources[2].second >= 1 && resources[3].second >= 1 && resources[4].second >= 1)
    {
        //One resource of each type needed to buy a development card will be missing
        resources[2].second -= 1;
        resources[3].second -= 1;
        resources[4].second -= 1;

        cout << "Player " << this->getName() << " bought a development card" << endl;

        // Display player's resources after establishing the settlement
        displayResourcesInfo();

        // Add one development card to the count
        ownedDevelopmentCardsNum++;
        return true;
    }

    cout << "Player " << this->getName() << " cannot buy a development card because he is broke" << endl;
    return false;
}


// Function to discard half of the resources of a player if the roll total is 7
void Player::discardResources(Board &gameBoard) const
{
    for (int i = 0; i < 3; i++)
    {
        // check if the player has more than 7 resources
        int totalResources = gameBoard.getPlayers()[i]->resources[0].second +
                        gameBoard.getPlayers()[i]->resources[1].second +
                        gameBoard.getPlayers()[i]->resources[2].second +
                        gameBoard.getPlayers()[i]->resources[3].second +
                        gameBoard.getPlayers()[i]->resources[4].second;

        if (totalResources > 7)
        {
            // calculate the number of resources to discard
            int resourcesToDiscard = totalResources / 2;

            // first, discard half of each resource type (rounded down)
            for (int j = 0; j < 5; j++)
            {
                int discardFromThisResource = gameBoard.getPlayers()[i]->resources[j].second / 2;
                gameBoard.getPlayers()[i]->resources[j].second -= discardFromThisResource;
                resourcesToDiscard -= discardFromThisResource;
            }

            // if there are still resources to discard, continue discarding one by one from each resource type
            int j = 0;
            while (resourcesToDiscard > 0)
            {
                if (gameBoard.getPlayers()[i]->resources[j].second > 0)
                {
                    gameBoard.getPlayers()[i]->resources[j].second--;
                    resourcesToDiscard--;
                }
                j = (j + 1) % 5; // move to the next resource type, return to the first one if necessary
            }

            // Display player's resources after discarding
            displayResourcesInfo();
        }
    }
}


// Function to roll two dice
void Player::rollDice(Board &gameBoard) const
{
    // Rolling 2 dice
    int diceRoll = rand() % 6 + 1 + rand() % 6 + 1;

    if (diceRoll == 7)
    {
        cout << "Player " << this->getName() << " rolled a 7" << endl;
        // every player with more than 7 resources will have to discard half of his resources
        discardResources(gameBoard);
    }
    else
    {
        cout << "Player " << this->getName() << " rolled a " << diceRoll << endl;

        gameBoard.giveResources(gameBoard.getPlayers(), diceRoll);
    }
}


// A function that took the top development card from the shuffled deck and gave it to the player. the card will be deleted from the deck.
void Player::chooseDevelopmentCard(Board &gameBoard)
{
    // Insure the deck is not empty
    if (gameBoard.getDeckSize() == 0)
    {
        cout << "No more development cards in the deck" << endl;
        return;
    }

    // Check if the player has the resources to buy a development card
    if (!canBuyDevelopmentCard())
    {
        return;
    }

    // Draw the top card from the deck and assign it to the player
    gameBoard.drawDevelopmentCard(this->getID());

    // Print the development card that the player got
    string card = this->ownedDevelopmentCards.back();
    cout << this->getName() << " got a: " << card << " card" << endl;

    ownedDevelopmentCardsNum++;

    // Display player's resources after buying the development card
    displayResourcesInfo();

    if (card == "Victory Point")
    {
        this->victoryPoints += 1;

        // Display points after get a 'Victory Point' card
        cout << "Player " << this->getName() << " now has " << victoryPoints << " points." << endl;

        // Check for victory condition
        chackingGameWin(gameBoard);
    }
}


// Function to use 'Monopoly' Development Card - The player chooses some resource and all other players are obliged to transfer this resource to him
void Player::useMonopoly(Board &gameBoard, string resource)
{
    // Verify the player owns a Monopoly card
    for (int i = 0; i < ownedDevelopmentCardsNum; i++)
    {
        if (ownedDevelopmentCards[i] == "Monopoly")
        {
            // Check if the player can get the resources
            for (int j = 0; j < 3; j++)
            {
                // The other players
                if (gameBoard.getPlayers()[j]->getID() != this->getID()-1)
                {
                    for (int k = 0; k < gameBoard.getPlayers()[j]->resources.size(); k++)
                    {
                        if (gameBoard.getPlayers()[j]->resources[k].first == resource)
                        {
                            // Add to the current player all the amount the other player has of this resource
                            addResource(resource, gameBoard.getPlayers()[j]->resources[k].second);

                            // Now, the other player has nothing left of this resource
                            gameBoard.getPlayers()[j]->resources[k].second = 0;
                        }
                    }
                }
            }
            // Remove the Monopoly card from the player's hand
            ownedDevelopmentCards.erase(ownedDevelopmentCards.begin() + i);
            ownedDevelopmentCardsNum--;
            return;
        }
    }
    cout << "Player " << this->getName() << " does not possess a Monopoly card" << endl;
}


// Function to use 'Road Building' Development Card - the player can build 2 roads on the map at no cost
void Player::useRoadBuilding(Board &gameBoard, int vertexIndex1, int vertexIndex2, int vertexIndex3, int vertexIndex4)
{
    // Verify the player owns a Road Building card
    for (int i = 0; i < ownedDevelopmentCardsNum; i++)
    {
        if (ownedDevelopmentCards[i] == "Road Placement")
        {
            // Check if the player can place the roads
            if (gameBoard.canPlaceRoad(this->getID(), vertexIndex1, vertexIndex2) && gameBoard.canPlaceRoad(this->getID(), vertexIndex3, vertexIndex4))
            {
                constructRoad(vertexIndex1, vertexIndex2, gameBoard);
                constructRoad(vertexIndex3, vertexIndex4, gameBoard);

                // Remove the Road Building card from the player's hand
                ownedDevelopmentCards.erase(ownedDevelopmentCards.begin() + i);
                ownedDevelopmentCardsNum--;
                return;
            }

            cout << "Player " << this->getName() << " can not place roads in these vertices" << endl;
            return;
        }
    }
    cout << "Player " << this->getName() << " does not possess a 'Road Building' card" << endl;
}


// Function to use 'Year Of Plenty' Development Card - the player gets to receive from the bank two resource cards of his choice and use them in the same turn
void Player::useYearOfPlenty(const string& wantedResource1, const string& wantedResource2)
{
    // Verify the player owns a Year Of Plenty card
    for (int i = 0; i < ownedDevelopmentCardsNum; i++)
    {
        if (ownedDevelopmentCards[i] == "Year of Plenty")
        {
            // Add the two resources to the resources owned by the current player
            addResource(wantedResource1, 1);
            addResource(wantedResource2, 1);

            // Display player's resources after geting the resources
            displayResourcesInfo();

            // Remove the Year Of Plenty card from the player's hand
            ownedDevelopmentCards.erase(ownedDevelopmentCards.begin() + i);
            ownedDevelopmentCardsNum--;
            return;
        }
    }
    cout << "Player " << this->getName() << " does not possess a 'Year Of Plenty' card" << endl;
}


// Function to use 'Knight' Development Card - a player holding 3 such cards receives the largest army card which gives him 2 victory points
void Player::useKnight(Board &gameBoard)
{
    // Verify the player owns a knight card
    for (int i = 0; i < ownedDevelopmentCardsNum; ++i)
    {
        if (ownedDevelopmentCards[i] == "Knight")
        {
            knightsPlayed++;

            // Announce knight card usage
            cout << "Player " << getName() << " used a knight card." << endl;
            // Announce the total number of knights used
            cout << "Player " << getName() << " has now used " << knightsPlayed << " knights." << endl;

            // Check for the largest army
            if (knightsPlayed > gameBoard.biggestArmy)
            {
                bool largestArmyUpdated = true;

                // Reduce points from previous largest army holder
                if (gameBoard.biggestArmyID != -1 && gameBoard.biggestArmyID != getID())
                {
                    gameBoard.getPlayers()[gameBoard.biggestArmyID-1]->victoryPoints -= 2;
                    largestArmyUpdated = false;
                }
                else if (gameBoard.biggestArmyID == -1)
                {
                    largestArmyUpdated = false;
                }

                // Update largest army and points
                if (!largestArmyUpdated)
                {
                    gameBoard.biggestArmy = knightsPlayed;
                    gameBoard.biggestArmyID = getID();
                    victoryPoints += 2;

                    // Check for victory condition
                    chackingGameWin(gameBoard);
                }
            }

            // Remove the Knight card from the player's hand
            ownedDevelopmentCards.erase(ownedDevelopmentCards.begin() + i);
            ownedDevelopmentCardsNum--;
            return;
        }
    }
    std::cout << "Player " << getName() << " does not possess a knight card." << std::endl;
}


// Function for trade resources with other players
void Player::tradeResources(Board &gameBoard, string wantedResource ,int wantedResourceAmount, int otherPlayerID, string otherPlayerWantedResource, int otherPlayerWantedResourceAmount)
{
    // check if the current player has the resources thet the other player wants
    for (int i = 0; i < 5; i++)
    {
        if (resources[i].first == otherPlayerWantedResource && resources[i].second >= otherPlayerWantedResourceAmount)
        {
            // check if the other player has the resources that the current player wants
            for (int j = 0; j < 5; j++)
            {
                if (gameBoard.getPlayers()[otherPlayerID - 1]->resources[j].first == wantedResource && gameBoard.getPlayers()[otherPlayerID - 1]->resources[j].second >= wantedResourceAmount)
                {
                    // trade the resources
                    resources[j].second += wantedResourceAmount;
                    resources[i].second -= otherPlayerWantedResourceAmount;
                    gameBoard.getPlayers()[otherPlayerID - 1]->resources[i].second += otherPlayerWantedResourceAmount;
                    gameBoard.getPlayers()[otherPlayerID - 1]->resources[j].second -= wantedResourceAmount;

                    cout << "Player " << this->getName() << " traded " << wantedResourceAmount << " " << wantedResource << " with player " << gameBoard.getPlayers()[otherPlayerID - 1]->getName() << " for " << otherPlayerWantedResourceAmount << " " << otherPlayerWantedResource << endl;

                    // Display current player's resources after trading
                    displayResourcesInfo();

                    // Display other player's resources after trading
                    gameBoard.getPlayers()[otherPlayerID - 1]->displayResourcesInfo();
                    return;
                }
            }
        }
    }
    // print that the trade was not successful
    cout << "Player " << this->getName() << " cannot trade " << wantedResourceAmount << " " << wantedResource << " with player " << gameBoard.getPlayers()[otherPlayerID - 1]->getName() << " for " << otherPlayerWantedResourceAmount << " " << otherPlayerWantedResource << endl;
}
