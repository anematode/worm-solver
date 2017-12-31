# worm-solver

## Introdution

Consider a puzzle consisting of a string of uniformly sized cubes. Every couple of blocks the string turns and provides a plane of rotation. Here's an actual image of one of these puzzles:

<img src="https://i.imgur.com/v9FCo73.jpg" width=500></img>
<br>
<br>
Figure 1: An unsolved worm puzzle.

The coloring is impertinent here. The target of the puzzle is to assemble it into a cube, like so:

<img src="https://i.imgur.com/uJZi0XF.jpg" width=500></img>
<br>
<br>
Figure 2: A solved worm puzzle.

By the way, if you know what these puzzles are called, please tell me!

## Input

Anyway, the solver tells us instructions on how to solve these types of puzzles. To use it, first lay out the puzzle like so:

<img src="https://i.imgur.com/tu9BKWE.jpg" width=500></img>
<br>
<br>
Figure 3: A layed-out worm puzzle.

Notice that the puzzle is grouped in small pieces. In this case, the lengths of each of the pieces, including the corners, is 3, 2, 2, 3, 2, 3, 2, 2, ... etc.

To input your puzzle into the program, input these numbers into main.cc at line 8. You should also update the count of these lengths at line 7. If your puzzle is bigger, say, 4 x 4 or 5 x 5, you can change the puzzle size at line 5.

## Running the Program

To run the program, simply run

```make```

in the project directory, which will produce an executable called main that you can run.

## The Output

The output will give you the path the puzzle takes, starting at the beginning of the puzzle (where you started inputting your lengths from). These paths are given in their length and their cardinal direction.

#### Sample Output

The output for this puzzle is:

```
Solution:

Worm starts at 0, 0, 0 facing X+.
Travel 3 units in direction X+.
Travel 3 units in direction Y+.
Travel 3 units in direction X+.
Travel 3 units in direction Y-.
Travel 2 units in direction Z+.
Travel 2 units in direction Y+.
Travel 2 units in direction Z-.
Travel 3 units in direction Y+.
Travel 3 units in direction X-.
Travel 2 units in direction Y-.
Travel 2 units in direction Z+.
Travel 3 units in direction X+.
Travel 2 units in direction Z-.
Travel 3 units in direction Y+.
Travel 2 units in direction Z+.
Travel 2 units in direction X-.
Travel 3 units in direction Y+.
Travel 0 units in direction X+.
```

## The Algorithm

The algorithm is very basic. We have a Shape class denoting a partially-solved object. Simple recursion just tries all possible worm configurations (DFS).
