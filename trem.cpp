#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y, pthread_mutex_t * critic){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->critic = critic;
    velocidade = 120;
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
                    pthread_mutex_lock(&critic[1]);
                    pthread_mutex_lock(&critic[5]);
                }
                x+=10;
            }
            else if (x == 290 && y < 290) {
                if(y == 190) {
                    pthread_mutex_unlock(&critic[1]);
                }
                y+=10;
            }
            else if (x > 20 && y == 290) {
                if(x == 270) {
                    pthread_mutex_unlock(&critic[5]);
                }
                x-=10;
            }
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 170 && x <560)
                x+=10;
            else if (x == 560 && y < 290)
                y+=10;
            else if (x > 290 && y == 290)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 170 && x <830) {
                if(x == 580) {
                    pthread_mutex_unlock(&critic[6]);
                } else if(x == 720) {
                    pthread_mutex_unlock(&critic[4]);
                }
                x+=10;
            }
            else if (x == 830 && y < 290)
                y+=10;
            else if (x > 560 && y == 290) {
                if(x == 580) {
                    pthread_mutex_lock(&critic[4]);
                    pthread_mutex_lock(&critic[6]);
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
                    pthread_mutex_lock(&critic[0]);
                }
                x+=10;
            }
            else if (x == 430 && y < 170) {
                if(y == 150) {
                    pthread_mutex_lock(&critic[1]);
                    pthread_mutex_lock(&critic[2]);
                }
                y+=10;
            }
            else if (x > 160 && y == 170) {
                if(x == 410) {
                    pthread_mutex_unlock(&critic[0]);
                } else if (x == 270) {
                    pthread_mutex_unlock(&critic[2]);
                }
                x-=10;
            }
            else {
                if(y == 150) {
                    pthread_mutex_unlock(&critic[1]);
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 40 && x <700) {
                if(x == 450) {
                    pthread_mutex_unlock(&critic[0]);
                }
                x+=10;
            }
            else if (x == 700 && y < 170) {
                if(y == 150) {
                    pthread_mutex_lock(&critic[4]);
                }
                y+=10;
            }
            else if (x > 430 && y == 170) {
                if(x == 580) {
                    pthread_mutex_lock(&critic[3]);
                    pthread_mutex_lock(&critic[0]);
                }
                if(x == 540) {
                    pthread_mutex_unlock(&critic[4]);
                }
                x-=10;
            }
            else {
                if(y == 150) {
                    pthread_mutex_unlock(&critic[3]);
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




