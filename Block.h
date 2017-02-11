/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Block.h
 * Author: mario
 *
 * Created on 11 de febrero de 2017, 14:10
 */

#ifndef BLOCK_H
#define BLOCK_H

class Box;

class Block : public Box {
private:
    bool active = true;
    
public:
    Block(int width, int height, float ini_speed);
    
    void disable(){ active = false; }
    bool getActive() { return active; }
};

#endif /* BLOCK_H */

