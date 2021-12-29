#include <queue>
#include <iostream>

using std::cin;
using std::cout;

int main() {
    std::queue<int> first_player, second_player;
    for (int i = 0; i < 5; ++i) {
        int input;
        cin >> input;
        first_player.push(input);
    }
    for (int i = 0; i < 5; ++i) {
        int input;
        cin >> input;
        second_player.push(input);
    }
    int moves = 0;
    while (!first_player.empty() && !second_player.empty() && moves <= 1000001) {
        if (moves != 1000000) {
            int first_card = first_player.front();
            int second_card = second_player.front();
            first_player.pop();
            second_player.pop();
            std::queue<int> *temp_queue;
            if (first_card == 0 && second_card == 9) {
                temp_queue = &first_player;
            } else {
                if (second_card == 0 && first_card == 9) {
                    temp_queue = &second_player;
                } else {
                    temp_queue = (first_card > second_card) ? &first_player : &second_player;
                }
            }
            temp_queue->push(first_card);
            temp_queue->push(second_card);
            ++moves;
        } else {
            cout << "botva";
            return 0;
        }
    }
    if (first_player.empty()) {
        cout << "second " << moves << "\n";
    } else {
        cout << "first " << moves << "\n";
    }
    return 0;
}