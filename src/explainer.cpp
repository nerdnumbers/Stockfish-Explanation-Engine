/*
Implementation of Andres Alvarez's Explainer code.
*/
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "explainer.h"
#include "types.h"
#include "thread.h"

using namespace std;

namespace Stockfish
{
  int Explainer::attack_sequence_value(Stockfish::Square square)
  {
  }

  Explainer::Explainer(Stockfish::Position &position) : position_(position){};

  void Explainer::display_threatmap()
  {
    std::string s = "+---+---+---+---+---+---+---+---+\n";

    for (Rank r = RANK_8; r >= RANK_1; --r)
    {
      for (File f = FILE_A; f <= FILE_H; ++f)
      {
        s += "| " + to_string(square_threat_level(make_square(f, r))) + " ";
      }
      s += "| " + std::to_string(1 + r) + "\n+---+---+---+---+---+---+---+---+\n";
    }
    s += "  a   b   c   d   e   f   g   h\n";

    sync_cout << s << sync_endl;
  }

  void Explainer::explain_piece(string &s)
  {
    sync_cout << "Explaining a piece!" << sync_endl;
    sync_cout << position_ << sync_endl;
  }

  vector<Stockfish::Square> Explainer::squares_from_bb(Stockfish::Bitboard bb)
  {
    vector<Stockfish::Square> retSquares;

    for (Stockfish::Rank r = RANK_8; r >= RANK_1; --r)
    {
      for (Stockfish::File f = FILE_A; f <= FILE_H; ++f)
      {
        Square s = make_square(f, r);
        if (bb & s)
        {
          retSquares.push_back(s);
        }
      }
    }

    return retSquares;
  }

  int Explainer::piece_value(Stockfish::Piece piece)
  {
    int pieceNumber = int(piece);
    if (pieceNumber > 7)
    {
      pieceNumber -= 8;
    }

    if (pieceNumber == 1)
    {
      return 1;
    }
    else if (pieceNumber == 2 || pieceNumber == 3)
    {
      return 3;
    }
    else if (pieceNumber == 4)
    {
      return 5;
    }
    else if (pieceNumber == 5)
    {
      return 9;
    }
    else if (pieceNumber == 6)
    {
      return 99;
    }
  }

  int Explainer::square_threat_level(Stockfish::Square square)
  {
    if (position_.piece_on(square))
    {
      int p = (int)position_.piece_on(square);

      Stockfish::Color squareColor = WHITE;

      if (p > 7)
      {
        squareColor = BLACK;
        p -= 8;
      }

      // Show attacks as positive, defenses as negative.
      int threatLevelParity = 1;
      if (squareColor == position_.side_to_move())
      {
        threatLevelParity = -1;
      }

      Stockfish::Bitboard allThreats = position_.attackers_to(square);
      Stockfish::Bitboard attackers = allThreats & position_.pieces(~squareColor);
      Stockfish::Bitboard defenders = allThreats & position_.pieces(squareColor);

      vector<Stockfish::Square> attackingSquares = squares_from_bb(attackers);
      vector<Stockfish::Square> defendingSquares = squares_from_bb(defenders);

      if (attackingSquares.empty())
      {
        return 0;
      }
      else
      {
        int pieceUnderAttackValue = piece_value(position_.piece_on(square));
        int threatLevel = 0;

        vector<int> attackingValues = values_from_squares(attackingSquares);
        vector<int> defendingValues = values_from_squares(defendingSquares);

        sort(attackingValues.begin(), attackingValues.end());
        sort(defendingValues.begin(), defendingValues.end());

        while (!attackingValues.empty())
        {
          if (defendingValues.empty())
          {
            return threatLevelParity * (threatLevel + pieceUnderAttackValue);
          }
          else
          {
            int currentAttackValue = (int)attackingValues.front();
            int currentDefendingValue = (int)defendingValues.front();
            attackingValues.erase(attackingValues.begin());
            defendingValues.erase(defendingValues.begin());

            if (currentAttackValue < pieceUnderAttackValue)
            {
              threatLevel += pieceUnderAttackValue;
              pieceUnderAttackValue = currentDefendingValue;
            }
          }
        }

        return threatLevelParity * threatLevel;
      }
    }
    else
    {
      return 0;
    }
  }

  vector<int> Explainer::values_from_squares(vector<Stockfish::Square> squares)
  {
    vector<int> retValues;
    for (auto &square : squares)
    {
      retValues.push_back(piece_value(position_.piece_on(square)));
    }

    return retValues;
  }
}
