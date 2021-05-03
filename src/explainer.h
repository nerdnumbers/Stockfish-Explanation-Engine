/*
Explainer code written by Andres Alvarez. The purpose of is to be able to
explain various aspects of given pieces/moves/positions of a given chess game.
*/

#ifndef EXPLAINER_H_INCLUDED
#define EXPLAINER_H_INCLUDED

#include "types.h"
#include "position.h"

namespace Stockfish
{
  class Explainer
  {

  public:
    Explainer(Stockfish::Position &position);
    void explain_piece(Stockfish::Square square);

  private:
    Stockfish::Position &position_;
  };
}

#endif