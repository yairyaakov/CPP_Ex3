// 207723198
// yair852258@gmail.com

#include "Board.hpp"
#include <iostream>
#include <tuple>
#include <algorithm>
#include <chrono>
#include <random>

// Constructor for the Board class
Board::Board(Player &player1, Player &player2, Player &player3)
{
    cout << "Initializing board:" << endl;

    // Add players to the players vector
    players.push_back(&player1);
    players.push_back(&player2);
    players.push_back(&player3);


    // Setup the resource types, values, and indices for the board configuration
    vector<tuple<string, int, size_t>> plotConfig = {
        {"Mountains", 10, 0}, {"Pasture", 2, 1}, {"Forest", 9, 2}, {"Agricultural", 12, 3}, {"Hills", 6, 4}, {"Pasture", 4, 5},
        {"Hills", 10, 6}, {"Agricultural", 9, 7}, {"Forest", 11, 8}, {"Desert", 0, 9}, {"Forest", 3, 10}, {"Mountains", 8, 11},
        {"Forest", 8, 12}, {"Mountains", 3, 13}, {"Agricultural", 4, 14}, {"Pasture", 5, 15}, {"Hills", 5, 16}, {"Agricultural", 6, 17},
        {"Pasture", 11, 18}};

    // Initialize plots with predefined resources and values
    for (size_t i = 0; i < plotConfig.size(); ++i) {
        plots.emplace_back(Plot(get<0>(plotConfig[i]), get<1>(plotConfig[i]), get<2>(plotConfig[i])));
    }

    // Initialize vertices (54 vertices)
    vertices.reserve(54);
    for (size_t i = 0; i < 54; ++i)
    {
        vertices.emplace_back(Vertex(i));
    }

    // Define the connections between plots and vertices based on my specified order
    vector<vector<size_t>> vertexConnections = {
        {0, 1, 2, 8, 9, 10}, {2, 3, 4, 10, 11, 12}, {4, 5, 6, 12, 13, 14}, {7, 8, 9, 17, 18, 19},
        {9, 10, 11, 19, 20, 21}, {11, 12, 13, 21, 22, 23}, {13, 14, 15, 22, 24, 25}, {16, 17, 18, 27, 28, 29},
        {18, 19, 20, 29, 30, 31}, {20, 21, 22, 31, 32, 33}, {22, 23, 24, 33, 34, 35}, {24, 25, 26, 35, 36, 37},
        {28, 29, 30, 39, 40, 41}, {30, 31, 32, 40, 41, 42}, {32, 33, 34, 42, 43, 44}, {34, 35, 36, 44, 45, 46},
        {39, 40, 41, 47, 48, 49}, {41, 42, 43, 49, 50, 51}, {43, 44, 45, 51, 52, 53}
    };

    // Assign vertices to each plot
    for (size_t i = 0; i < plots.size(); ++i)
    {
        for (size_t j = 0; j < vertexConnections[i].size(); ++j)
        {
            size_t vertexIndex = vertexConnections[i][j];
            plots[i].setVertex(vertices[vertexIndex]); // Let each plot know which vertices sit on it
            vertices[vertexIndex].addAdjPlot(&plots[i]); // Let each vertex know what plots he sits on
        }
    }

     // Define vertex neighbors to handle roads
    vertices[0].addVertexNeighbor(&vertices[1]);
    vertices[0].addVertexNeighbor(&vertices[8]);
    vertices[1].addVertexNeighbor(&vertices[0]);
    vertices[1].addVertexNeighbor(&vertices[2]);
    vertices[2].addVertexNeighbor(&vertices[1]);
    vertices[2].addVertexNeighbor(&vertices[3]);
    vertices[2].addVertexNeighbor(&vertices[10]);
    vertices[3].addVertexNeighbor(&vertices[2]);
    vertices[3].addVertexNeighbor(&vertices[4]);
    vertices[4].addVertexNeighbor(&vertices[3]);
    vertices[4].addVertexNeighbor(&vertices[5]);
    vertices[4].addVertexNeighbor(&vertices[12]);
    vertices[5].addVertexNeighbor(&vertices[4]);
    vertices[5].addVertexNeighbor(&vertices[6]);
    vertices[6].addVertexNeighbor(&vertices[5]);
    vertices[6].addVertexNeighbor(&vertices[14]);
    vertices[7].addVertexNeighbor(&vertices[8]);
    vertices[8].addVertexNeighbor(&vertices[7]);
    vertices[8].addVertexNeighbor(&vertices[9]);
    vertices[8].addVertexNeighbor(&vertices[0]);
    vertices[9].addVertexNeighbor(&vertices[8]);
    vertices[9].addVertexNeighbor(&vertices[10]);
    vertices[9].addVertexNeighbor(&vertices[19]);
    vertices[10].addVertexNeighbor(&vertices[9]);
    vertices[10].addVertexNeighbor(&vertices[2]);
    vertices[10].addVertexNeighbor(&vertices[11]);
    vertices[11].addVertexNeighbor(&vertices[10]);
    vertices[11].addVertexNeighbor(&vertices[12]);
    vertices[11].addVertexNeighbor(&vertices[21]);
    vertices[12].addVertexNeighbor(&vertices[11]);
    vertices[12].addVertexNeighbor(&vertices[4]);
    vertices[12].addVertexNeighbor(&vertices[13]);
    vertices[13].addVertexNeighbor(&vertices[12]);
    vertices[13].addVertexNeighbor(&vertices[14]);
    vertices[13].addVertexNeighbor(&vertices[23]);
    vertices[14].addVertexNeighbor(&vertices[13]);
    vertices[14].addVertexNeighbor(&vertices[6]);
    vertices[14].addVertexNeighbor(&vertices[15]);
    vertices[15].addVertexNeighbor(&vertices[14]);
    vertices[15].addVertexNeighbor(&vertices[25]);
    vertices[16].addVertexNeighbor(&vertices[17]);
    vertices[17].addVertexNeighbor(&vertices[16]);
    vertices[17].addVertexNeighbor(&vertices[18]);
    vertices[17].addVertexNeighbor(&vertices[7]);
    vertices[18].addVertexNeighbor(&vertices[17]);
    vertices[18].addVertexNeighbor(&vertices[19]);
    vertices[18].addVertexNeighbor(&vertices[29]);
    vertices[19].addVertexNeighbor(&vertices[18]);
    vertices[19].addVertexNeighbor(&vertices[9]);
    vertices[19].addVertexNeighbor(&vertices[20]);
    vertices[20].addVertexNeighbor(&vertices[19]);
    vertices[20].addVertexNeighbor(&vertices[21]);
    vertices[20].addVertexNeighbor(&vertices[31]);
    vertices[21].addVertexNeighbor(&vertices[20]);
    vertices[21].addVertexNeighbor(&vertices[11]);
    vertices[21].addVertexNeighbor(&vertices[22]);
    vertices[22].addVertexNeighbor(&vertices[21]);
    vertices[22].addVertexNeighbor(&vertices[23]);
    vertices[22].addVertexNeighbor(&vertices[33]);
    vertices[23].addVertexNeighbor(&vertices[22]);
    vertices[23].addVertexNeighbor(&vertices[13]);
    vertices[23].addVertexNeighbor(&vertices[24]);
    vertices[24].addVertexNeighbor(&vertices[23]);
    vertices[24].addVertexNeighbor(&vertices[25]);
    vertices[24].addVertexNeighbor(&vertices[35]);
    vertices[25].addVertexNeighbor(&vertices[24]);
    vertices[25].addVertexNeighbor(&vertices[15]);
    vertices[25].addVertexNeighbor(&vertices[26]);
    vertices[26].addVertexNeighbor(&vertices[25]);
    vertices[26].addVertexNeighbor(&vertices[37]);
    vertices[27].addVertexNeighbor(&vertices[28]);
    vertices[28].addVertexNeighbor(&vertices[27]);
    vertices[28].addVertexNeighbor(&vertices[29]);
    vertices[28].addVertexNeighbor(&vertices[16]);
    vertices[29].addVertexNeighbor(&vertices[28]);
    vertices[29].addVertexNeighbor(&vertices[18]);
    vertices[29].addVertexNeighbor(&vertices[30]);
    vertices[30].addVertexNeighbor(&vertices[29]);
    vertices[30].addVertexNeighbor(&vertices[31]);
    vertices[30].addVertexNeighbor(&vertices[40]);
    vertices[31].addVertexNeighbor(&vertices[30]);
    vertices[31].addVertexNeighbor(&vertices[20]);
    vertices[31].addVertexNeighbor(&vertices[32]);
    vertices[32].addVertexNeighbor(&vertices[31]);
    vertices[32].addVertexNeighbor(&vertices[33]);
    vertices[32].addVertexNeighbor(&vertices[42]);
    vertices[33].addVertexNeighbor(&vertices[32]);
    vertices[33].addVertexNeighbor(&vertices[22]);
    vertices[33].addVertexNeighbor(&vertices[34]);
    vertices[34].addVertexNeighbor(&vertices[33]);
    vertices[34].addVertexNeighbor(&vertices[35]);
    vertices[34].addVertexNeighbor(&vertices[44]);
    vertices[35].addVertexNeighbor(&vertices[34]);
    vertices[35].addVertexNeighbor(&vertices[24]);
    vertices[35].addVertexNeighbor(&vertices[36]);
    vertices[36].addVertexNeighbor(&vertices[35]);
    vertices[36].addVertexNeighbor(&vertices[37]);
    vertices[36].addVertexNeighbor(&vertices[46]);
    vertices[37].addVertexNeighbor(&vertices[36]);
    vertices[37].addVertexNeighbor(&vertices[26]);
    vertices[37].addVertexNeighbor(&vertices[38]);
    vertices[38].addVertexNeighbor(&vertices[37]);
    vertices[38].addVertexNeighbor(&vertices[39]);
    vertices[39].addVertexNeighbor(&vertices[38]);
    vertices[39].addVertexNeighbor(&vertices[28]);
    vertices[39].addVertexNeighbor(&vertices[40]);
    vertices[40].addVertexNeighbor(&vertices[39]);
    vertices[40].addVertexNeighbor(&vertices[30]);
    vertices[40].addVertexNeighbor(&vertices[41]);
    vertices[41].addVertexNeighbor(&vertices[40]);
    vertices[41].addVertexNeighbor(&vertices[42]);
    vertices[41].addVertexNeighbor(&vertices[49]);
    vertices[42].addVertexNeighbor(&vertices[41]);
    vertices[42].addVertexNeighbor(&vertices[32]);
    vertices[42].addVertexNeighbor(&vertices[43]);
    vertices[43].addVertexNeighbor(&vertices[42]);
    vertices[43].addVertexNeighbor(&vertices[44]);
    vertices[43].addVertexNeighbor(&vertices[51]);
    vertices[44].addVertexNeighbor(&vertices[43]);
    vertices[44].addVertexNeighbor(&vertices[34]);
    vertices[44].addVertexNeighbor(&vertices[45]);
    vertices[45].addVertexNeighbor(&vertices[44]);
    vertices[45].addVertexNeighbor(&vertices[46]);
    vertices[45].addVertexNeighbor(&vertices[53]);
    vertices[46].addVertexNeighbor(&vertices[45]);
    vertices[46].addVertexNeighbor(&vertices[36]);
    vertices[47].addVertexNeighbor(&vertices[48]);
    vertices[48].addVertexNeighbor(&vertices[47]);
    vertices[48].addVertexNeighbor(&vertices[49]);
    vertices[49].addVertexNeighbor(&vertices[48]);
    vertices[49].addVertexNeighbor(&vertices[41]);
    vertices[49].addVertexNeighbor(&vertices[50]);
    vertices[50].addVertexNeighbor(&vertices[49]);
    vertices[50].addVertexNeighbor(&vertices[51]);
    vertices[51].addVertexNeighbor(&vertices[50]);
    vertices[51].addVertexNeighbor(&vertices[43]);
    vertices[51].addVertexNeighbor(&vertices[52]);
    vertices[52].addVertexNeighbor(&vertices[51]);
    vertices[52].addVertexNeighbor(&vertices[53]);
    vertices[53].addVertexNeighbor(&vertices[52]);
    vertices[53].addVertexNeighbor(&vertices[45]);

    // Manually establish connections between edges and vertices based on my specified order
    // The left index of vertex is intentionally smaller that the right number
    vector<vector<size_t>> edgeConnections = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {0, 8}, {2, 10}, {4, 12}, {6, 14},
    {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {13, 14}, {14, 15}, {7, 17}, {9, 19},
    {11, 21}, {13, 23}, {15, 25}, {16, 17}, {17, 18}, {18, 19}, {19, 20}, {20, 21}, {21, 22},
    {22, 23}, {23, 24}, {24, 25}, {25, 26}, {16, 27}, {18, 29}, {20, 31}, {22, 33}, {24, 35},
    {26, 37}, {27, 28}, {28, 29}, {29, 30}, {30, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 35},
    {35, 36}, {36, 37}, {28, 38}, {30, 40}, {32, 42}, {34, 44}, {36, 46}, {38, 39}, {39, 40},
    {40, 41}, {41, 42}, {42, 43}, {43, 44}, {44, 45}, {45, 46}, {39, 47}, {41, 49}, {43, 51},
    {45, 53}, {47, 48}, {48, 49}, {49, 50}, {50, 51}, {51, 52}, {52, 53}
    };

    edges.reserve(edgeConnections.size());

    // Set the vertices for each edge
    for (size_t i = 0; i < edgeConnections.size(); ++i)
    {
        const Edge edge(&vertices[edgeConnections[i][0]], &vertices[edgeConnections[i][1]], i);
        edges[i]=edge;

        // add the edges that the vertex sit on
        vertices[edgeConnections[i][0]].addEdge(&edges[i]);
        vertices[edgeConnections[i][1]].addEdge(&edges[i]);
    }

    // initialize 25 development cards: 14 knigths Cards, 5 victory points Cards, 2 road building Cards, 2 year of plenty Cards, 2 monopoly Cards
    for (int i = 0; i < 14; i++)
    {
        developmentCardsDeck.emplace_back("Knight");
    }

    for (int i = 0; i < 5; i++)
    {
        developmentCardsDeck.emplace_back("Victory Point");
    }

    for (int i = 0; i < 2; i++)
    {
        developmentCardsDeck.emplace_back("Road Placement");
    }

    for (int i = 0; i < 2; i++)
    {
        developmentCardsDeck.emplace_back("Year Of Plenty");
    }

    for (int i = 0; i < 2; i++)
    {
        developmentCardsDeck.emplace_back("Monopoly");
    }

    default_random_engine engine(chrono::system_clock::now().time_since_epoch().count());
    shuffle(developmentCardsDeck.begin(), developmentCardsDeck.end(), engine);

    // Print message indicating game setup is complete and initial board configuration
    cout << "Game initialization is complete. Initial board configuration:" << endl;
    printBoard();
}


