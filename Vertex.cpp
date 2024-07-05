// 207723198
// yair852258@gmail.com

#include "Vertex.hpp"

// Constructor
Vertex::Vertex(size_t index) : index(index), owner(-1), building(None)
{}

size_t Vertex::getIndex() const
{
    return index;
}
// Adding a vertex adjacent to the current vertex
void Vertex::addVertexNeighbor(Vertex* vertex)
{
    neighborsVertices.push_back(vertex);
}

// Add the edge which the vertex sits on
void Vertex::addEdge(Edge* edge)
{
    edgesCover.push_back(edge);
}

// Return the ID of the player who own the vertex
int Vertex::getOwnerID() const
{
    return owner;
}

// Get the adjacent vertices
const vector<Vertex*>& Vertex::getneighborsVertices() const {
    return neighborsVertices;
}

// Get edges that the current vertex sits on
const vector<Edge*>& Vertex::getEdgesCover() const
{
    return edgesCover;
}

// Get the building type of the current vertex
Vertex::Building Vertex::getBuilding() const
{
    return building;
}

// Set the building type of the current vertex
void Vertex::setBuilding(Building build, int playerID)
{
    building = build;
    owner = playerID;
}

// Set the vertex to be owned by the player
void Vertex:: setOwner(int playerId)
{
    owner = playerId;
}

// Check if a vertex is a neighbor
bool Vertex::isNeighbor(const Vertex& vertex) const {
    for (const Vertex* neighbor : neighborsVertices) {
        if (neighbor->getIndex() == vertex.getIndex()) {
            return true;
        }
    }
    return false;
}

// Get the adjacent edges
const vector<Edge*>& Vertex::getEdges() const
{
    return edgesCover;
}

// Get the adjacent plots
const vector<Plot*>& Vertex::getadjPlots() const
{
    return adjPlots;
}

//
void Vertex::addAdjPlot(Plot *adjPlot)
{
    adjPlots.push_back(adjPlot);
}

