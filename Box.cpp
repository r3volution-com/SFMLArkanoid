#include "Box.h"
#include <iostream>

Box::Box(int width, int height, float ini_speed) {
    w = width;
    h = height;
    speed = ini_speed;
}

Box::~Box() {
}

void Box::load(sf::Texture textu, int clipX, int clipY){
    //Copiamos la textura al objeto
    tex = textu;
    
    //Y creo el spritesheet a partir de la imagen anterior
    sprite = sf::Sprite(tex);
    
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(clipX, clipY, w, h));
    
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(w/2,h/2);
}

void Box::setOrigin(float ini_x, float ini_y){
    x = ini_x;
    y = ini_y;
    sprite.setPosition(x, y);
    hitbox = sf::Rect<float>(x-(w/2), y-(h/2), w, h);
}

void Box::setSpeed(float speedy){
    speed = speedy;
}

void Box::move(int xDir, int yDir){
    float moveX = xDir*speed;
    float moveY = yDir*speed;
    x = hitbox.left = hitbox.left + moveX;
    y = hitbox.top = hitbox.top + moveY;
    sprite.move(moveX,moveY);
}

bool Box::checkCollision(sf::Rect<float> other){
    return hitbox.intersects(other);
}