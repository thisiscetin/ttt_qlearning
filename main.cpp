
#import <thread>
#import <iostream>
#include "trainer.h"

void start_training(trainer *t, std::string game_name) {
    int counter = 0;
    int lastWon = 0;
    int lastLost = 0;
    int lastCheckPoint = 0;
    while (true) {
        counter++;
        t->play();

        if (counter % 500000 == 0) {
            const trainer_stats &s = t->get_stats();
            std::cout << "\n[" << game_name << "]\t";
            std::cout << "agent 0 won %: " << float(s.agent0_won - lastWon) * 100 / float(counter - lastCheckPoint);
            std::cout << ", agent 1 won %: "
                      << float(s.agent1_won - lastLost) * 100 / float(counter - lastCheckPoint);
            std::cout << "\t\t| agent 0 double table (action) size: " << t->get_table_size();

            lastWon = s.agent0_won;
            lastLost = s.agent1_won;
            lastCheckPoint = counter;
        }
    }
}

void play_with_human(agent *a) {
    game *g = new game();

    marker a_marker = a->get_marker();
    marker h_marker = (a_marker == marker::x) ? marker::o : marker::x;
    marker turn = rand() % 2 == 0 ? a_marker : h_marker;

    result r;
    while (true) {
        const std::string state = g->render_board();
        if (turn == a_marker) {
            std::cout << "Max Q was at state: " << a->get_max_Q_at_state(state) << " on action: " << a->play(state, g->get_available_slots()) << std::endl;
            r = g->play(a_marker, a->play(state, g->get_available_slots()));
        } else {
            std::cout << g->render_board() << std::endl;

            int pos;
            std::cout << "\nEnter pos [0-8]: ";
            std::cin >> pos;
            std::cout << std::endl;
            r = g->play(h_marker, pos);
        }

        turn = (turn == a_marker) ? h_marker : a_marker;
        if (r.finished) {
            std::cout << "Finished as below." << std::endl;
            std::cout << g->render_board() << std::endl;

            if (r.winner == a_marker) {
                std::cout << "Agent won!" << std::endl;
            }
            if (r.winner == h_marker) {
                std::cout << "You won!" << std::endl;
            }
            return;
        }
    }
    delete g;
}

int main() {
    strategy *s1 = new strategy{0.5, 0.5, 25};
    agent *a = new agent(marker::x, s1);

    // main agent a is played agains two other agents
    // discovery epsilon is 1/x, if discovery epsilon is 4, 25% of the time agent will make random moves
    // agent b is a dumber than with many random moves agent c
    strategy *s2 = new strategy{0.8, 0.7, 4};
    agent *b = new agent(marker::o, s2);

    strategy *s3 = new strategy{0.9, 0.6, 10};
    agent *c = new agent(marker::o, s3);


    trainer *t0 = new trainer(a, b);
    trainer *t1 = new trainer(a, c);

    std::thread th0(start_training, t0, "agent a vs. b");
    std::thread th1(start_training, t1, "agent a vs. c");

    while (true) {
        try {
            play_with_human(a);
        }
        catch (const std::exception &ex) {
            std::cout << "Error game restarted due to: " << ex.what() << "\n\n";
        }
    }
    th0.join();
    th1.join();

    return 0;
}

