# TicTacToe game with Double Q-Learning

Aim of this project to build a model-free reinforcement learning algorithm (QLearning) that can play tic tac toe 
better than a human does. When application runs, agent starts playing agains in two other agents. One opponent agent picks highly random moves while the other one makes a bit smarter moves.

At the same time you can play against the agent, by using numbers on the board between [0, 8]. 0 refers to the (1, 1) cell in the tictactoe board while 8 refers to (3, 3).

## Building

```
> cmake . && make
```
This command should create a binary in `bin/` folder name `game`.

## Running the game
After running the command from the root folder,

```
> bin/game
```

You will generate 3 agents playing TicTacToe.
- Agent A will be playing with Agent B.
- Agent A will be playing with Agent C.

And you will be promted to enter a number to mark on the board. While training you can play against Agent A yourself and see the improvement.

```
[agent a vs. b]	agent 0 won %: 58.547, agent 1 won %: 41.0874		| agent 0 double table (action) size: 29936
[agent a vs. c]	agent 0 won %: 51.6226, agent 1 won %: 48.2668		| agent 0 double table (action) size: 30034

-o-
xo-
x--


Enter pos [0-8]: 
```

While training continues you can play the game in an infinite loop.

# References
- [Double Q-Learning](https://towardsdatascience.com/double-q-learning-the-easy-way-a924c4085ec3)
- [Wikipedia Q-learning](https://en.wikipedia.org/wiki/Q-learning)
- [Wikipedia Tic Tac Toe](https://en.wikipedia.org/wiki/Tic-tac-toe)
