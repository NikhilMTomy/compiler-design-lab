#include <iostream>
#include <iomanip>
#include <vector>

#include <State.h>

void printTransitionTable(const std::vector<char> &alphabet, std::vector<State> &states);
std::vector<State*> process(const std::string &inputString, int position, State* currentState);