// Get the vector that hold the players
vector<Player*>& Board::getPlayers()
{
    return players;
}


// Get the plots of the board
const vector<Plot> &Board::getPlots() const
{
    return plots;
}


// Get the vertices of the board
vector<Vertex> &Board::getVertices()
{
    return vertices;
}


void Board::printBoard() const
{
    for (const Plot &plot : plots)
    {
        cout << "Plot " << plot.getIndex() << ": " << plot.getResource() << " (" << plot.getNumber() << ")\n";
    }
}


// Function to get the edge index between two vertices
int Board::getEdgeIndex(size_t vertexIndex1, size_t vertexIndex2) const
{
    // We defined the two vertices on each side from the smallest to the largest
    if (vertexIndex1 > vertexIndex2)
    {
        swap(vertexIndex1, vertexIndex2);
    }
    for (int i = 0; i < 72; i++)
    {
        if (edges[i].getVertex1().getIndex() == vertexIndex1 && edges[i].getVertex2().getIndex() == vertexIndex2)
        {
            return i;
        }
    }
    return -1;
}


// Get the number of the development cards in the deck
size_t Board::getDeckSize() const
{
    return developmentCardsDeck.size();
}


// Function to check if a player can place his initial settlements
bool Board::canPlaceInitialSettlementAndRoad(Player &player, size_t vertexIndex1, size_t vertexIndex2)
{
    // Ensure vertex indices are within valid range
    if (vertexIndex1 >= vertices.size() || vertexIndex1 < 0 || vertexIndex2 >= vertices.size() || vertexIndex2 < 0)
    {
        throw out_of_range("Vertex index out of bounds.");
    }

    // Access the primary vertex
    Vertex &mainVertex = vertices[vertexIndex1];

    // Verify the primary vertex is unoccupied
    if (mainVertex.getOwnerID() != -1)
    {
        throw runtime_error("Vertex already has an owner.");
    }

    // Check for neighboring vertices ownership
    for (const Vertex *neighbor : mainVertex.getneighborsVertices())
    {
        if (neighbor->getOwnerID() != -1)
        {
            throw runtime_error("Neighboring vertex " + to_string(neighbor->getIndex()) + " is occupied.");
        }
    }

    // Validate the connecting edge availability
    int edgeIdx = getEdgeIndex(vertexIndex1, vertexIndex2);
    if (edgeIdx != -1 && edges[edgeIdx].getOwnerID() != -1)
    {
        throw runtime_error("Edge already has an owner.");
    }

    // Assign the vertex to the player
    mainVertex.setBuilding(Vertex::Building::Settlement, player.getID());

    // Assign the edge to the player
    edges[edgeIdx].setOwnerID(player.getID());

    // Allocate resources to the player based on vertex location
    for (const Plot *plot : mainVertex.getadjPlots())
    {
        string resourceType = plot -> getResource();
        if (resourceType == "Mountains") player.addResource("Ore", 1);
        else if (resourceType == "Pasture") player.addResource("Wool", 1);
        else if (resourceType == "Forest") player.addResource("Wood", 1);
        else if (resourceType == "Agricultural") player.addResource("Wheat", 1);
        else if (resourceType == "Hills") player.addResource("Brick", 1);
    }
    return true;
}


