// 207723198
// yair852258@gmail.com

#include "DevelopmentCard.hpp"

DevelopmentCard::DevelopmentCard(const string& type) : type(type) {}

string DevelopmentCard::getType() const {
    return type;
}