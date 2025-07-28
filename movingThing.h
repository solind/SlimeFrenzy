#pragma once
#include "raylib.h"
#include <random>
#include <vector>

class movingThing{
    public:
    Texture2D sprite;
    float x, y;
    Vector2 player;
    int speed;


    movingThing(){
        x = 0;
        y = 0;
        speed = 5;
        player = {0, 0};
        sprite = LoadTexture("resources/witch.PNG");
    }
    movingThing(float a, float b, int c, const char* image){
        x = a;
        y = b;
        speed = c;
        player = {x, y};
        sprite = LoadTexture(image);
        }
    
    virtual ~movingThing() {
    //UnloadTexture(sprite);
    }




    bool move(int direction){
        switch(direction){
            case 1:
                x+= speed;
                break;
            case 2:
                x-= speed;
                break;
            case 3:
                y+= speed;
                break;
            case 4:
                y-=speed;
                break;
            default :
                break;
        }
        return true;
    }

    void draw(){
        DrawTexture(sprite, x, y, WHITE);
    }
    virtual void changeSprite(const char* pic){
        UnloadTexture(sprite);
        sprite = LoadTexture(pic);
    }
};

class Player : public movingThing{
    public:
    int w, h;
    int health, damage, level;
    float maxHealth;
    Rectangle hitbox;
    Player() : movingThing(200, 750, 5, "resources/rightWitch.PNG"){
        w = 90;
        h=128;
        level = 1;
        health = 100;
        maxHealth = 100;
        damage = 5;
        hitbox = {x, y, (float)w, (float)h};
    }

    ~Player() override = default;

    void moveBox(){
        hitbox = {x, y, (float)w, (float)h};
    }
    void levelUp(){
        level++;
        maxHealth+=20;
        health = maxHealth;
        damage++;
        speed++;
    }
    void hurt(int a){
        health-=a;
    }
    bool isDead(){
        return health<1;
    }
    bool move(int direction){
        bool moved = false;
        switch(direction){
            case 1:
                if(x+speed<2500-w){
                    x+= speed;
                    moved = true;
                }
                changeSprite("resources/rightWitch.PNG");
                break;
            case 2:
                if(x-speed>0){
                    x-= speed;
                    moved = true;
                }
                changeSprite("resources/leftWitch.PNG");
                break;
            case 3:
                if(y+speed<1500-h){
                    y+= speed;
                    moved = true;
                }
                break;
            case 4:
                if(y-speed>0){
                    y-=speed;
                    moved = true;
                }
                break;
            default :
                break;
        return moved;
    }
    return moved;
    }
    void reset(){
        x = 200;
        y = 750;
        health = maxHealth;
        moveBox();
        changeSprite("resources/rightWitch.PNG");
    }
    
};

class ChillPlayer : public movingThing{
    public:
    int w, h;
    float maxHealth;
    Rectangle hitbox;
    ChillPlayer() : movingThing(200, 750, 10, "resources/rightWitchBig.png"){
        w = 90;
        h=128;
        hitbox = {x, y, (float)w, (float)h};
    }

    ~ChillPlayer() override = default;

    void moveBox(){
        hitbox = {x, y, (float)w, (float)h};
    }
    bool move(int direction){
        bool moved = false;
        switch(direction){
            case 1:
                if(x+speed<1170){
                    x+= speed;
                    moved = true;
                }
                changeSprite("resources/rightWitchBig.png");
                break;
            case 2:
                if(x-speed>0){
                    x-= speed;
                    moved = true;
                }
                changeSprite("resources/leftWitchBig.png");
                break;
            case 3:
                if(y+speed<1500-h){
                    y+= speed;
                    moved = true;
                }
                break;
            case 4:
                if(y-speed>0){
                    y-=speed;
                    moved = true;
                }
                break;
            default :
                break;
        return moved;
    }
    return moved;
    }
    void reset(){
        x = 200;
        y = 750;
        moveBox();
        changeSprite("resources/rightWitchBig.png");
    }
};

class Magic : public movingThing{
    public:
    int w, h, damage;
    Rectangle hitbox;
    Magic() : movingThing(2500, 1500, 20, "resources/magic.png"){
        w=48;
        h=48;
        damage = 25;
        hitbox = {x, y, (float)w, (float)h};
    }

    ~Magic() override = default;

    void moveBox(){
        hitbox = {x, y, (float)w, (float)h};
    }
    void setCoords(int a, int b){
        x = a;
        y = b;
    }
    void spawn(int direction, Player& player){
        switch(direction){
            case 1:
                setCoords(player.x, player.y+24);
                moveBox();
                break;
            case 2:
                setCoords(player.x-90, player.y+24);
                moveBox();
                break;
            case 3:
                setCoords(player.x+24, player.y+128);
                moveBox();
                break;
            case 4:
                setCoords(player.x+24, player.y-48);
                moveBox();
                break;
            default :
                break;
    }
}
    void increaseDamage(){
        damage+=5;
    }
};

