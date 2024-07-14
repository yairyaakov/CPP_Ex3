// 207723198
// yair852258@gmail.com

#ifndef PLOT_HPP
#define PLOT_HPP

#pragma once
#include <string>
#include "Vertex.hpp"

using namespace std;

class Plot {
public:
    Plot(const string& resource, int number, size_t index);

    string getResource() const;

    int getNumber() const;

    size_t getIndex() const;

    vector<Vertex*> getVertices() const;

    void setVertex(Vertex& vertex);

private:
    string resource;
    int number;
    size_t index;
    vector<Vertex*> vertices;
};



#endif //PLOT_HPP