// Check if a settlement can be placed on a vertex
bool Board::canPlaceSettlement(int playerId, size_t vertexIndex)
{
    // Check if vertexIndex is valid
    if (vertexIndex >= vertices.size() || vertexIndex < 0)
    {
        throw out_of_range("Error: vertex index out of range.");
    }

    // Retrieve the vertex using the given index
    Vertex &currentVertex = vertices[vertexIndex];

    // Ensure the vertex is unoccupied by any settlement or city
    if (currentVertex.getBuilding() != Vertex::Building::None)
    {
        throw runtime_error("Error: vertex already occupied.");
    }

    // Ensure neighboring vertices are unoccupied
    const vector<Vertex *> &neighboringVertices = currentVertex.getneighborsVertices();
    for (const Vertex *neighborVertex : neighboringVertices)
    {
        if (neighborVertex->getBuilding() != Vertex::Building::None)
        {
            throw runtime_error("Error: adjacent vertex " + std::to_string(neighborVertex->getIndex()) + " is already taken.");
        }
    }

    // Check for at least one edge connected to the vertex that belongs to the player
    const vector<Edge *> &connectedEdges = currentVertex.getEdgesCover();
    for (const Edge *edge : connectedEdges)
    {
        // If on this edge there is a road of this player return the settlement can be placed on this vertex and set the vertex to be owned by the player
        if (edge->getOwnerID() == playerId)
        {
            currentVertex.setBuilding(Vertex::Building::Settlement, playerId);
            return true;
        }
    }
    throw runtime_error("Error: no connected edges belong to the player.");
}


