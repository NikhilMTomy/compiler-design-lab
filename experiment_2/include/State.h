#ifndef __STATE_H__
#define __STATE_H__

#define NULL_STATE 'N'
#define EPSILON 'E'

#include <unordered_map>
#include <vector>

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

#endif