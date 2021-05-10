#include <QGraphicsTextItem>
#include "game.h"
#include <QDebug>
#include "pipe_block.h"
#include "background_image.h"

Game::Game(QWidget *parent)
{
    // criar scene
    scene = new QGraphicsScene();

    // fixar o tamanho em 800x600, que é infinito por definição
    scene->setSceneRect(0,0,512,464);
    QPixmap m("/home/MALEK/QT-Creator/PROJECTs/soso/bomb.jpeg");
    scene->setBackgroundBrush(QBrush("#5C94FC"));
    // visualizar o objeto scene (cenario)
    setScene(scene);
    //desabilitar as barras de rolagem
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // fixar o tamanho
    setFixedSize(512,464);

    scene->setStickyFocus(true);

    //Construindo os blocos na tela
    assemble_blocks();
    assemble_scenery();

    show();

}

void Game::moveScreen(double quant)
{
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

    if(scene->focusItem()->x() > (scene->sceneRect().center().x() - 200)){
        double distance = (scene->focusItem()->x() - scene->sceneRect().center().x()) * -1;
        moveScreen(distance);
    }
}

void Game::assemble_blocks()
{

    QList <Floor_Block*> floor_blocks;

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


        Floor_Block *block2 = new Floor_Block();
        block2->setPos(blocksWidth,floor);
        floor_blocks.push_back(block2);

        Floor_Block *block = new Floor_Block();
        block->setPos(blocksWidth,floor+32);
        floor_blocks.push_back(block);
        blocksWidth += 32;
    }

    for(Floor_Block *b : floor_blocks){
        scene->addItem(b);
    }

    QList <Mystery_Block*> mystery_blocks;

    Mystery_Block *mystery1 = new Mystery_Block(0);
    mystery1->setPos(512, lvl1);
    mystery_blocks.push_back(mystery1);

    Mystery_Block *mystery2 = new Mystery_Block(1);
    mystery2->setPos(672, lvl1);
    mystery_blocks.push_back(mystery2);

    Mystery_Block *mystery3 = new Mystery_Block(1);
    mystery3->setPos(736, lvl1);
    mystery_blocks.push_back(mystery3);

    Mystery_Block *mystery4 = new Mystery_Block(1);
    mystery4->setPos(704, lvl2);
    mystery_blocks.push_back(mystery4);



    for(Mystery_Block *m : mystery_blocks){
        scene->addItem(m);
    }

    QList <Brick_Block*> brick_blocks;

    Brick_Block *brick1 = new Brick_Block();
    brick1->setPos(640,lvl1);
    brick_blocks.push_back(brick1);

    Brick_Block *brick2 = new Brick_Block();
    brick2->setPos(704,lvl1);
    brick_blocks.push_back(brick2);

    Brick_Block *brick3 = new Brick_Block();
    brick3->setPos(768,lvl1);
    brick_blocks.push_back(brick3);



    for(Brick_Block *b : brick_blocks){
        scene->addItem(b);
    }

    QList <Pipe_Block*> pipe_blocks;

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


    for(Pipe_Block *p : pipe_blocks){
        scene->addItem(p);
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
        background_imgs.push_back( new Background_Image(512+(i * 1536),floor, small_grass));
        background_imgs.push_back(new Background_Image(752+(i * 1536),floor, small_grass2));
    }


    for(int i = 0; i < 5; i++){
        background_imgs.push_back(new Background_Image(272 +(1536 * i), 144, small_cloud));

        background_imgs.push_back(new Background_Image(640 +(1536 * i ),112, small_cloud));

        background_imgs.push_back(new Background_Image(880 +(1536 * i),144, big_cloud));

        background_imgs.push_back(new Background_Image(1168 +(1536 * i),112, mid_cloud));
    }


    for(Background_Image *b : background_imgs){
        scene->addItem(b);
    }
}
