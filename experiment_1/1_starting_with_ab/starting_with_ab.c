// ^ab.*$
#include <stdio.h>

#define BUFF_SIZE 16
#define TRANSITION_SIZE 8
#define FINAL_STATE 2
#define DEAD_STATE -1

struct Transition {
    int initialState;
    char symbol;
    int nextState;
} transitions[TRANSITION_SIZE] = {
    {0, 'a', 1},
    {0, 'b', DEAD_STATE},

    {1, 'a', DEAD_STATE},
    {1, 'b', 2},

    {2, 'a', 2},
    {2, 'b', 2},

    {-1, 'a', -1},
    {-1, 'b', -1},
};

int main() {
    char input[BUFF_SIZE];
    int i = 0, currentState = 0;

    scanf("%s", input);

    printf("\nTransitions");
    printf("\n%d", currentState);

    for (i=0; input[i] != '\0' && currentState != DEAD_STATE; i++) {
        for (int j=0; j<TRANSITION_SIZE; j++) {
            if (transitions[j].initialState == currentState && transitions[j].symbol == input[i]) {
                currentState = transitions[j].nextState;
                break;
            }
        }
        printf(" -> %d", currentState);
    }

    if (currentState == FINAL_STATE) {
        printf("\nString accepted\n");
    } else {
        printf("\nString not accepted\n");
    }

    printf("\nTransition table\n");
    printf("%10s %10s %10s\n", "State", "a", "b");
    for (i=0; i<TRANSITION_SIZE; i+=2) {
        printf("%10d %10d %10d\n", transitions[i].initialState, transitions[i].nextState, transitions[i+1].nextState);
    }
}