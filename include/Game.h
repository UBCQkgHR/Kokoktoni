#ifndef GAME_H
#define GAME_H
#include "./Level.h"
class Game {

public:
  Game();
  ~Game();

  template <typename T> void checkCollisionX(T &obj, const Level &level) {
    const int TILE = 32;
    auto bounds = obj.getBounds();
    auto &velocity = obj.getVelocity();
    //  sf::FloatRect bounds = obj.sprite.getGlobalBounds();

    int topTile =
        (int)(bounds.top / TILE); // координата по Y(  верхний левый угол)
    int bottomTile = (int)((bounds.top + bounds.height - 1) /
                           TILE); // координата нижне точки по левому краю(
                                  // левый нижний угол )
    if (velocity.x > 0) {
      int rightTile =
          (int)((bounds.left + bounds.width) / TILE); // верхний правый угол
      for (int y = topTile; y <= bottomTile; ++y) {
        int index = y * level.x_size + rightTile;
        if (level.mapColisium[index] == 1) {
          obj.setPosition(rightTile * TILE - bounds.width, bounds.top);
          velocity.x = 0;
          break;
        }
      }
    } else if (velocity.x < 0) {
      int leftTile = (int)(bounds.left / TILE); // координата по Х

      for (int y = topTile; y <= bottomTile; ++y) {
        int index = y * level.x_size + leftTile;
        if (level.mapColisium[index] == 1) {
          obj.setPosition((leftTile + 1) * TILE, bounds.top);
          velocity.x = 0;
          break;
        }
      }
    }
  }

  template <typename T> void checkCollisionY(T &obj, const Level &level) {
    const int TILE = 32;
    auto bounds = obj.getBounds();
    auto &velocity = obj.getVelocity();
    //   sf::FloatRect bounds = obj.sprite.getGlobalBounds();
    int leftTile = (int)(bounds.left / TILE);
    int rightTile = (int)((bounds.left + bounds.width - 1) / TILE);

    if (velocity.y > 0) {
      int bottomTile = static_cast<int>((bounds.top + bounds.height) / TILE);
      for (int x = leftTile; x <= rightTile; ++x) {
        int index = bottomTile * level.x_size + x;
        if (level.mapColisium[index] == 1) {
          obj.setPosition(bounds.left, bottomTile * TILE - bounds.height);
          velocity.y = 0;
          break;
        }
      }
    } else if (velocity.y < 0) {
      int topTile = static_cast<int>(bounds.top / TILE);
      for (int x = leftTile; x <= rightTile; ++x) {
        int index = topTile * level.x_size + x;
        if (level.mapColisium[index] == 1) {
          obj.setPosition(bounds.left, (topTile + 1) * TILE);
          velocity.y = 0;
          break;
        }
      }
    }
  }
};
#endif
