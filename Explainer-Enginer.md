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

Given a move, e.g. be2 or e2e4, give analysis behind if the move is good/bad,
if it is part of a SEE attack.

## Explain position [options]

Gives overview of the current positon. Based on the options supplied, specifics
can be given. These are listed below

`explain positions threatmap [options]`

Given this state has many many places to go, more options can easily be added,
per the initial email, things such as move suggestions in order, moves to avoid,
etc.

### explain positions threatmap [options]

For the current position a "threatmap" will be rendered. This will be an output
of the board with a number on each square giving the threat level. This will
be based on factors such as how many pieces are attacking the square and if it
is pinned. More information as this map is updated. The most recent iteration
simply examines how much value is gained/lost by exchanging until a "weaker"
defender holds off the attack (e.g. a piece is guarded by a pawn) or until
defenders are exhausted. The total value returned is the value of lost pieces.

# Random Quickfixes

Given the time scale of this project and the admitted rustiness I have in C++
as well as the pretty large domain knowledge base in both Chess Engines
and Stockfish, there are some workarounds or places I can see for obvious
improvement in my solution. I'll keep track of these here.

## Position.h

I am not 100% of the optimization gained by preventing any copying of the
Position object. However, to allow my Explainer Class to easily store a
position, I've temporarily removed it.

# Useful Positions

FEN of hung bishop
r1bqk2r/pp2bppp/2pp1n2/3B2B1/3QP3/2N5/PPP2PPP/R3K2R b KQkq - 1 9

FEN of previous position that shows off hung pieces on both sdes.
r1bqk2r/pp2bppp/2pp4/3n2B1/3QP3/2N5/PPP2PPP/R3K2R w KQkq - 0 10

Fun FEN to show off attackers/defenders with skewer points too.
r6q/p1kb1p2/QppR1P2/4n3/N3P3/1B6/PPP3Pr/2KR4 w - - 6 25
