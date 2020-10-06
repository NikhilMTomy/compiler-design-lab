#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <vector>

#define NULL_STATE 'N'
#define EPSILON 'E'

class State {
	private:
		std::unordered_map<char, std::vector<State*>> transitions;
		const char state;
	public:
		State(const char state);
		void addTransitions(char input, State* nextState);
		std::vector<State*> nextStates(char input);
		std::vector<State*> directNextStates(char input);
		std::vector<State*> epsilonNextStates(char input);
		const char* getName();
};

State::State(const char state) : state(state) {}

void State::addTransitions(char input, State* nextState) {
	if (transitions.find(input) == transitions.end()) {
		std::vector<State*> states;
		states.push_back(nextState);
		transitions[input] = states;
	} else {
		transitions[input].push_back(nextState);
	}
}

std::vector<State*> State::directNextStates(char input) {
    std::vector<State*> states;
	if (transitions.find(input) != transitions.end()) {
        states = transitions[input];
	}
    return states;
}

std::vector<State*> State::epsilonNextStates(char input) {
    std::vector<State*> states;
    if (transitions.find(EPSILON) != transitions.end()) {
        states = transitions[input];
    }
    return states;
}

std::vector<State*> State::nextStates(char input) {
    std::vector<State*> states = directNextStates(input);
    std::vector<State*> epsilonStates = epsilonNextStates(input);

    if (epsilonStates.size() != 0) {
        states.insert(states.end(), epsilonStates.begin(), epsilonStates.end());
    }
    return states;
}

const char* State::getName() {
	return &this->state;
}

const std::vector<char> alphabet = {'0', '1'};
std::vector<State> states;

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
		return nextStates;
	} else {
		for (State* state : nextStates) {
			std::vector<State*> states = process(inputString, position+1, state);
			finalStates.insert(finalStates.end(), states.begin(), states.end());
		}
		return finalStates;
	}
}


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