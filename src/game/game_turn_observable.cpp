#include "game_turn_observable.h"
#include <iostream>

GameTurnObservable::GameTurnObservable() {
  _observers = new list<GameTurnObserver*>();
}

GameTurnObservable::~GameTurnObservable() {
  _observers->clear();
  delete _observers;
}

void GameTurnObservable::attach(GameTurnObserver* o) {
  _observers->push_back(o);
}

void GameTurnObservable::detach(GameTurnObserver* o) {
  _observers->remove(o);
}
