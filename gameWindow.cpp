#include "movingThing.h"
#include <cmath>

//SLIME FRENZY by Haley Solin
//
//MUSIC CREDS:
//
//Exploration | Chiptune RPG Adventure Theme by nickpanek620 on Pixabay
//Tower Defense | 8-Bit Chiptune Game Music by nickpanek620 on Pixabay
// Chiptune grooving by unnamed person on Pixabay
//license: https://pixabay.com/service/license-summary/


int main(){
    int screenWidth = 2500;
    int screenHeight = 1500;
    
    InitWindow(screenWidth, screenHeight, "Slime Frenzy");
    Player player = Player();
    ChillPlayer chiller = ChillPlayer();
    Magic magic = Magic();
    Sword sword = Sword();
    Boss boss = Boss();
    Enemies enemies = Enemies();
    Texture2D grass = LoadTexture("resources/grasss.PNG");
    Texture2D bar = LoadTexture("resources/fullBar.PNG");
    Texture2D titleScreen = LoadTexture("resources/title.PNG");
    Texture2D guildBG = LoadTexture("resources/guild.PNG");
    Texture2D textBox = LoadTexture("resources/carolineText.PNG");
    Texture2D rightSword = LoadTexture("resources/sword.PNG");
    Texture2D leftSword = LoadTexture("resources/leftSword.PNG");
    float width = 1600;
    Rectangle healthBar = {15009, 10, width, 50};
    double lastSpawn = GetTime();
    double sinceSpawn = 0.0;
    double lastShoot = GetTime();
    double sinceShoot = 0.0;
    double spawnTime = 2;
    int frameCount = 0;
    int magicDirection = 0;
    int totalSlimesKilled = 0;
    int slimesKilled = 0;
    int slimeBounty = 0;
    int coins = 0;
    int storyLine = 0;
    bool paused = false;
    bool fighting = false;
    bool guild = false;
    bool story = false;
    bool isTalking = false;
    bool intro = true;
    bool tutorial = false;
    bool selectBounty = false;
    bool checkStats = false;
    bool shopping = false;
    bool bought = false;
    bool playDie = true;
    bool bossing = false;

    InitAudioDevice();

    Music chillMusic = LoadMusicStream("resources/sounds/chillMusic.mp3");
    Music fightingMusic = LoadMusicStream("resources/sounds/chillFighting.mp3");
    Music bossMusic = LoadMusicStream("resources/sounds/fighting.mp3");

    Sound attackSound = LoadSound("resources/sounds/sword.mp3");
    Sound killSound = LoadSound("resources/sounds/kill.mp3");
    Sound magicSound = LoadSound("resources/sounds/magic.mp3");
    Sound hurtSound = LoadSound("resources/sounds/hit.mp3");
    Sound levelUpSound = LoadSound("resources/sounds/levelUp.mp3");
    Sound deathSound = LoadSound("resources/sounds/death.mp3");
    Sound buttonSound = LoadSound("resources/sounds/button.mp3");
    Sound winSound = LoadSound("resources/sounds/winner.mp3");
    Sound gameStart = LoadSound("resources/sounds/gameStart.mp3");

    PlayMusicStream(chillMusic);
    PlayMusicStream(fightingMusic);
    PlayMusicStream(bossMusic);

    SetTargetFPS(60);
   
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        if(!fighting&&!bossing){
            PauseMusicStream(fightingMusic);
            PauseMusicStream(bossMusic);
            UpdateMusicStream(chillMusic);
            ResumeMusicStream(chillMusic);
        }
        else if(bossing){
            PauseMusicStream(chillMusic);
            PauseMusicStream(fightingMusic);
            UpdateMusicStream(bossMusic);
            ResumeMusicStream(bossMusic);
        }
        else{
            PauseMusicStream(chillMusic);
            PauseMusicStream(bossMusic);
            UpdateMusicStream(fightingMusic);
            ResumeMusicStream(fightingMusic);
        }
        if(!fighting&&!guild&&!story&&!bossing){
            DrawTexture(titleScreen, 0, 0, WHITE);
            if(IsKeyPressed(KEY_S)){
                story = true;
                PlaySound(gameStart);
            }
        }
        if(story){
            ClearBackground(BLACK);
            DrawText("-- Press SPACE to continue --", 850, 1300, 50, LIGHTGRAY);
            if(storyLine>=0){
                DrawText("Once upon a time, there lived a girl with an unremarkable life.", 350, 300, 50, WHITE);
            }
            if(storyLine>=1){
                DrawText("That is, until she woke up one day in a completely unfamiliar place: \na fantasy world!", 350, 520, 50, WHITE);
            }
            if(storyLine>=2){
                DrawText("She was approached by a girl named Caroline who offered her a job as \na slime hunter at the adventurer's guild.", 350, 770, 50, WHITE);
            }
            if(storyLine>=3){
                DrawText("Being both broke and homeless, she gladly accepted the offer.\nNow, it is your job to help her complete bounties and get rich!", 350, 1020, 50, WHITE);
            }
            if(storyLine>=4){
                story = false;
                guild = true;
            }
            if(IsKeyPressed(KEY_SPACE)){
                storyLine++;
                PlaySound(buttonSound);
            }
        }
        
        if(guild){
            ClearBackground(BROWN);
            DrawTexture(guildBG, 0, 0, WHITE);
            chiller.draw();
            if(chiller.x>1000&&!isTalking){
                DrawText("Press 'X' to talk", 1500, 550, 50, BLACK);
            }
            if (IsKeyPressed(KEY_X)&&chiller.x>1000){
                PlaySound(buttonSound);
                if (isTalking){
                    isTalking = false;
                    intro = true;
                    selectBounty = false;
                    tutorial = false;
                    checkStats = false;
                    shopping = false;
                    bought = false;
                }
                else
                    isTalking = true;
            }
            if(!isTalking){
                if(IsKeyDown(KEY_D)&&((chiller.x)<=1170)){
                    chiller.move(1);
                    chiller.moveBox();
                }
                 else if (IsKeyDown(KEY_A)){
                    chiller.move(2);
                    chiller.moveBox();
                }
                else if (IsKeyDown(KEY_S)&&chiller.y<=924){
                    chiller.move(3);
                    chiller.moveBox();
                }
                else if (IsKeyDown(KEY_W)&&chiller.y>165){
                    chiller.move(4);
                    chiller.moveBox();
                }
            }
            if (isTalking){
            DrawTexture(textBox, 0, 0, WHITE);
            if(intro){
                DrawText("Welcome to the Adventurer's Guild! How can I help you?\n\n1-Tutorial\n\n2-Start Bounty\n\n3-Check Stats\n\n4-Open Shop\n\n5-Exit Game", 752, 778, 50, DARKBROWN);
                DrawText("'X' to go close", 1285, 1330, 50, BROWN);
                if(IsKeyPressed(KEY_ONE)){
                    PlaySound(buttonSound);
                    tutorial = true;
                    intro = false;
                }
                else if(IsKeyPressed(KEY_TWO)){
                    PlaySound(buttonSound);
                    selectBounty = true;
                    intro = false;
                }
                else if(IsKeyPressed(KEY_THREE)){
                    PlaySound(buttonSound);
                    checkStats = true;
                    intro = false;
                }
                else if(IsKeyPressed(KEY_FOUR)){
                    PlaySound(buttonSound);
                    shopping = true;
                    intro = false;
                }
                else if(IsKeyPressed(KEY_FIVE)){
                    break;
                }
            }
            if(tutorial){
                if(IsKeyPressed(KEY_B)){
                    PlaySound(buttonSound);
                    intro = true;
                    tutorial = false;
                }
                DrawText("Before entering battle mode, you will select how many \nslimes to kill to end battle mode.\n\nIn battle mode, press WASD to move, space to hit with\nyour sword, and arrow keys in the direction you want to \nshoot magic. Use your magic wisely, because there is a\n4 second cooldown!\n\nSlimes will spawn and shoot balls at you which can kill you!\nAlso, you can press P at any time to pause.", 752, 778, 50, DARKBROWN);
                DrawText("'B' to go back", 1275, 1330, 50, BROWN);
            }
            if(selectBounty){
                if(IsKeyPressed(KEY_B)){
                    PlaySound(buttonSound);
                    intro = true;
                    selectBounty = false;
                }
                DrawText("Select the bounty level with 3, 4, 5, or 6.\n\n3- 10 slime bounty  - Reward: 100 coins\n\n4- 20 slime bounty - Reward: 250 coins\n\n5- 30 slime bounty - Reward: 400 coins\n\n6- Boss fight       - Reward: 1000 coins", 752, 788, 50, DARKBROWN);
                DrawText("'B' to go back", 1275, 1330, 50, BROWN);
                if(IsKeyPressed(KEY_THREE)){
                PlaySound(buttonSound);
                fighting = true;
                guild = false;
                slimeBounty = 10;
                isTalking = false;
                selectBounty = false;
                intro = true;
                chiller.reset();
                StopMusicStream(chillMusic);
                PlayMusicStream(chillMusic);
            }
            else if(IsKeyPressed(KEY_FOUR)){
                PlaySound(buttonSound);
                fighting = true;
                guild = false;
                slimeBounty = 20;
                isTalking = false;
                selectBounty = false;
                intro = true;
                chiller.reset();
                StopMusicStream(chillMusic);
                PlayMusicStream(chillMusic);
            }
            else if(IsKeyPressed(KEY_FIVE)){
                PlaySound(buttonSound);
                fighting = true;
                guild = false;
                slimeBounty = 30;
                isTalking = false;
                selectBounty = false;
                intro = true;
                chiller.reset();
                StopMusicStream(chillMusic);
                PlayMusicStream(chillMusic);
            }
            else if(IsKeyPressed(KEY_SIX)){
                PlaySound(buttonSound);
                bossing = true;
                guild = false;
                slimeBounty = 30;
                isTalking = false;
                selectBounty = false;
                intro = true;
                chiller.reset();
                StopMusicStream(chillMusic);
                PlayMusicStream(chillMusic);
            }
            }
            if(checkStats){
                if(IsKeyPressed(KEY_B)){
                    PlaySound(buttonSound);
                    intro = true;
                    checkStats = false;
                }
                DrawText(TextFormat("You have killed a grand total of %i slimes. \n\nYou are on level %i.\n\nTo level up, kill %i more slimes.\n\nYou currently have %i coins.",totalSlimesKilled, player.level, (int)(10*(1.0/1.8*std::pow(player.level,2)))-totalSlimesKilled, coins), 752, 788, 50, DARKBROWN);
                DrawText("'B' to go back", 1275, 1330, 50, BROWN);
            }
            if(shopping){
                if(IsKeyPressed(KEY_B)){
                    PlaySound(buttonSound);
                    intro = true;
                    shopping = false;
                    bought = false;
                }
                if(coins>=300){
                DrawText(TextFormat("OK! You currently have %i coins.\n\nFor 300 coins, you can increase your damage \nby 2.\n\nFor reference, slimes have 25 health.\n\nWould you like to upgrade? Press 'Y' or 'N'", coins), 752, 788, 50, DARKBROWN);
                DrawText("'B' to go back", 1275, 1330, 50, BROWN);
                if (IsKeyPressed(KEY_Y)){
                        PlaySound(buttonSound);
                        bought = true;
                        shopping = false;
                        coins-=300;
                        sword.increaseDamage();
                        magic.increaseDamage();
                    }
                    if (IsKeyPressed(KEY_N)){
                        PlaySound(buttonSound);
                        shopping = false;
                        intro = true;
                    }
                }

                else{
                    DrawText(TextFormat("OK! You currently have %i coins.\n\nYou need %i more coins for an upgrade.", coins, 300-coins), 752, 788, 50, DARKBROWN);
                    DrawText("'B' to go back", 1275, 1330, 50, BROWN);
                }
                }
            if(bought){
                if(IsKeyPressed(KEY_B)){
                    PlaySound(buttonSound);
                    intro = true;
                    bought = false;
                }
                DrawText(TextFormat("OK! You now have %i coins.\n\nYour sword now does %i damage,\nand your magic now does %i damage.", coins, sword.damage, magic.damage), 752, 788, 50, DARKBROWN);
                DrawText("'B' to go back", 1275, 1330, 50, BROWN);
            }
        }
        }
      if(fighting){
        if(!paused&&!player.isDead()){
            sinceSpawn = GetTime() - lastSpawn;
            sinceShoot = GetTime() - lastShoot;
            frameCount++;
        }
        if(std::floor(sinceShoot)==0){
            
            bar = LoadTexture("resources/emptyBar.PNG");
        }
        else if(std::floor(sinceShoot)==1){
            
            bar = LoadTexture("resources/emptyishBar.PNG");
        }
        else if(std::floor(sinceShoot)==2){
            
            bar = LoadTexture("resources/halfBar.PNG");
        }
        else if(std::floor(sinceShoot)==3){
            
            bar = LoadTexture("resources/fullishBar.PNG");
        }
        else if(std::floor(sinceShoot)==4){
            
            bar = LoadTexture("resources/fullBar.PNG");
        }
        
        DrawTexture(grass, 0, 0, WHITE);
        if (!player.isDead()){
            player.draw(); //draw player
            sword.draw();
        }
        if(IsKeyPressed(KEY_P)){
            if(paused)
                paused = false;
            else
                paused = true;
        }
        if(!paused){
        if(IsKeyDown(KEY_D)){
            //sword.changeSprite("resources/sword.PNG");
            if(player.move(1)){
                sword.flip(1, player, rightSword, leftSword);
                
                //sword.move(1);
            }
            player.moveBox();
        }
        else if (IsKeyDown(KEY_A)){
            //sword.changeSprite("resources/leftSword.PNG");
            if(player.move(2)){
                sword.flip(2, player, rightSword, leftSword);
                
                //sword.move(2);
            }
            player.moveBox();
        }
        else if (IsKeyDown(KEY_S)){
            
            if(player.move(3)){ 
                sword.move(3);
                sword.moveBox();
            }
            player.moveBox();
        }
        else if (IsKeyDown(KEY_W)){
            if(player.move(4)){
            sword.move(4);
            sword.moveBox();
            }
            player.moveBox();
        }//move player

        if(IsKeyDown(KEY_SPACE)){
            sword.hitting();
            PlaySound(attackSound);
        }
        else{
            sword.stopHitting();
        }
        if(IsKeyPressed(KEY_SPACE)){
            if(enemies.swordDamage(sword)){
                slimesKilled++;
                totalSlimesKilled++;
                PlaySound(killSound);
            }
        }
        }

       if (sinceShoot>4 && !player.isDead() && !paused){
            if(IsKeyPressed(KEY_RIGHT)){
                magic.spawn(1, player);
                magicDirection = 1;
                lastShoot = GetTime();
                PlaySound(magicSound);
            }
            else if (IsKeyPressed(KEY_LEFT)){
                magic.spawn(2, player);
                magicDirection = 2;
                lastShoot = GetTime();
                PlaySound(magicSound);
            }
            else if (IsKeyPressed(KEY_DOWN)){
                magic.spawn(3, player);
                magicDirection = 3;
                lastShoot = GetTime();
                PlaySound(magicSound);
            }
            else if (IsKeyPressed(KEY_UP)){
                magic.spawn(4, player);
                magicDirection = 4;
                lastShoot = GetTime();
                PlaySound(magicSound);
            }
        }   //spawn magic

        magic.draw();
        magic.moveBox();
        

        if (enemies.magicDamage(magic)){
            slimesKilled++;
            totalSlimesKilled++;
            PlaySound(killSound);
        }//up slime kill count


        if(!player.isDead()&&!paused){
            magic.move(magicDirection);
        }

        if(sinceSpawn>=spawnTime && !player.isDead() &&!paused){
            enemies.spawn();
            lastSpawn = GetTime();
        }//spawn slimes
        enemies.drawAll();
        enemies.drawBalls();
        if (!player.isDead() && !paused){
            enemies.moveAll();
            enemies.addBalls(frameCount);//spawns a ball sometimes
            enemies.moveBalls();
            if(enemies.ballDamage(player)){
                PlaySound(hurtSound);
            }
        }

        if(totalSlimesKilled==(int)(10*(1.0/1.8*std::pow(player.level,2))) && slimesKilled!=0){
            player.levelUp();
            sword.levelUp();
            PlaySound(levelUpSound);
        }
        DrawText(TextFormat("HEALTH: %i\tSlimes Killed: %i\tLevel: %i", player.health, slimesKilled, player.level), 10, 10, 50, WHITE);
        DrawTexture(bar, 10, 1350, WHITE);
        if(paused){
            DrawText("PAUSED", 1000, 700, 100, WHITE);
        }
        if(player.isDead()){
            DrawText("you're dead lol", 850, 700, 100, WHITE);
            DrawText("'R' to return to the guild", 750, 800, 75, WHITE);
            if(playDie){
                StopMusicStream(fightingMusic);
                PlaySound(deathSound);
                playDie=false;
            }
            if(IsKeyPressed(KEY_R)){
                guild = true;
                fighting = false;
                playDie = true;
                slimesKilled = 0;
                player.reset();
                enemies.reset();
                magic.setCoords(2500, 1500);
                sword.reset();
                PlayMusicStream(fightingMusic);
                bar = LoadTexture("resources/fullBar.PNG");
            }
        }
        if(slimeBounty==slimesKilled){
            paused = true;
            DrawRectangleRounded({500, 500, 1500, 500}, 0.3f, 15, PURPLE);
            DrawText("Bounty Complete!", 825, 650, 100, WHITE);
            DrawText("'R' to return to the guild", 750, 750, 75, WHITE);
            if(playDie){
                StopMusicStream(fightingMusic);
                PlaySound(winSound);
                playDie=false;
            }
            if(IsKeyPressed(KEY_R)){
            playDie = true;
            guild = true;
            fighting = false;
            paused = false;
            slimesKilled = 0;
            player.reset();
            enemies.reset();
            magic.setCoords(2500, 1500);
            sword.reset();
            coins+=(slimeBounty*10+((slimeBounty/10-1)*50));
            StopMusicStream(fightingMusic);
            PlayMusicStream(fightingMusic);
            bar = LoadTexture("resources/fullBar.PNG");
            }
        }
    }
        if(bossing){
        width = boss.health*2.7;
        healthBar = {1000, 10, width, 50};
        if(!paused&&!player.isDead()){
            sinceSpawn = GetTime() - lastSpawn;
            sinceShoot = GetTime() - lastShoot;
            frameCount++;
        }
        if(std::floor(sinceShoot)==0){
            
            bar = LoadTexture("resources/emptyBar.PNG");
        }
        else if(std::floor(sinceShoot)==1){
            
            bar = LoadTexture("resources/emptyishBar.PNG");
        }
        else if(std::floor(sinceShoot)==2){
            
            bar = LoadTexture("resources/halfBar.PNG");
        }
        else if(std::floor(sinceShoot)==3){
            
            bar = LoadTexture("resources/fullishBar.PNG");
        }
        else if(std::floor(sinceShoot)==4){
            
            bar = LoadTexture("resources/fullBar.PNG");
        }
        
        DrawTexture(grass, 0, 0, WHITE);
        
        if(IsKeyPressed(KEY_P)){
            if(paused)
                paused = false;
            else
                paused = true;
        }
        if(!paused){
        if(IsKeyDown(KEY_D)&&!CheckCollisionRecs(player.hitbox, boss.hitbox)){
            if(player.move(1)){
                sword.flip(1, player, rightSword, leftSword);
            }
            player.moveBox();
        }
        else if (IsKeyDown(KEY_A)){
            if(player.move(2)){
                sword.flip(2, player, rightSword, leftSword);
            }
            player.moveBox();
        }
        else if (IsKeyDown(KEY_S)&&!(player.x>1456&&(270<player.y&&player.y<1210))){
            
            if(player.move(3)){ 
                sword.move(3);
                sword.moveBox();
            }
            player.moveBox();
        }
        else if (IsKeyDown(KEY_W)&&!(player.x>1456&&(290<player.y&&player.y<1232))){
            if(player.move(4)){
            sword.move(4);
            sword.moveBox();
            }
            player.moveBox();
        }//move player

        if(IsKeyDown(KEY_SPACE)&&!player.isDead()&&!paused){
            sword.hitting();
            PlaySound(attackSound);
        }
        else{
            sword.stopHitting();
        }
        if(IsKeyPressed(KEY_SPACE)&&!player.isDead()&&!paused){
            if(enemies.swordDamage(sword)){
                slimesKilled+=1;
                totalSlimesKilled+=1;
                PlaySound(killSound);
            }
            if(boss.swordDamage(sword)){
                PlaySound(killSound);
            }
        }
        }

       if (sinceShoot>4 && !player.isDead() && !paused){
            if(IsKeyPressed(KEY_RIGHT)){
                magic.spawn(1, player);
                magicDirection = 1;
                lastShoot = GetTime();
                PlaySound(magicSound);
            }
            else if (IsKeyPressed(KEY_LEFT)){
                magic.spawn(2, player);
                magicDirection = 2;
                lastShoot = GetTime();
                PlaySound(magicSound);
            }
            else if (IsKeyPressed(KEY_DOWN)){
                magic.spawn(3, player);
                magicDirection = 3;
                lastShoot = GetTime();
                PlaySound(magicSound);
            }
            else if (IsKeyPressed(KEY_UP)){
                magic.spawn(4, player);
                magicDirection = 4;
                lastShoot = GetTime();
                PlaySound(magicSound);
            }
        }   //spawn magic
        
        enemies.drawAll();
        enemies.drawBalls();
        if(!boss.isDead())
            boss.draw();
        boss.drawBalls();

        if (!player.isDead()){
            player.draw(); //draw player
            sword.draw();
        }
        magic.draw();
        magic.moveBox();
        

        if (enemies.magicDamage(magic)){
            slimesKilled++;
            totalSlimesKilled++;
            PlaySound(killSound);
        }//up slime kill count

        if (boss.magicDamage(magic)){
            magic.setCoords(2500,1500);
        }

        if(!player.isDead()&&!paused){
            magic.move(magicDirection);
        }

        if(sinceSpawn>=12 && !player.isDead() &&!paused){
            enemies.spawn();
            lastSpawn = GetTime();
        }//spawn slimes
        

        if (!player.isDead() && !paused){
            enemies.moveAll();
            enemies.addBalls(frameCount);//spawns a ball sometimes
            enemies.moveBalls();
            if(enemies.ballDamage(player)){
                PlaySound(hurtSound);
            }
            if(boss.checkMyBalls(player)){
                PlaySound(hurtSound);
            }
            boss.addBall(frameCount, player);
            boss.moveBalls();
        }

        if(totalSlimesKilled>=(int)(10*(1.0/1.8*std::pow(player.level,2))) && slimesKilled!=0){
            player.levelUp();
            sword.levelUp();
            PlaySound(levelUpSound);
        }
        DrawText(TextFormat("HEALTH: %i\tSlimes Killed: %i\tLevel: %i", player.health, slimesKilled, player.level), 10, 10, 50, WHITE);
        DrawTexture(bar, 10, 1350, WHITE);
        DrawRectangleRounded(healthBar, 0.2f, 10, RED);
        if(paused){
            DrawText("PAUSED", 1000, 700, 100, WHITE);
        }
        if(player.isDead()){
            DrawText("you're dead lol", 850, 700, 100, WHITE);
            DrawText("'R' to return to the guild", 750, 800, 75, WHITE);
            if(playDie){
                StopMusicStream(bossMusic);
                PlaySound(deathSound);
                playDie=false;
            }
            if(IsKeyPressed(KEY_R)){
                guild = true;
                bossing = false;
                playDie = true;
                slimesKilled = 0;
                player.reset();
                enemies.reset();
                boss.reset();
                magic.setCoords(2500, 1500);
                sword.reset();
                chiller.reset();
                PlayMusicStream(bossMusic);
                bar = LoadTexture("resources/fullBar.PNG");
            }
        }
        if(boss.isDead()){
            paused = true;
            DrawRectangleRounded({500, 500, 1500, 500}, 0.3f, 15, PURPLE);
            DrawText("Bounty Complete!", 825, 650, 100, WHITE);
            DrawText("'R' to return to the guild", 750, 750, 75, WHITE);
            if(playDie){
                StopMusicStream(bossMusic);
                PlaySound(winSound);
                playDie=false;
            }
            if(IsKeyPressed(KEY_R)){
            slimesKilled+=10;
            totalSlimesKilled+=10;
            if(totalSlimesKilled>=(int)(10*(1.0/1.8*std::pow(player.level,2))) && slimesKilled!=0){
            player.levelUp();
            sword.levelUp();
            }
            playDie = true;
            paused = false;
            guild = true;
            bossing = false;
            slimesKilled = 0;
            player.reset();
            enemies.reset();
            boss.reset();
            magic.setCoords(2500, 1500);
            sword.reset();
            coins+=1000;
            StopMusicStream(bossMusic);
            PlayMusicStream(bossMusic);
            }
       
    }
    }
        EndDrawing();
    }
    UnloadMusicStream(chillMusic);
    UnloadMusicStream(fightingMusic);
    UnloadMusicStream(bossMusic);
    CloseAudioDevice();
    CloseWindow();
    return 0;
    
}