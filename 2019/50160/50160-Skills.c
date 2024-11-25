#include <stdbool.h>
#include <stdio.h>

typedef struct attack{
    int damage, extra, coolDown;
    int lastTime;
}Attack;

typedef struct boss{
    int max_health;
    int current_health;
    int regent;
}Boss;

int compute_damage(int round, Attack *attack){
    if(attack->lastTime == -1){
        int bonus = (round > attack->coolDown ? attack->extra * (round - attack->coolDown) : 0);
        return attack->damage + bonus;
    }
    if(round - attack->lastTime < attack->coolDown)
        return 0;
    else
        return attack->damage + attack->extra * (round - attack->lastTime - attack->coolDown);
}

int main(){
    //get input data
    int total_round;
    scanf("%d", &total_round);

    Boss dragon;
    scanf("%d %d", &dragon.max_health, &dragon.regent);
    dragon.current_health = dragon.max_health;

    Attack attack[4] = {0};
    for(int i = 0; i < 3; i++){
        scanf("%d %d %d", &attack[i].damage, &attack[i].extra, &attack[i].coolDown);
        attack[i].lastTime = -1;
    }
    scanf("%d", &attack[3].damage);

    bool win = false;
    for(int round = 0; round < total_round && !win; round++){
        //choose the damage
        int max_index = 0;
        int max_damage = compute_damage(round, &attack[0]);

        for(int i = 1; i < 4; i++){
            int damage = compute_damage(round, &attack[i]);

            if(damage > max_damage){
                max_index = i;
                max_damage = damage;
            }
        }

        //attack
        dragon.current_health -= max_damage;
        //update skill status
        attack[max_index].lastTime = round;

        if(dragon.current_health <= 0)
            win = true;

        //print
        //printf("type %d damage %d rest %d\n", max_index, max_damage, dragon.current_health);
        printf("%d%c", dragon.current_health, " \n"[win]);

        //regent
        dragon.current_health += dragon.regent;
        if(dragon.current_health > dragon.max_health)
            dragon.current_health = dragon.max_health;
    }

    return 0;
}