bool Board::canPlaceCity(int playerId, size_t vertexIndex)
{
    // Check if vertexIndex is valid
    if (vertexIndex >= vertices.size() || vertexIndex < 0)
    {
        throw out_of_range("Error: vertex index out of range.");
    }

    // Retrieve the vertex at the given index
    Vertex &selectedVertex = vertices[vertexIndex];

    // Ensure the vertex is owned by the player
    if (selectedVertex.getOwnerID() != playerId)
    {
        throw runtime_error("Error: Vertex is not owned by the player.");
    }

    // Confirm the vertex is not already a city
    if (selectedVertex.getBuilding() == Vertex::City)
    {
        throw runtime_error("Error: Vertex already has a city.");
    }

    // Mark the vertex as a city and make the vertex owned by the player
    selectedVertex.setBuilding(Vertex::Building::City, playerId);
    return true;
}


// Check if a road can be placed between two vertices
bool Board::canPlaceRoad(int playerId, size_t vertexIndex1, size_t vertexIndex2)
{
    // Verify that the vertex indices are within valid bounds
    if (vertexIndex1 >= vertices.size() || vertexIndex2 >= vertices.size() || vertexIndex1 == vertexIndex2 || vertexIndex1 < 0 || vertexIndex2 < 0)
    {
        throw out_of_range("Error: vertex indices out of range.");
    }

    // Retrieve the vertices using the specified indices
    const Vertex &vertex1 = vertices[vertexIndex1];
    const Vertex &vertex2 = vertices[vertexIndex2];

    // Ensure the vertices are adjacent
    if (!vertex1.isNeighbor(vertex2))
        {
        throw runtime_error("Error: vertices are not adjacent.");
    }

    // Verify the road between these vertices is unoccupied
    const vector<Edge *> &edgesCover1 = vertex1.getEdgesCover();
    const vector<Edge *> &edgesCover2 = vertex2.getEdgesCover();
    for (const Edge *edge1 : edgesCover1)
    {
        for (const Edge *edge2 : edgesCover2)
        {
            if (edge1 == edge2 && edge1->getOwnerID() != -1)
            {
                throw runtime_error("Error: road already taken.");
            }
        }
    }

    // Check if the player owns a settlement or city on either vertex
    if (vertex1.getOwnerID() == playerId || vertex2.getOwnerID() == playerId)
    {
        int edgeIndex = getEdgeIndex(vertexIndex1, vertexIndex2);
        if (edgeIndex != -1) //If there is such an edge
        {
            edges[edgeIndex].setOwnerID(playerId);
        }
        return true;
    }

    // Ensure there is at least one connecting edge owned by the player
    for (const Edge *edge1 : edgesCover1)
    {
        if (edge1->getOwnerID() == playerId)
        {
            int edgeIndex = getEdgeIndex(vertexIndex1, vertexIndex2);
            if (edgeIndex != -1)
            {
                edges[edgeIndex].setOwnerID(playerId);
                return true;
            }
        }
    }
    for (const Edge *edge2 : edgesCover2)
    {
        if (edge2->getOwnerID() == playerId)
        {
            int edgeIndex = getEdgeIndex(vertexIndex1, vertexIndex2);
            if (edgeIndex != -1)
            {
                edges[edgeIndex].setOwnerID(playerId);
                return true;
            }
        }
    }

    throw runtime_error("Error:A road segment can only be connected to a settlement (or city) owned by the player or to another road segment.");
}


