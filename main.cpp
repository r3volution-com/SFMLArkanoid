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
    sf::Texture tex;
    int restantes = 10;
    int ballMoveX = 0;
    int ballMoveY = 1;
    int spacer = 35;
    bool collision = false;
    ostringstream ss;
    
    sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");

    sf::Rect<float> leftWall = sf::Rect<float>(0, 0, 1, 480);
    sf::Rect<float> rightWall = sf::Rect<float>(639, 0, 1, 480);
    sf::Rect<float> topWall = sf::Rect<float>(0, 0, 640, 1);
    sf::Rect<float> bottomWall = sf::Rect<float>(0, 479, 640, 1);
    
    //Cargo la fuente para el texto
    if (!font.loadFromFile("resources/sansation.ttf")){
        std::cerr << "Error cargando la fuente sansation.ttf";
        exit(0);
    }
    
    //Cargo la imagen donde reside la textura del sprite
    if (!tex.loadFromFile("resources/map.png")) {
        std::cerr << "Error cargando la imagen map.png";
        exit(0);
    }
    
    ss << "Bloques restantes: " << restantes;
    
    sf::Text text(ss.str(), font);
    text.setPosition(180, 140);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    
    Bar barra = Bar(100, 25, 5.0f);
    barra.load(tex, 0, 0);
    barra.setOrigin(320, 450);
    
    Box bola = Box(20, 20, 2.0f);
    bola.load(tex, 160, 0);
    bola.setOrigin(320, 200);
    
    Block bloque = Block(60,15,0);
    bloque.load(tex, 100, 0);
    vector<Block> bloques(restantes, bloque);
    for (int i=0; i<bloques.size(); i++){
        bloques[i].setOrigin((60*i)+spacer, 10);
        spacer += 3;
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
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        default:
                        break;
                    }
                break;
                default: break;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if (barra.getX() < 540) barra.move(1, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if (barra.getX() > 0) barra.move(-1, 0);
        }
        int coll = barra.checkCollision(bola.getHitbox());
        if (coll == 0){
            ballMoveY = ballMoveY*-1;
            ballMoveX = ballMoveX*-1;
        } else if (coll == 1){
            ballMoveY = ballMoveY*-1;
            ballMoveX = 0;
        } else if (coll == 2){
            ballMoveY = ballMoveY*-1;
            ballMoveX = ballMoveX*-1;
        } else if (coll == 3){
            ballMoveY = ballMoveY*-1;
            ballMoveX = ballMoveX*-1;
        } else if (coll == 4){
            ballMoveY = ballMoveY*-1;
            ballMoveX = ballMoveX*-1;
        }
        if (bola.checkCollision(topWall)) ballMoveY = ballMoveY*-1;
        if (bola.checkCollision(leftWall)) ballMoveX = ballMoveX*-1;
        if (bola.checkCollision(rightWall)) ballMoveX = ballMoveX*-1;
        if (bola.checkCollision(bottomWall)) {ballMoveY = 0; ballMoveX = 0; }
        bola.move(ballMoveX, ballMoveY);
        
        window.clear();
        window.draw(text);
        window.draw(barra.getSprite());
        window.draw(bola.getSprite());
        
        for (int i=0; i<10; i++){
            if(bloques[i].getActive()) {
                if (bloques[i].checkCollision(bola.getHitbox()) && !collision){
                    collision = true;
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