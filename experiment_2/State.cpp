#include <State.h>

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