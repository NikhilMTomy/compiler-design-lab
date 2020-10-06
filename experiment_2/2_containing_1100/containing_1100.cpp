#include <iostream>
#include <iomanip>
#include <string>

#include <State.h>
#include <common.h>

const std::vector<char> alphabet = {'0', '1'};
std::vector<State> states;

void initializeState(std::vector<State> &states) {
	states[0].addTransitions('0', &states[0]);
	states[0].addTransitions('1', &states[0]);
	states[0].addTransitions('1', &states[1]);

	states[1].addTransitions('1', &states[2]);

	states[2].addTransitions('0', &states[3]);

	states[3].addTransitions('0', &states[4]);

	states[4].addTransitions('0', &states[4]);
	states[4].addTransitions('1', &states[4]);
}

int main() {
	states.push_back(State('0'));
	states.push_back(State('1'));
	states.push_back(State('2'));
	states.push_back(State('3'));
	states.push_back(State('4'));

	State* finalState = &states[states.size()-1];

	initializeState(states);

	std::string inputString;
	std::cin >> inputString;

	std::vector<State*> finalStates = process(inputString, 0, &states[0]);

	bool accepted = false;
	for (State* state : finalStates) {
		if (state == finalState) {
			accepted = true;
			break;
		}
	}
	if (accepted) {
		std::cout << "Accepted\n";
	} else {
		std::cout << "Not Accepted\n";
	}

	printTransitionTable(alphabet, states);
	std::cout << std::endl;
}