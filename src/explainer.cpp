/*
Implementation of Andres Alvarez's Explainer code.
*/
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "explainer.h"
#include "thread.h"

using namespace std;

namespace Stockfish
{
  Explainer::Explainer(Stockfish::Position &position) : position_(position){};

  void Explainer::explain_piece(Stockfish::Square square)
  {
    sync_cout << "Explaining a piece!" << sync_endl;
    sync_cout << position_ << sync_endl;
  }
}