class Sword : public movingThing{
    public:
    int w, h, damage, face;
    Rectangle hitbox;
    Sword() : movingThing(275, 780, 5, "resources/sword.PNG"){
        w=100;
        h=64;
        damage = 5;
        face = 1;
        hitbox = {x, y, (float)w, (float)h};
    }

    ~Sword() override = default;

    void moveBox(){
        hitbox = {x, y, (float)w, (float)h};
    }
    void setCoords(int a, int b){
        x = a;
        y = b;
    }
    void changeSwordSprite(Texture2D texture){
        sprite = texture;
    }
    void flip(int direction, Player& player, Texture2D right, Texture2D left){
        switch(direction){
            case 1:
                x = player.x+75;
                y = player.y+30;
                move(1);
                moveBox();
                face = 1;
                changeSwordSprite(right);
                break;
            case 2:
                x = player.x-(113);
                y = player.y+30;
                move(2);
                moveBox();
                face = 2;
                changeSwordSprite(left);
                break;
            default:
                break;
        }
    }
    void hitting(){
        if (face==1){
            changeSprite("resources/hitting.PNG");
        }
        else
            changeSprite("resources/leftHitting.PNG");
    }
    void stopHitting(){
        if (face==1){
            changeSprite("resources/sword.PNG");
        }
        else
            changeSprite("resources/leftSword.PNG");
    }
    void levelUp(){
        speed++;
    }
    void reset(){
    
        x = 275;
        y = 780;
        moveBox();
        changeSprite("resources/sword.PNG");
        face = 1;
    
    }
    void increaseDamage(){
        damage+=2;
    }
};

class SlimeBall : public movingThing{
    public:
    int w, h, damage;
    Rectangle hitbox;
    SlimeBall(int color) : movingThing(100, 100, 20, "resources/texture.png"){
        w=29;
        h=29;
        damage = 20;
        hitbox = {x, y, (float)w, (float)h};
        switch(color){
            case 1:
                sprite = LoadTexture("resources/greenBall.PNG");
                break;
            case 2:
                sprite = LoadTexture("resources/blueBall.PNG");
                break;
            case 3:
                sprite = LoadTexture("resources/pinkBall.PNG");
                break;
            default:
                break;
        }
    }

    ~SlimeBall() override = default;

    void moveBox(){
        hitbox = {x, y, (float)w, (float)h};
    }
    void setCoords(int a, int b){
        x = a;
        y = b;
    }
};

class Slime : public movingThing{
    public:
    int color;
    int w, h;
    int health, damage;
    Rectangle hitbox;
    std::vector<SlimeBall> balls;
    Slime() : movingThing(){
        color = GetRandomValue(1,3);
        switch(color){
            case 1:
                sprite = LoadTexture("resources/greenSlime.png");
                break;
            case 2:
                sprite = LoadTexture("resources/blueSlime.png");
                break;
            case 3:
                sprite = LoadTexture("resources/pinkSlime.png");
                break;
            default:
                break;
        }
        w = 64;
        h=52;
        health = 25;
        damage = 20;
        x = 2436;
        y = GetRandomValue(60, 1436);
        speed = 3;
        hitbox = {x, y, (float)w, (float)h};
        SlimeBall ball = SlimeBall(color);
        ball.setCoords(x-ball.w, y+32-(ball.h/2));
        balls.push_back(ball);
    }

    ~Slime() override {
        balls.clear();  // Will trigger ~SlimeBall() for each if managed correctly
    }

    void moveMyBalls(){
        for(int i = 0; i<(int)(balls.size()); i++){
            balls[i].move(2);
            balls[i].moveBox();
            if (balls[i].x<=0){
                balls.erase(balls.begin());
            }
        }
    }
    void addBall(int a){
        int random = GetRandomValue(1, 10);
        if (a%30==0 && random == 1){
            SlimeBall ball = SlimeBall(color);
            ball.setCoords(x-ball.w, y+32-(ball.h/2));
            balls.push_back(ball);
        }
    }
    void drawMyBalls(){
        for(int i = 0; i<(int)(balls.size()); i++){
            balls[i].draw();
        }
    }
    bool checkMyBalls(Player &player){
        bool touch = false;
        for(int i = 0; i<(int)(balls.size()); i++){
            touch = CheckCollisionRecs(player.hitbox, balls[i].hitbox);
            if (touch){
                balls.erase(balls.begin()+i);
                player.hurt(damage);
                break;
            }
        }
        return touch;
    }
    void hurt(int i){
        health-=i;
    }
};

class Enemies{
    private:
    std::vector<Slime> slimes;
    
    public:
    Enemies(){
        Slime first = Slime();
        slimes.push_back(first);
     
    }

