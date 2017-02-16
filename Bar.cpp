#include "Box.h"
#include "Bar.h"
#include <iostream>

Bar::Bar(int width, int height, float ini_speed) : Box(width, height, ini_speed){
}

void Bar::setOrigin(float ini_x, float ini_y) {
    Box::setOrigin(ini_x, ini_y);
    float w = Box::getW();
    float h = Box::getH();
    float portion = w/3;
    float fixHitboxX = portion/2;
    float fixHitboxY = h/2;
    leftHitbox = sf::Rect<float>(ini_x-portion-fixHitboxX, ini_y-fixHitboxY, portion, h);
    centerHitbox = sf::Rect<float>(ini_x-fixHitboxX, ini_y-fixHitboxY, portion, h);
    rightHitbox = sf::Rect<float>(ini_x+portion-fixHitboxX, ini_y-fixHitboxY, portion, h);
}

void Bar::move(int xDir, int yDir){
    Box::move(xDir, yDir);
    float moveX = xDir*Box::getSpeed();
    leftHitbox.left = leftHitbox.left + moveX;
    centerHitbox.left = centerHitbox.left + moveX;
    rightHitbox.left = rightHitbox.left + moveX;
}

int Bar::checkCollision(sf::Rect<float> other){
    if (leftHitbox.intersects(other)) return 0;
    else if (rightHitbox.intersects(other)) return 2;
    else if (centerHitbox.intersects(other)) return 1;
    else return -1;
}