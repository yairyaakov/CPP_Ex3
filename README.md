# Settlers of Catan Game

## Author
**Ori Yair Yaakov**  
Email: [yair852258@gmail.com](mailto:yair852258@gmail.com)

---

## Table of Contents
1. [Game Rules](#game-rules)
2. [Examples of Validations](#examples-of-validations)
3. [Class Hierarchy](#class-hierarchy)
4. [Libraries Used](#libraries-used)
5. [Usage](#usage)

---

## Game Rules

This implementation follows the rules of the popular board game Settlers of Catan. The game is designed for three players, and the objective is to be the first player to reach a certain number of victory points (10 in this implementation).

1. **Setup**: The game board is initialized with a fixed configuration of 19 plots, each with a specific resource type (Mountains, Pasture, Forest, Agricultural, Hills, or Desert) and a number (2-12, except for the Desert plot). There are 54 vertices and 72 edges on the board.

2. **Initial Placement**: Each player takes turns placing two settlements and two roads on the board. Settlements must be placed on unoccupied vertices that are not adjacent to any other settlements or cities. Roads must connect a player's settlement to another unoccupied vertex. Validations are performed to ensure that the initial placement follows the rules (e.g., `Board::placeInitialSettlementAndRoad`).

3. **Resource Collection**: On each turn, two dice are rolled, and players with settlements or cities adjacent to plots with the corresponding number receive resources based on the plot's resource type. If a 7 is rolled, players with more than 7 cards must discard half of their resources (e.g., `Player::discardResources`).

4. **Development Cards**: Players can draw Development Cards from a deck, which can provide various benefits, such as additional resources, roads, or victory points. The deck consists of Knights, Victory Points, Road Building, Year of Plenty, and Monopoly cards. Validations are performed to ensure that players have the required resources to purchase a Development Card (e.g., `Player::chooseDevelopmentCard`) and that they can properly use the card's effect (e.g., `Player::useKnight`, `Player::useRoadBuilding`).

5. **Building**: Players can use their resources to build new settlements, cities, or roads on the board, following specific placement rules. Validations are performed to ensure that the placements follow the rules (e.g., `Board::canPlaceSettlement`, `Board::canPlaceRoad`, `Board::canPlaceCity`).

6. **Trading**: Players can trade resources with other players. Validations are performed to ensure that both players have the required resources for the trade (e.g., `Player::tradeResources`).

7. **Victory Condition**: The first player to reach 10 victory points (determined by the number of settlements, cities, and Development Cards) wins the game.

## Examples of Validations

- `Board::canPlaceSettlement`: Checks if the vertex is unoccupied, not adjacent to any other settlements or cities, and has at least one adjacent edge owned by the player.
- `Board::canPlaceRoad`: Checks if the two vertices are neighbors, the road is unoccupied, and the player has a settlement or city on one of the vertices or at least one adjacent edge.
- `Board::canPlaceCity`: Checks if the vertex is occupied by the player's settlement and not already a city.
- `Player::chooseDevelopmentCard`, `Player::useKnight`, `Player::useRoadBuilding`, `Player::useYearOfPlenty`, `Player::useMonopoly`: Check if the player has the corresponding Development Card and validate the card's effect.

The implemented validations are designed to adhere strictly to the original game's logic and rules.

## Class Hierarchy

- `Board`: Manages the game board, including plots, vertices, edges, and players. It handles resource distribution, development card drawing, and building placement rules.
- `Plot`: Represents a plot on the board with a specific resource type, number, and vertices.
- `Vertex`: Represents a vertex on the board, which can be occupied by a settlement or city.
- `Edge`: Represents an edge on the board, which can be occupied by a road.
- `Player`: Represents a player in the game, with resources, settlements, cities, roads, and development cards.
- `DevelopmentCard`: Represents a development card with a specific type (Knight, Victory Point, Road Building, Year of Plenty, or Monopoly).

## Libraries Used

The following libraries are used in this implementation:

- `<iostream>`: For input/output operations.
- `<vector>`: For dynamic array storage.
- `<tuple>`: For holding plot data.
- `<algorithm>`: For shuffling the development card deck.
- `<random>`: For generating random numbers for shuffling.
- `<chrono>`: For seeding the random number generator.

## Usage

### Running the Game

To compile and run the project, use the following command:

```bash
make catan
```
This command compiles the project and executes the main catan application.
The game will prompt players for their moves and actions according to the game rules.

### Running Tests

To run tests, use the following command:

```bash
make runtests
```
This command executes all unit tests to ensure the correctness of the tree implementation.

### Cleaning Up Files

To delete files created during compilation and execution, use the following command:

```bash
make clean
```
This command removes executable files and object files, leaving the directory clean.

