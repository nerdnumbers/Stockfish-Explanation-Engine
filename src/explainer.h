/*
Explainer code written by Andres Alvarez. The purpose of is to be able to
explain various aspects of given pieces/moves/positions of a given chess game.
*/

#ifndef EXPLAINER_H_INCLUDED
#define EXPLAINER_H_INCLUDED
#include <vector>

#include "bitboard.h"
#include "types.h"
#include "position.h"
using namespace std;

namespace Stockfish
{
  class Explainer
  {

  public:
    Explainer(Stockfish::Position &position);

    int attack_sequence_value(Stockfish::Square square);
    int piece_value(Stockfish::Piece piece);
    int square_threat_level(Stockfish::Square square);

    vector<Stockfish::Square> squares_from_bb(Stockfish::Bitboard bb);
    vector<int> values_from_squares(vector<Stockfish::Square> squares);

    void display_threatmap();
    void explain_piece(string &str);

  private:
    Stockfish::Position &position_;
  };
}

#endif