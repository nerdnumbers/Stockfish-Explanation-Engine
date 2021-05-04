# Overview

This sample project is adding one class Stockfish::Explainer and functionality
to the UCI interface to support querying about pieces, moves, and positions.

# Feature Updates

## UI

Initially three new commands will be added, as follows
`explain piece [square]`

`explain move [move]`

`explain position [options]`

## Explain Piece [Square]

Square is expected to be in standard notation, e.g. A1 or a1. For this version
a verbose explanation of the square will be returned using a lot of built
in Stockfish functionality, e.g. attackers, if it is hanging/etc.

## Explain [move]

Given a move, e.g. be2 or e2e4, give anfor

## Explain position [options]

Gives overview of the current positon. Based on the options supplied, specifics
can be given. These are listed below

`explain positions threatmap [options]`

### explain positions threatmap [options]

For the current position a "threatmap" will be rendered. This will be an output
of the board with a number on each square giving the threat level. This will
be based on factors such as how many pieces are attacking the square and if it
is pinned. More information as this map is updated.

# Random Quickfixes

Given the time scale of this project and the admitted rustiness I have in C++
as well as the pretty large domain knowledge base in both Chess Engines
and Stockfish, there are some workarounds or places I can see for obvious
improvement in my solution. I'll keep track of these here.

## Position.h

I am not 100% of the optimization gained by preventing any copying of the
Position object. However, to allow my Explainer Class to easily store a
position, I've temporarily removed it.
