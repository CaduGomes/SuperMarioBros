#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include <QDebug>
#include "game.h"
#include "pipe_block.h"
#include "background_image.h"
#include "flag_object.h"
#include "goomba_mob.h"

Game::Game(ISubject &gLoop, QWidget *parent): gameLoop(gLoop)
{
    gameLoop.attach(this);
    // criar scene
    scene = new QGraphicsScene();

    // fixar o tamanho em 800x600, que é infinito por definição
    scene->setSceneRect(0,0,512,464);

    scene->setBackgroundBrush(QBrush("#5C94FC"));
    // visualizar o objeto scene (cenario)
    setScene(scene);
    //desabilitar as barras de rolagem
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // fixar o tamanho
    setFixedSize(512,464);

    scene->setStickyFocus(true);

//    Goomba_Mob *goomba1 = new Goomba_Mob();
//    goomba1->setPos(150, 250);

//    scene->addItem(goomba1);

    //Construindo os blocos na tela
    assemble_blocks();
    assemble_scenery();

    player = new Player(gameLoop);
    player->setPos(0, 300);
    // colocar o foco no jogador
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    show();

}

void Game::update()
{
    check_mario_center_screen();
}

void Game::moveScreen(double quant)
{
    if(scene->sceneRect().right() > 6750){
        return;
    }

    if(quant > 150){
        scene->setSceneRect(scene->sceneRect().left()+2, 0, 512,464);
    }else if (quant > 80){
        scene->setSceneRect(scene->sceneRect().left()+4, 0, 512,464);
    }else if(quant > 30 && quant < 10){
        scene->setSceneRect(scene->sceneRect().left()+8, 0, 512,464);
    }else {
        scene->setSceneRect(scene->sceneRect().left()+10, 0, 512,464);
    }
}

void Game::check_mario_center_screen()
{
    if(scene->focusItem()->x() > (scene->sceneRect().center().x() - 100)){
        double distance = (scene->focusItem()->x() - scene->sceneRect().center().x()) * -1;
        moveScreen(distance);
    }

    if(scene->sceneRect().center().x() > 300 && !add_goomba1){
            Goomba_Mob *goomba = new Goomba_Mob(gameLoop);
            goomba->setPos(scene->sceneRect().right() + 100, floor-32);
            scene->addItem(goomba);
            add_goomba1 = true;
        }

        if(scene->sceneRect().center().x() > 1043 && !add_goomba2){
            Goomba_Mob *goomba = new Goomba_Mob(gameLoop);
            goomba->setPos(1690, floor-32);
            scene->addItem(goomba);
            Goomba_Mob *goomba2 = new Goomba_Mob(gameLoop);
            goomba2->setPos(1730, floor-32);
            scene->addItem(goomba2);

            add_goomba2 = true;
        }

        if(scene->sceneRect().center().x() > 2056 && !add_goomba3){
            Goomba_Mob *goomba = new Goomba_Mob(gameLoop);
            goomba->setPos(2660, lvl2-32);
            scene->addItem(goomba);
            Goomba_Mob *goomba2 = new Goomba_Mob(gameLoop);
            goomba2->setPos(2692, lvl2-32);
            scene->addItem(goomba2);

            add_goomba3 = true;
        }
}

