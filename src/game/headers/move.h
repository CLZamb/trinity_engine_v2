#ifndef MOVE_H
#define MOVE_H

#include <cassert>
#include "../../common/headers/utils.h"

/*
   0000 0000 0000 0000 0000 0011 1111 -> From 0x3F
   0000 0000 0000 0000 1111 1100 0000 -> To >> 6, 0x3F
   0000 0000 0000 1111 0000 0000 0000 -> Captured >> 12, 0xF
   0000 0000 0001 0000 0000 0000 0000 -> EnPessant >> 16, 0x1
   0000 0001 1110 0000 0000 0000 0000 -> Piece >> 17, 0xF
   0001 1110 0000 0000 0000 0000 0000 -> Promoted Piece >> 21, 0xF
   0010 0000 0000 0000 0000 0000 0000 -> Castle >> 25, 0x1
   */

class Move {
  public:
    Move() {}
    explicit Move(unsigned int m) : m_move(m) { }
    Move(int m) : m_move(m) {}
    Move(unsigned int from, unsigned int to, unsigned int type) {
      m_move = (from & 0x3f) | ((to & 0x3f) << 6) | ((type & 0xf) << 17);
    }
    Move(unsigned int from, unsigned int to, unsigned int type, unsigned int captured) {
      m_move = (from & 0x3f) | ((to & 0x3f) << 6) | ((captured << 0xf) & 12) | ((type & 0xf) << 17);
    }

    unsigned int get_move() { return m_move; }

    SquareIndices get_from() const {
      return static_cast<SquareIndices>(m_move & 0x3f);
    }

    SquareIndices get_to() const {
      return static_cast<SquareIndices>((m_move >> 6) & 0x3f);
    }

    Piecetype get_captured_piece() const {
      return static_cast<Piecetype>((m_move >> 12) & 0xf);
    }

    bool is_en_passant() const {
      return ((m_move >> 16) & 0x1);
    }

    Piecetype get_piece() const {
      return static_cast<Piecetype>((m_move >> 17) & 0xf);
    }

    Piecetype get_promoted_piece() const {
      return static_cast<Piecetype>((m_move >> 21) & 0xf);
    }

    bool is_castle() const {
      return ((m_move >> 25) & 0x1);
    }

    void set_from(unsigned int from) {
      m_move &= ~0x3f;
      m_move |= (from & 0x3f);
      assert(from == (m_move & 0x3f));
    }

    void set_to(unsigned int to) {
      m_move &= ~0xfc0;
      m_move |= (to & 0x3f) << 6;
      assert(to == ((m_move >> 6) & 0x3f));
    }

    void set_move(unsigned int from, unsigned int to, unsigned int type) {
      m_move = (from & 0x3f) | ((to & 0x3f) << 6) | ((type & 0xf) << 17);
    }

    void set_move(unsigned int from, unsigned int to) {
      m_move = (from & 0x3f) | ((to & 0x3f) << 6);
    }    void set_move(unsigned int m) { m_move = m; }

    void set_capture_piece(unsigned int piece) {
      m_move &= ~0xf000;
      m_move |= ((piece & 0xf) << 12);
    }

    void set_piece(unsigned int piece) {
      m_move &= ~0x1e0000;
      m_move |= ((piece & 0xf) << 17);

      assert(piece == ((m_move >> 17) & 0xf));
    }

    void set_en_passant(bool en_pessant) {
      m_move &= ~0x10000;
      m_move |= ((en_pessant & 0x1) << 16);
    }

    void set_promoted_piece(unsigned int piece) {
      m_move &= ~0x1e00000;
      m_move |= ((piece & 0xf) << 21);
    }

    void set_is_castle(bool is_castle) {
      m_move &= ~0x2000000;
      m_move |= ((is_castle & 0x1) << 25);
    }

    bool operator==(Move a) const {
      return (m_move & 0xffff) == (a.m_move & 0xffff);
    }

    bool operator!=(Move a) const {
      return (m_move & 0xffff) != (a.m_move & 0xffff);
    }

 private:
    unsigned int m_move;  // or short or template type
};

typedef std::vector<Move> MoveList;

#endif /* MOVE_H */
