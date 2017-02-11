/* 
 * File:   Box.h
 * Author: mario
 *
 * Created on 10 de febrero de 2017, 20:44
 */

#ifndef BOX_H
#define BOX_H

#include <SFML/Graphics.hpp>

class Box {
private:
    int w, h;
    float x, y;
    float speed;
    
    sf::Texture tex;
    sf::Sprite sprite;
    sf::Rect<float> hitbox;
public:
    Box(int width, int height, float ini_speed);
    virtual ~Box();
    
    void setOrigin(float ini_x, float ini_y);
    void setSpeed(float speedy);
    void load(const char* texturePath);
    void move(int xDir, int yDir);
    bool checkCollision(sf::Rect<float> other);
    
    float getX() { return x; }
    float getY() { return y; }
    int getW() { return w; }
    int getH() { return h; }
    int getSpeed() { return speed; }
    sf::Sprite getSprite(){ return sprite; }
    sf::Rect<float> getHitbox() {return hitbox; }
};

#endif /* BOX_H */