void Game::assemble_blocks()
{

    QList <Floor_Block*> floor_blocks;

    QList <Mystery_Block*> mystery_blocks;

    QList <Brick_Block*> brick_blocks;

    QList <Pipe_Block*> pipe_blocks;

    //Criando o chão
    {
        int blocksWidth = 0;

        for(int i=0;i < 211;i++){

            if(i == 69){
                blocksWidth += 64;
            }

            if(i == 84){
                blocksWidth += 96;
            }

            if(i == 148){
                blocksWidth += 64;
            }

            floor_blocks.push_back(new Floor_Block(blocksWidth, floor, false));

            floor_blocks.push_back(new Floor_Block(blocksWidth, floor + 32, false));
            blocksWidth += 32;
        }
    }

    //Primeiro conjunto de blocos
    {
        Mystery_Block *mystery1 = new Mystery_Block(gameLoop, 0);
        mystery1->setPos(512, lvl1);
        mystery_blocks.push_back(mystery1);

        Mystery_Block *mystery2 = new Mystery_Block(gameLoop, 1);
        mystery2->setPos(672, lvl1);
        mystery_blocks.push_back(mystery2);

        Mystery_Block *mystery3 = new Mystery_Block(gameLoop, 1);
        mystery3->setPos(736, lvl1);
        mystery_blocks.push_back(mystery3);

        Mystery_Block *mystery4 = new Mystery_Block(gameLoop, 1);
        mystery4->setPos(704, lvl2);
        mystery_blocks.push_back(mystery4);

        Brick_Block *brick1 = new Brick_Block();
        brick1->setPos(640,lvl1);
        brick_blocks.push_back(brick1);

        Brick_Block *brick2 = new Brick_Block();
        brick2->setPos(704,lvl1);
        brick_blocks.push_back(brick2);

        Brick_Block *brick3 = new Brick_Block();
        brick3->setPos(768,lvl1);
        brick_blocks.push_back(brick3);
    }

    //Segundo conjunto de blocos
    {
        Mystery_Block *mystery1 = new Mystery_Block(gameLoop, 1);
        mystery1->setPos(2496, lvl1);
        mystery_blocks.push_back(mystery1);

        Brick_Block *brick1 = new Brick_Block();
        brick1->setPos(2464,lvl1);
        brick_blocks.push_back(brick1);

        Brick_Block *brick2 = new Brick_Block();
        brick2->setPos(2528,lvl1);
        brick_blocks.push_back(brick2);

        for(int i=0;i < 8;i++){
            Brick_Block *b = new Brick_Block();
            b->setPos(2560 +(i*32),lvl2);
            brick_blocks.push_back(b);
        }

        Mystery_Block *mystery2 = new Mystery_Block(gameLoop, 1);
        mystery2->setPos(3008, lvl2);
        mystery_blocks.push_back(mystery2);

        for(int i=0;i < 3;i++){
            Brick_Block *b = new Brick_Block();
            b->setPos(2912 +(i*32),lvl2);
            brick_blocks.push_back(b);
        }

        Brick_Block *brick3 = new Brick_Block();
        brick3->setPos(3008,lvl1);
        brick_blocks.push_back(brick3);
    }

    //Terceiro conjunto de blocos
    {
        for(int i=0;i < 2;i++){
            Brick_Block *b = new Brick_Block();
            b->setPos(3200 +(i*32),lvl1);
            brick_blocks.push_back(b);
        }

        Mystery_Block *mystery1 = new Mystery_Block(gameLoop, 1);
        mystery1->setPos(3392, lvl1);
        mystery_blocks.push_back(mystery1);

        Mystery_Block *mystery2 = new Mystery_Block(gameLoop, 1);
        mystery2->setPos(3488, lvl1);
        mystery_blocks.push_back(mystery2);

        Mystery_Block *mystery3 = new Mystery_Block(gameLoop, 1);
        mystery3->setPos(3584, lvl1);
        mystery_blocks.push_back(mystery3);

        Mystery_Block *mystery4 = new Mystery_Block(gameLoop, 1);
        mystery4->setPos(3488, lvl2);
        mystery_blocks.push_back(mystery4);

    }

    //Quarto conjunto de blocos
    {
        Brick_Block *brick1 = new Brick_Block();
        brick1->setPos(3808,lvl1);
        brick_blocks.push_back(brick1);

        for(int i=0;i < 3;i++){
            Brick_Block *b = new Brick_Block();
            b->setPos(3872 +(i*32),lvl2);
            brick_blocks.push_back(b);
        }

        Brick_Block *brick2 = new Brick_Block();
        brick2->setPos(4096,lvl2);
        brick_blocks.push_back(brick2);

        Mystery_Block *mystery1 = new Mystery_Block(gameLoop, 1);
        mystery1->setPos(4128, lvl2);
        mystery_blocks.push_back(mystery1);

        Mystery_Block *mystery2 = new Mystery_Block(gameLoop, 1);
        mystery2->setPos(4160, lvl2);
        mystery_blocks.push_back(mystery2);


        Brick_Block *brick3 = new Brick_Block();
        brick3->setPos(4192,lvl2);
        brick_blocks.push_back(brick3);

        for(int i=0;i < 2;i++){
            Brick_Block *b = new Brick_Block();
            b->setPos(4128 +(i*32),lvl1);
            brick_blocks.push_back(b);
        }
    }

    //Quinto conjunto de blocos
    {

        for(int i=0;i < 2;i++){
            Brick_Block *b = new Brick_Block();
            b->setPos(5376 +(i*32),lvl1);
            brick_blocks.push_back(b);
        }

        Mystery_Block *mystery1 = new Mystery_Block(gameLoop, 1);
        mystery1->setPos(5440, lvl1);
        mystery_blocks.push_back(mystery1);

        Brick_Block *brick1 = new Brick_Block();
        brick1->setPos(5472,lvl1);
        brick_blocks.push_back(brick1);
    }

    //Primeiro conjunto de Terrain Block
    {
        int x = 4288;
        for(int i=0;i < 4;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 32, true));
        }

        x += 32;
        for(int i=0;i < 3;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 64, true));
        }

        x += 32;
        for(int i=0;i < 2;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 96, true));
        }

        x += 32;
        floor_blocks.push_back(new Floor_Block(x, floor - 128, true));
    }

    //Segundo conjunto de Terrain Block
    {
        int x = 4480;

        floor_blocks.push_back(new Floor_Block(x, floor - 128, true));

        for(int i=0;i < 2;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 96, true));
        }

        for(int i=0;i < 3;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 64, true));
        }

        for(int i=0;i < 4;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 32, true));
        }

    }

    //Terceiro conjunto de Terrain Block
    {
        int x = 4736;
        for(int i=0;i < 5;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 32, true));

        }
        x += 32;
        for(int i=0;i < 4;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 64, true));

        }
        x += 32;
        for(int i=0;i < 3;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 96, true));

        }
        x += 32;
        for(int i=0;i < 2;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 128, true));
        }
    }

    //Quarto conjunto de Terrain Block
    {
        int x = 4960;

        floor_blocks.push_back(new Floor_Block(x, floor - 128, true));

        for(int i=0;i < 2;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 96, true));
        }

        for(int i=0;i < 3;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 64, true));
        }

        for(int i=0;i < 4;i++){
            floor_blocks.push_back(new Floor_Block(x + (i * 32), floor - 32, true));
        }

    }

    //Quinto conjunto de Terrain Block
    {
        int x = 6048;
        int floorDistance = 32;
        int size = 9;
        for(int i=0;i < 8;i++){
            for(int k=0;k < size; k++){
                floor_blocks.push_back(new Floor_Block(x - (k * 32), floor - floorDistance, true));
            }
            floorDistance += 32;
            size--;
            if(size < 2){
                break;
            }

        }

    }

    //Adicionando os canos
    {


        Pipe_Block *pipe1 = new Pipe_Block();
        pipe1->setPos(896,floor);
        pipe1->setSize(1);
        pipe_blocks.push_back(pipe1);

        Pipe_Block *pipe2 = new Pipe_Block();
        pipe2->setPos(1216,floor);
        pipe2->setSize(2);
        pipe_blocks.push_back(pipe2);

        Pipe_Block *pipe3 = new Pipe_Block();
        pipe3->setPos(1472,floor);
        pipe3->setSize(3);
        pipe_blocks.push_back(pipe3);

        Pipe_Block *pipe4 = new Pipe_Block();
        pipe4->setPos(1824,floor);
        pipe4->setSize(3);
        pipe_blocks.push_back(pipe4);

        Pipe_Block *pipe5 = new Pipe_Block();
        pipe5->setPos(5216,floor);
        pipe5->setSize(1);
        pipe_blocks.push_back(pipe5);

        Pipe_Block *pipe6 = new Pipe_Block();
        pipe6->setPos(5728,floor);
        pipe6->setSize(1);
        pipe_blocks.push_back(pipe6);

    }

    //Adicionando bandeira
    {
       Flag_Object *f = new Flag_Object(6344,floor-32);
       scene->addItem(f);

       floor_blocks.push_back(new Floor_Block(6336, floor - 32, true));
    }

    //Adicionando os blocos na tela
    {
        for(Pipe_Block *p : pipe_blocks){
            scene->addItem(p);
        }

        for(Mystery_Block *m : mystery_blocks){
            scene->addItem(m);
        }

        for(Brick_Block *b : brick_blocks){
            scene->addItem(b);
        }

        for(Floor_Block *b : floor_blocks){
            scene->addItem(b);
        }
    }

}

