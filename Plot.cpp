/// 207723198
// yair852258@gmail.com

#include "Plot.hpp"

Plot::Plot(const string& resource, int number, size_t index)
    : resource(resource), number(number), index(index)
{}

void Plot:: setVertex(Vertex& vertex)
{

    vertices.push_back(&vertex);

}

string Plot::getResource() const
{
    return resource;
}

int Plot::getNumber() const
{
    return number;
}

size_t Plot::getIndex() const
{
    return index;
}

vector<Vertex*> Plot::getVertices() const
{
    return vertices;
}
