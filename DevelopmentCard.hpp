// 207723198
// yair852258@gmail.com

#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>
using namespace std;

class DevelopmentCard {
public:
    explicit DevelopmentCard(const string& type);

    string getType() const;

private:
    string type;
};

#endif //DEVELOPMENTCARD_HPP
