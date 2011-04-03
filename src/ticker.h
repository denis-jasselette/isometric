#ifndef _TICKER_H_
#define _TICKER_H_

#include <SFML/System.hpp>

class Ticker {
  public:
    Ticker(int framerateLimit);
    ~Ticker();

    float tick();
    void togglePause();
    void setPause(bool);
    bool isPaused();
    float getFramerate();

  private:
    sf::Clock *clock;
    float framerate;
    int framerateLimit;
    float minDelta;
    bool paused;
};

#endif /* _TICKER_H_ */