// Function to give resources to the players based on the dice roll
void Board::giveResources(vector<Player *> &players, int diceRoll)
{
    for (int i = 0; i < 19; i++)
    {
        if (plots[i].getNumber() == diceRoll)
        {
            cout << "Plot " << i << " number: " << plots[i].getNumber() << endl;
            const vector<Vertex *> &vertices = plots[i].getVertices();
            for (Vertex *currentVertex : vertices)
            {
                if (currentVertex->getBuilding() == Vertex::Building::Settlement)
                {
                    int playerId = currentVertex->getOwnerID();

                    if (plots[i].getResource() == "Mountains")
                    {
                        // give the player who owns the vertex a mountain resource
                        players[playerId - 1]->addResource("Ore", 1);
                    }
                    else if (plots[i].getResource() == "Pasture")
                    {
                        // give the player who owns the vertex a pasture resource
                        players[playerId - 1]->addResource("Wool", 1);
                    }
                    else if (plots[i].getResource() == "Forest")
                    {
                        // give the player who owns the vertex a forest resource
                        players[playerId - 1]->addResource("Wood", 1);
                    }
                    else if (plots[i].getResource() == "Agricultural")
                    {
                        // give the player who owns the vertex an agricultural resource
                        players[playerId - 1]->addResource("Wheat", 1);
                    }
                    else if (plots[i].getResource() == "Hills")
                    {
                        // give the player who owns the vertex a hills resource
                        players[playerId - 1]->addResource("Brick", 1);
                    }
                }

                // A city gives the player 2 times more resources
                else if (currentVertex->getBuilding() == Vertex::Building::City)
                {
                    int playerId = currentVertex->getOwnerID();

                    if (plots[i].getResource() == "Mountains")
                    {
                        // give the player who owns the vertex a mountain resource
                        players[playerId - 1]->addResource("Ore", 2);
                    }
                    else if (plots[i].getResource() == "Pasture")
                    {
                        // give the player who owns the vertex a pasture resource
                        players[playerId - 1]->addResource("Wool", 2);
                    }
                    else if (plots[i].getResource() == "Forest")
                    {
                        // give the player who owns the vertex a forest resource
                        players[playerId - 1]->addResource("Wood", 2);
                    }
                    else if (plots[i].getResource() == "Agricultural")
                    {
                        // give the player who owns the vertex an agricultural resource
                        players[playerId - 1]->addResource("Wheat", 2);
                    }
                    else if (plots[i].getResource() == "Hills")
                    {
                        // give the player who owns the vertex a hills resource
                        players[playerId - 1]->addResource("Brick", 2);
                    }
                }
            }
        }
    }
    cout << "\n" << endl;
}


// Function to draw the top card from the deck and assign it to the player
void Board::drawDevelopmentCard(int playerID)
{
    string cardType = developmentCardsDeck.back().getType();  // Get the type of the top card
    developmentCardsDeck.pop_back(); // Remove the top card from the deck
    players[playerID - 1]->ownedDevelopmentCards.push_back(cardType); // Add the card to the player's hand
}


// Help function to pop some card
void Board::setDevelopmentCardsDeck(const string& typeCard)
{
    for (size_t i=0; i<developmentCardsDeck.size(); i++)
    {
        if (developmentCardsDeck[i].getType() == typeCard)
        {
            developmentCardsDeck.erase(developmentCardsDeck.begin()+i);
            break;
        }
    }
}
