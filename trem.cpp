#include "trem.h"
#include <QtCore>
#include <iostream>

//Construtor
Trem::Trem(int ID, int x, int y, pthread_mutex_t * critic){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->critic = critic;
    velocidade = 120;
}

void Trem::lock(int n) {
    //std::cout << "trem " << ID << " quer o " << n << std::endl;
    pthread_mutex_lock(&critic[n]);
    //std::cout << "trem " << ID << " esta com o " << n << std::endl;
}

void Trem::unlock(int n) {
    pthread_mutex_unlock(&critic[n]);
    //std::cout << "trem " << ID << " soltou o " << n << std::endl;
}

//Função a ser executada após executar trem->START
// somar no x = direita
// somar no y = baixo
// o resto vc entendeu
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 170 && x < 290) {
                if(x == 140) {
                    lock(5);
                    lock(1);
                }
                x+=10;
            }
            else if (x == 290 && y < 290) {
                if(y == 190) {
                    unlock(1);
                }
                y+=10;
            }
            else if (x > 20 && y == 290) {
                if(x == 270) {
                    unlock(5);
                }
                x-=10;
            }
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 170 && x <560){
                x+=10;
            }
            else if (x == 560 && y < 290) {
                y+=10;
            }
            else if (x > 290 && y == 290) {
                x-=10;
            }
            else {
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 170 && x <830) {
                if(x == 580) {
                    unlock(6);
                } else if(x == 720) {
                    unlock(4);
                }
                x+=10;
            }
            else if (x == 830 && y < 290)
                y+=10;
            else if (x > 560 && y == 290) {
                if(x == 580) {
                    lock(4);
                    lock(6);
                }
                x-=10;
            }
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 40 && x <430) {
                if(x == 410) {
                    lock(0);
                }
                x+=10;
            }
            else if (x == 430 && y < 170) {
                if(y == 150) {
                    lock(1);
                    lock(2);
                }
                y+=10;
            }
            else if (x > 160 && y == 170) {
                if(x == 410) {
                    unlock(0);
                } else if (x == 270) {
                    unlock(2);
                }
                x-=10;
            }
            else {
                if(y == 150) {
                    unlock(1);
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 40 && x <700) {
                if(x == 450) {
                    unlock(0);
                }
                x+=10;
            }
            else if (x == 700 && y < 170) {
                if(y == 150) {
                    lock(4);
                }
                y+=10;
            }
            else if (x > 430 && y == 170) {
                if(x == 580) {
                    lock(0);
                    lock(3);
                }
                if(x == 540) {
                    unlock(4);
                }
                x-=10;
            }
            else {
                if(y == 150) {
                    unlock(3);
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }

        while(velocidade == 220);
        msleep(velocidade);
    }
}