void Game::assemble_scenery()
{
    QList <Background_Image*> background_imgs;

    QPixmap tall_grass(":/sprites/world/tall-grass.png");
    QPixmap tall_grass2(":/sprites/world/tall-grass_2.png");
    QPixmap mid_grass(":/sprites/world/mid-grass.png");
    QPixmap small_grass(":/sprites/world/small-grass.png");
    QPixmap small_grass2(":/sprites/world/small-grass_2.png");
    QPixmap small_cloud(":/sprites/world/small-cloud.png");
    QPixmap big_cloud(":/sprites/world/big-cloud.png");
    QPixmap mid_cloud(":/sprites/world/mid-cloud.png");




    for(int i = 0; i < 5; i++){
        background_imgs.push_back(new Background_Image(-208 +(i * 1536),floor, mid_grass));
        background_imgs.push_back(new Background_Image(2+(i * 1536),floor, tall_grass));
        background_imgs.push_back(new Background_Image(368+(i * 1536),floor, tall_grass2));
        background_imgs.push_back(new Background_Image(512+(i * 1536),floor, small_grass));
        background_imgs.push_back(new Background_Image(752+(i * 1536),floor, small_grass2));
    }


    for(int i = 0; i < 5; i++){
        background_imgs.push_back(new Background_Image(272 +(1536 * i), 144, small_cloud));

        background_imgs.push_back(new Background_Image(640 +(1536 * i ),112, small_cloud));

        background_imgs.push_back(new Background_Image(880 +(1536 * i),144, big_cloud));

        background_imgs.push_back(new Background_Image(1168 +(1536 * i),112, mid_cloud));
    }

      background_imgs.push_back(new Background_Image(6464,floor, QPixmap(":/sprites/world/castle.png")));
    for(Background_Image *b : background_imgs){
        scene->addItem(b);
    }
}
