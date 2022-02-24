# Maximal Snake Generator
A program to generate maximal snakes for research into the snake-in-the-box (https://en.wikipedia.org/wiki/Snake-in-the-box) problem.
The program uses a brute-force algorithm to generate the snakes, and saves them when they are found. There are two implementations, one in Java and one in C++.

In a nutshell: a snake is a path in a graph where vertices on the path are not adjacent to any vertex visited previously. A binary representation of a snake can be used to correct single bit errors since they are Gray codes (https://en.wikipedia.org/wiki/Gray_code). Longer snakes are more useful, thus maximal (non-extendable) snakes are the most desirable. The graph the snakes are being generated on in this program is an n-dimensional hypercube.
