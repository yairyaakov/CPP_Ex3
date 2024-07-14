// 207723198
// yair852258@gmail.com

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include "Edge.hpp"

class Plot; // Forward declaration of the Plot class
class Edge; // Forward declaration of the Edge class


using namespace std;

class Vertex {
public:
    // Represent if there is a settlement or a city on the vertex
    enum Building {None, Settlement, City};

    // Constructor
    explicit Vertex(size_t index);

    // Get the index of the vertex
    size_t getIndex() const;

    // Get the adjacent vertices
    const vector<Vertex*>& getneighborsVertices() const;

    // Get edges that the current vertex sits on
    const vector<Edge*>& getEdgesCover() const;

    // Get the adjacent plots
    const vector<Plot*>& getadjPlots() const;

    // Get the building type of the current vertex
    Building getBuilding() const;

    // Get the ID of the player who own the vertex
    int getOwnerID() const;

    // Adding a vertex adjacent to the current vertex
    void addVertexNeighbor(Vertex* vertex);

    // Add the edge which the vertex sits on
    void addEdge(Edge* edge);

    // Add the plot which the vertex sits on
    void addAdjPlot(Plot *adjPlot);

    // Set the building type of the current vertex
    void setBuilding(Building build, int playerID);

    // Set the vertex to be owned by the player
    void setOwner(int playerId);

    // Check if a vertex is a neighbor
    bool isNeighbor(const Vertex& vertex) const;

private:
    size_t index; // Index of the vertex

    int owner; // ID of the player who owns the vertex, -1 if unowned

    vector<Vertex*> neighborsVertices; // The vertices that are neighbors of the current vertex

    vector<Edge*> edgesCover; // The edges that the current vertex sits on

    Building building; // The building type on the vertex

    vector<Plot*> adjPlots; // The plots that the corrent vertex sits on
};



#endif //VERTEX_HPP
