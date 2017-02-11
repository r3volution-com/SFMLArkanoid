#include "Box.h"
#include <iostream>

Box::Box(int width, int height, float ini_speed) {
    w = width;
    h = height;
    speed = ini_speed;
}

Box::~Box() {
}

void Box::load(const char* texturePath){
    //Cargo la imagen donde reside la textura del sprite
    if (!tex.loadFromFile(texturePath)) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    //Y creo el spritesheet a partir de la imagen anterior
    sprite = sf::Sprite(tex);
    
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(w/2,h/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

void Box::setOrigin(float ini_x, float ini_y){
    x = ini_x;
    y = ini_y;
    sprite.setPosition(x, y);
    hitbox = sf::Rect<float>(x, y, w, h);
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