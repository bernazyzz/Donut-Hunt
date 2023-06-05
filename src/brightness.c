#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

void makeFov(Player* player, int cols, int rows, Tile** map, int * linesActions, bool *sawAVine, bool *sawAMonster, bool *sawAnItem){
    int y, x , raio = 25, distancia;
    Position target; // usado para pegar as coordenadas do y e do x 

    map[player->pos.y][player->pos.x].visible = true;
    map[player->pos.y][player->pos.x].seen = true;

    for (y = player->pos.y - raio; y < player->pos.y + raio; y++){  // estes ciclos percorrem todas as posições no mapa que estão dentro do raio de visão do jogador, com base a sua posição atual.
        for (x = player->pos.x - raio; x < player->pos.x + raio; x++){ 
            target.y = y; // posição de destino consoante o raio utilizado
            target.x = x;
            distancia = getDistance(player, target); // calcula a distancia 

           if (distancia < raio){
            if (InMap (y, x, cols, rows) && lineOfSight(player, target, map)){ // verifica se está dentro do mapa e o seu campo de visão
                map[y][x].visible = true;
                map[y][x].seen = true;
                if (map[y][x].ch == '$' && *sawAVine == false) {
                    *linesActions = addActions(cols, "You saw a Vine!", *linesActions,4);
                    *sawAVine = 1;
                }
                if (map[y][x].monster != NULL) {
                    if ((map[y][x].monster->type == 'S' || map[y][x].monster->type == 'G' || map[y][x].monster->type == 'D') && (*sawAMonster == false)) {
                        *linesActions = addActions(cols, "Be careful, a monster!", *linesActions,5);
                        *sawAMonster = 1;
                    }
                }

                if (map[y][x].ch == '?' && *sawAnItem == false) {
                    *linesActions = addActions(cols, "You saw an Item!",*linesActions,map[y][x].item->rarity);
                    *sawAnItem = 1;
                }
            }
           }
        }
    }
}

int getDistance (Player* player, Position target){  // calcula a distancia do jogador a um certo ponto 
    double y, x;
    int distancia;
    y = target.y - player->pos.y;
    x = target.x - player->pos.x;
    distancia = floor(sqrt((x * x) + (y * y)));

    return distancia;
} 

bool InMap(int y , int x, int cols , int rows){  // verifica se está dentro do mapa 
    
    if ((y > 0 && y < rows - 1) && (x > 0 && x < cols - 1)){
        return true;
    }
    return false;
}

bool lineOfSight(Player* player, Position target, Tile** map)
{
    int y = player->pos.y;
    int x = player->pos.x;
    int abs_y = abs(target.y - player->pos.y);  // determina a direção em que a linha vai ser desenhada 
    int abs_x = abs(target.x - player->pos.x);
    int sign_y = (player->pos.y < target.y) ? 1 : -1; // se for menor é definido como 1 que signfica que a linha desenha para baixo se for maior dá -1 e desenha para cima
    int sign_x = (player->pos.x < target.x) ? 1 : -1; // se for menor é definido como 1 que signfica que a linha desenha para esquerda se for maior dá -1 e desenha para direita
    int error = abs_x - abs_y; // usado para determinar  o próximo pixel da linha a ser desenhada   

    while (x != target.x || y != target.y){
        if(!map[y][x].transparent){  // se não for transparente, significa que não há linha de visão entre a posição de origem e a posição de destino, então a função retorna false
            return false;
        }
        int error2 = error * 2; // usado para determinar qual direção seguir na próxima iteração do loop
        if (error2 > -abs_y){ 
            error -= abs_y;
            x += sign_x;  //faz com que a linha siga na direção da coordenada x
        }
        if (error2 < abs_x){
            error += abs_x;
            y += sign_y; // faz com que a linha siga na direção da coordenada y
        }
    }
    return true; // indica que há uma linha de visão entre as duas posições. 
}

void clearFov (Player* player, int cols, int rows, Tile** map){
    int y, x, raio = 26;

    for (y = player->pos.y - raio; y < player->pos.y + raio; y++ ){  // estes ciclos percorrem todas as posições no mapa que estão dentro do raio de visão do jogador, com base a sua posição atual.
        for (x = player->pos.x - raio; x < player->pos.x + raio; x++){
            if (InMap(y, x, cols, rows)) map[y][x].visible = false; // se estiver dentro mapa trocam valor visible = true por false
        }
    }
}

// Will turn the whole map visible for debugging 
void debugMap(Tile ** map, int cols, int rows) {
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      map[y][x].visible = true;
    }
  }
}