// 207723198
// yair852258@gmail.com

#ifndef EDGE_HPP
#define EDGE_HPP

#pragma once
#include "Vertex.hpp"
class Vertex; // Forward declaration

using namespace std;

class Edge {
public:
    Edge(const Vertex *v1, const Vertex *v2, size_t index);

    // Get the owner's ID of the edge
    int getOwnerID() const;

    // Set the owner's ID of the edge
    void setOwnerID(int newOwner);

    // Get the vertices of the current edge
    const Vertex &getVertex1() const;
    const Vertex &getVertex2() const;

private:
    const Vertex *vertex1;  // Pointer to the first vertex of the edge
    const Vertex *vertex2;  // Pointer to the second vertex of the edge
    size_t index; // Index of the edge
    int owner; // Owner's ID of the edge if there is a road
};




#endif //EDGE_HPP
