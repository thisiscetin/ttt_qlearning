#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "easy_game.h"

int main() {
    agent *a = new agent(0.5, 0.5);

    for (int i = 0; i < 10000000; i++) {
        easy_game g = easy_game(1 + rand() % 7);

        bool finished = false;
        int k = 0;
        while (!finished && k != 100) {
            k++;
            const std::string state = g.render();
            direction d = a->play(state);

            if (rand() % 2 == 0 && i % 100000 != 0) {
                d = (d == direction::left) ? direction::right : direction::left;
            }
            long double reward = g.play(d);

            const std::string next_state = g.render();
            a->feedback(state, next_state, d, reward);
            finished = g.get_finished();

            if (i % 100000 == 0)
                std::cout << g.render() << " r:" << reward <<
                          " mqL:" << a->t->get_Q_at_action(g.render(), direction::left) <<
                          " mqR:" << a->t->get_Q_at_action(g.render(), direction::right) << std::endl;
        }
        k = 0;
        if (i % 100000 == 0)
            std::cout << "end" << std::endl;
    }

    return 0;
}




//#import <thread>
//#include "trainer.h"
//
//void start_training(trainer* t) {
//    int counter = 0;
//    int lastWon = 0;
//    int lastLost = 0;
//    int lastCheckPoint = 0;
//    while (true) {
//        counter++;
//        t->play();
//
//        if (counter % 500000 == 0) {
//            const trainer_stats &s = t->get_stats();
//            std::cout << "agent won %: " << float(s.agent_won - lastWon) * 100 / float(counter - lastCheckPoint);
//            std::cout << ", agent lost %: " << float(s.dummy_agent_won - lastLost) * 100 / float(counter - lastCheckPoint);
//            std::cout << "  | table (action) size: " << t->get_table_size() << std::endl;
//
//            lastWon = s.agent_won;
//            lastLost = s.dummy_agent_won;
//            lastCheckPoint = counter;
//        }
//    }
//}
//
//void play_with_human(agent* a) {
//    game g = game();
//
//    marker a_marker = a->get_marker();
//    marker h_marker = (a_marker == marker::x) ? marker::o : marker::x;
//    marker turn = a_marker;
//
//    result r;
//    while (true) {
//        const std::string state = g.render_board();
//        if (turn == a_marker) {
//            std::cout << "Max Q at action: " << a->get_max_Q_at_state(state) << std::endl;
//            r = g.play(a_marker, a->play(state, g.get_available_slots()));
//        } else {
//            std::cout << g.render_board() << std::endl;
//
//            int pos;
//            std::cout << "Enter pos: ";
//            std::cin >> pos;
//            std::cout << std::endl;
//            r = g.play(h_marker, pos);
//        }
//
//        turn = (turn == a_marker) ? h_marker : a_marker;
//        if (r.finished) {
//            std::cout << "Finished as below." << std::endl;
//            std::cout << g.render_board() << std::endl;
//
//            if (r.winner == a_marker) {
//                std::cout << "Agent won!" << std::endl;
//                a->learn(state, g.render_board(), a->play(state, g.get_available_slots()), 100.0);
//            }
//            if (r.winner == h_marker) {
//                std::cout << "You won!" << std::endl;
//                a->learn(state, g.render_board(), a->play(state, g.get_available_slots()), -100.0);
//            }
//            return;
//        }
//    }
//}
//
//int main() {
//    strategy* s = new strategy {0.9, 0.9, 4};
//    agent* a = new agent(marker::x, s);
//    dummy_agent* d0 = new dummy_agent();
//
//    trainer* t0 = new trainer(a, d0);
////    trainer* t1 = new trainer(a, d1);
////    std::thread th0(start_training, t0);
////    std::thread th1(start_training, t1);
//    start_training(t0);
//
////    while (true) {
////        try {
////            play_with_human(a);
////        }
////        catch (const std::exception& ex) {
////            std::cout << "Error game restarted due to: " << ex.what() << "\n\n";
////        }
////    }
//
////    th0.join();
////    th1.join();
//
//    return 0;
//}

