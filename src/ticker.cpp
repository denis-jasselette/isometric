#include "ticker.h"
#include <iostream>

Ticker::Ticker(int framerateLimit) {
  this->framerateLimit = framerateLimit;
  minDelta = 1.0 / framerateLimit;
  framerate = 0;
  clock = new sf::Clock();
  clock->Reset();
  paused = false;
}

Ticker::~Ticker() {
  delete clock;
}

float Ticker::tick() {
  if (paused)
    return -1;

  float timeLeft = minDelta - clock->GetElapsedTime();
  while (timeLeft > 0) {
    sf::Sleep(timeLeft);
    timeLeft = minDelta - clock->GetElapsedTime();
  }

  float delta = clock->GetElapsedTime();
  clock->Reset();
  framerate = .9 * framerate + .1 / delta;
  return delta;
}

void Ticker::togglePause() {
  setPause(!paused);
}

void Ticker::setPause(bool pause) {
  if (paused == pause)
    return;

  if (paused)
    clock->Reset();

  paused = pause;
}

bool Ticker::isPaused() {
  return paused;
}

float Ticker::getFramerate() {
  return framerate;
}
