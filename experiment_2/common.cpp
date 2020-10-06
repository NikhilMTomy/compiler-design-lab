#include <common.h>

void printTransitionTable(const std::vector<char> &alphabet, std::vector<State> &states) {
	int maxLen = (alphabet.size() * 11) + 12;
	std::cout << "\nTransition Table\n" << std::left;


	std::cout << std::setfill('-') << std::setw(maxLen) << "-" << std::setfill(' ') << "\n";


	std::cout << "|" << std::setw(10) << "State" << "|";
	for (const char &c : alphabet) {
		std::cout << std::setw(10) << c << "|";
	}
	std::cout << "\n";


	std::cout << std::setfill('-') << std::setw(maxLen) << "-" << std::setfill(' ') << "\n";


	for (State &state : states) {
		std::cout << "|" << std::setw(10) << std::string("q") + std::string(state.getName()) << "|";

		for (const char &c : alphabet) {
			std::vector<State*> nextStates = state.nextStates(c);
			std::string stateString;

			for (State *nextState : nextStates) {
				stateString += "q";
				stateString += nextState->getName();
				stateString += " ";
			}
			if (stateString.empty()) {
				stateString += NULL_STATE;
			}

			std::cout << std::setw(10) << stateString << "|";
		}

		std::cout << "\n";
	}


	std::cout << std::setfill('-') << std::setw(maxLen) << "-" << std::setfill(' ') << "\n";


	std::cout << std::right;
}

std::vector<State*> process(const std::string &inputString, int position, State* currentState) {
	std::vector<State*> nextStates = currentState->nextStates(inputString[position]);
	std::vector<State*> finalStates;

	

	if (position == inputString.length() - 1) {

		/*
		std::cout << "Current State : " << currentState->getName() << " Input : " << inputString[position] << " Position  : " << position << std::endl;
		std::cout << "Next States   : ";
		for (State* state : nextStates) {
			std::cout << state->getName() << " ";
		}
		std::cout << "\n\n";
		*/

		return nextStates;
	} else {
		for (State* state : nextStates) {
			std::vector<State*> states = process(inputString, position+1, state);
			finalStates.insert(finalStates.end(), states.begin(), states.end());
		}

		/*
		std::cout << "Current State : " << currentState->getName() << " Input : " << inputString[position] << " Position  : " << position << std::endl;
		std::cout << "Next States   : ";
		for (State* state : nextStates) {
			std::cout << state->getName() << " ";
		}
		std::cout << "\n\n";
		*/

		return finalStates;
	}
}
