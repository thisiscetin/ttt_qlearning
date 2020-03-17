#include <iostream>
#include "trainer.h"

int main() {
    strategy* s = new strategy {0.5, 0.5, 20};
    agent* a = new agent(marker::x, s);
    dummy_agent* d = new dummy_agent();

    trainer* t = new trainer(a, d);

    int counter = 0;
    int lastWon = 0;
    int lastLost = 0;
    int lastCheckPoint = 0;
    while (true) {
        counter++;
        t->play();

        if (counter % 100000 == 0) {
            const trainer_stats &s = t->get_stats();
            std::cout << "agent won %: " << float(s.agent_won - lastWon) * 100 / float(counter - lastCheckPoint);
            std::cout << ", agent lost %: " << float(s.dummy_agent_won - lastLost) * 100 / float(counter - lastCheckPoint);
            std::cout << "  | table (action) size: " << t->get_table_size() << std::endl;

            lastWon = s.agent_won;
            lastLost = s.dummy_agent_won;
            lastCheckPoint = counter;
        }
    }
    return 0;
}

