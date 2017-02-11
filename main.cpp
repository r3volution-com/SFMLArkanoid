/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mario
 *
 * Created on 10 de febrero de 2017, 20:44
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Box.h"
#include "Bar.h"
#include "Block.h"

using namespace std;

int main() {
    //Creamos una ventana 
    sf::Font font;
    sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");

    sf::Rect<float> leftWall = sf::Rect<float>(0, 0, 1, 480);
    sf::Rect<float> rightWall = sf::Rect<float>(639, 0, 1, 480);
    sf::Rect<float> topWall = sf::Rect<float>(0, 0, 640, 1);
    sf::Rect<float> bottomWall = sf::Rect<float>(0, 479, 640, 1);
    
    font.loadFromFile("resources/sansation.ttf");
    
    int restantes = 10;
    
    std::ostringstream ss;
    ss << "Bloques restantes: " << restantes;
    
    sf::Text text(ss.str(), font);
    //text.setOrigin(320,240);
    text.setPosition(180, 140);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    
    Bar barra = Bar(100, 25, 5.0f);
    barra.load("resources/bar.png");
    barra.setOrigin(320, 450);
    
    int ballMoveX = 0;
    int ballMoveY = 1;
    Box bola = Box(20, 20, 2.0f);
    bola.load("resources/ball.png");
    bola.setOrigin(320, 200);
    
    Block bloque = Block(58,15,0);
    bloque.load("resources/block.png");
    std::vector<Block> bloques(restantes, bloque);
    int spacer = 35;
    for (int i=0; i<bloques.size(); i++){
        bloques[i].setOrigin((58*i)+spacer, 10);
        spacer += 5;
    }
    
    window.setFramerateLimit(60);
    
    //Bucle del juego
    while (window.isOpen()) {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        //Mapeo del cursor
                        case sf::Keyboard::Right:
                            if (barra.getX() < 590) barra.move(1, 0);
                        break;
                        case sf::Keyboard::Left:
                            if (barra.getX() > 50) barra.move(-1, 0);
                        break;
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                    }
                break;
                default: break;
            }
        }
        int coll = barra.checkCollision(bola.getHitbox());
        if (coll == 0){
            ballMoveY = -1;
            ballMoveX = -1;
        } else if (coll == 1){
            ballMoveY = -1;
            ballMoveX = 0;
        } else if (coll == 2){
            ballMoveY = -1;
            ballMoveX = 1;
        }
        if (bola.checkCollision(topWall)) ballMoveY = 1;
        if (bola.checkCollision(leftWall)) ballMoveX = 1;
        if (bola.checkCollision(rightWall)) ballMoveX = -1;
        if (bola.checkCollision(bottomWall)) {ballMoveY = 0; ballMoveX = 0; }
        bola.move(ballMoveX, ballMoveY);
        
        window.clear();
        window.draw(text);
        window.draw(barra.getSprite());
        window.draw(bola.getSprite());
        
        for (int i=0; i<10; i++){
            if(bloques[i].getActive()) {
                if (bloques[i].checkCollision(bola.getHitbox())){
                    ballMoveY = 1;
                    bloques[i].disable();
                    restantes--;
                    ss.str(std::string());
                    ss << "Bloques restantes: " << restantes;
                    text.setString(ss.str());
                    bola.setSpeed(bola.getSpeed()+0.1f);
                }
                window.draw(bloques[i].getSprite());
            }
        }
        window.display();
    }
    return 0;
}