    ~Enemies() {
        slimes.clear(); // Will trigger ~Slime() for each
    }
    void spawn(){
        Slime newSlime = Slime();
        slimes.push_back(newSlime);
    }
    int getAmount(){
        return slimes.size();
    }
    void moveAll(){
        for(int i = 0; i<(getAmount()); i++){
            slimes[i].move(2);
            slimes[i].hitbox = {slimes[i].x, slimes[i].y, (float)slimes[i].w, (float)slimes[i].h};
            if (slimes[i].x <= 0){
                slimes.erase(slimes.begin());
            }
        }
    }
    void moveBalls(){
        for(int i = 0; i<(getAmount()); i++){
            slimes[i].moveMyBalls();
        }
    }
    void drawAll(){
        for(int i = 0; i<(getAmount()); i++){
            slimes[i].draw();
        }
    }
    void addBalls(int a){
        for(int i = 0; i<(getAmount()); i++){
            slimes[i].addBall(a);
        }
    }
    void drawBalls(){
        for(int i = 0; i<(getAmount()); i++){
            slimes[i].drawMyBalls();
        }
    }
    bool ballDamage(Player &player){
        bool ouch = false;
        for(int i = 0; i<(getAmount()); i++){
            if((slimes[i].checkMyBalls(player))){
                ouch = true;
            }
        }
        return ouch;
    }

    bool magicDamage(Magic magic){
        bool touch = false;
        for(int i = 0; i<(getAmount()); i++){
            touch = CheckCollisionRecs(magic.hitbox, slimes[i].hitbox);
            if (touch){
                slimes.erase(slimes.begin()+i);
                return touch;
            }
        }
        return touch;
    }
    bool swordDamage(Sword &sword){
        bool touch = false;
        bool kill = false;
        for(int i = 0; i<(getAmount()); i++){
            touch = CheckCollisionRecs(sword.hitbox, slimes[i].hitbox);
            if (touch){
                slimes[i].hurt(sword.damage);
                if(slimes[i].health<=0){
                    slimes.erase(slimes.begin()+i);
                    kill = true;
                }
                return kill;
            }
        }
        return touch;
    }
    void reset(){
        slimes.clear();
    }
};

class FireBall : public movingThing{
    public:
    int w, h, damage;
    float direction;
    Rectangle hitbox;
    FireBall(int aim) : movingThing(1375, 725, 20, "resources/fireBall.PNG"){
        w=48;
        h=48;
        direction = aim;
        damage = 20;
        hitbox = {x, y, (float)w, (float)h};
    }

    ~FireBall() override = default;


    void moveBox(){
        hitbox = {x, y, (float)w, (float)h};
    }
    void setCoords(int a, int b){
        x = a;
        y = b;
    }
    void aim(){
        x+=cos((direction * PI)/180)*speed;
        y+=sin((direction * PI)/180)*speed;
    }
    void setDirection(Player &player){
        float mewo = player.x - x;
        float meow = player.y - y;
        direction= atan2(meow,mewo);
        direction = direction*180/PI;
    }
};

class Boss : public movingThing{
    public:
    int health, damage;
    Rectangle hitbox;
    std::vector<FireBall> balls;
    Boss() : movingThing(){
        sprite = LoadTexture("resources/boss.PNG");
        health = 500;
        damage = 20;
        x = 0;
        y = 0;
        speed = 0;
        hitbox = {1456, 399, (float)1043, (float)833};
        FireBall ball = FireBall(180);
        balls.push_back(ball);
    }

    ~Boss() override {
        balls.clear(); // Triggers ~FireBall()
    }

    void moveBalls(){
        for(int i = 0; i<(int)(balls.size()); i++){
            balls[i].aim();
            balls[i].moveBox();
            if (balls[i].x<=0 || (balls[i].y<=0||balls[i].y>=1500)){
                balls.erase(balls.begin()+i);
            }
        }
    }
    void addBall(int a, Player &player){
        int random = GetRandomValue(1, 3);
        if (a%30==0 && random == 1){
            FireBall ball = FireBall(GetRandomValue(1, 5));
            ball.setDirection(player);
            balls.push_back(ball);
        }
    }
    void drawBalls(){
        for(int i = 0; i<(int)(balls.size()); i++){
            balls[i].draw();
        }
    }
    bool checkMyBalls(Player &player){
        bool touch = false;
        for(int i = 0; i<(int)(balls.size()); i++){
            touch = CheckCollisionRecs(player.hitbox, balls[i].hitbox);
            if (touch){
                balls.erase(balls.begin()+i);
                player.hurt(damage);
                break;
            }
        }
        return touch;
    }
    void hurt(int i){
        health-=i;
    }
    void reset(){
        balls.clear();
        health = 500;
    }
    bool isDead(){
        return health<=0;
    }
    bool magicDamage(Magic &magic){
        bool touch = false;
            touch = CheckCollisionRecs(magic.hitbox, hitbox);
            if (touch){
            health-=magic.damage;
            }
        return touch;
    }
    bool swordDamage(Sword &sword){
        bool touch = false;
        bool kill = false;
            touch = CheckCollisionRecs(sword.hitbox, hitbox);
            if (touch){
                health-=sword.damage;
                if(health<=0){
                    kill = true;
                }
                return kill;
            }
        return kill;
    }
};
