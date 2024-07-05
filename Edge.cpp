// 207723198
// yair852258@gmail.com

#include "Edge.hpp"
#include "Vertex.hpp"

Edge::Edge(const Vertex* v1, const Vertex* v2, size_t index)
    : vertex1(v1), vertex2(v2), index(index), owner(-1) {}

// Get the owner's ID of the edge
int Edge::getOwnerID() const
{
    return owner;
}

// Set the owner's ID of the edge
void Edge::setOwnerID(int newOwner)
{
    owner = newOwner;
}

// Get the vertices of the current edge
const Vertex& Edge::getVertex1() const
{
    return *vertex1;
}

const Vertex& Edge::getVertex2() const
{
    return *vertex2;
}