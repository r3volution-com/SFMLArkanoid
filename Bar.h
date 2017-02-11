#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>

class Box;

class Bar : public Box {
private:
    sf::Rect<float> leftHitbox;
    sf::Rect<float> centerHitbox;
    sf::Rect<float> rightHitbox;
    
public:
    Bar(int width, int height, float ini_speed);
    
    void setOrigin(float ini_x, float ini_y);
    void move(int xDir, int yDir);
    int checkCollision(sf::Rect<float> other);
};

#endif /* BAR_H */