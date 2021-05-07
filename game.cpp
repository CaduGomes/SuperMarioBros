#include <QGraphicsTextItem>
#include "game.h"
#include <QDebug>

Game::Game(QWidget *parent)
{
    // criar scene
    scene = new QGraphicsScene();

    // fixar o tamanho em 800x600, que é infinito por definição
    scene->setSceneRect(0,0,800,400);
    scene->setBackgroundBrush(QBrush("#93bbec"));
    // visualizar o objeto scene (cenario)
    setScene(scene);
    //desabilitar as barras de rolagem
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qDebug() << scene->sceneRect().left();
    // fixar o tamanho
    setFixedSize(800,400);

    scene->setStickyFocus(true);

    //Construindo os blocos na tela
    assemble_screen();


    show();

}

void Game::moveScreen(double quant)
{

    if(quant > 150){
        scene->setSceneRect(scene->sceneRect().left()+2, 0, 800, 400);
    }else if (quant > 80){
        scene->setSceneRect(scene->sceneRect().left()+4, 0, 800, 400);
    }else if(quant > 30 && quant < 10){
        scene->setSceneRect(scene->sceneRect().left()+8, 0, 800, 400);
    }else {
        scene->setSceneRect(scene->sceneRect().left()+10, 0, 800, 400);
    }
}

void Game::check_mario_center_screen()
{

    if(scene->focusItem()->x() > (scene->sceneRect().center().x() - 200)){
        double distance = (scene->focusItem()->x() - scene->sceneRect().center().x()) * -1;
        moveScreen(distance);
    }
}

void Game::assemble_screen()
{
    QList <Floor_Block*> floor_blocks;

    for(int i=0;i < 25;i++){

        Floor_Block *block = new Floor_Block();
        block->setPos((i * 32),352);
        floor_blocks.push_back(block);

    }

    for(int i=0;i < 25;i++){

        Floor_Block *block = new Floor_Block();
        block->setPos((i * 32),384);
        floor_blocks.push_back(block);

    }

    for(Floor_Block *b : floor_blocks){
        scene->addItem(b);
    }

     QList <Mystery_Block*> mystery_blocks;

     Mystery_Block *mystery1 = new Mystery_Block(0);
     mystery1->setPos(500, 288);
     mystery_blocks.push_back(mystery1);

     Mystery_Block *mystery2 = new Mystery_Block(1);
     mystery2->setPos(400, 288);
     mystery_blocks.push_back(mystery2);



     for(Mystery_Block *m : mystery_blocks){
         scene->addItem(m);
     }

     QList <Brick_Block*> brick_blocks;

     Brick_Block *brick1 = new Brick_Block();
     brick1->setPos(532,288);
     brick_blocks.push_back(brick1);


     for(Brick_Block *b : brick_blocks){
         scene->addItem(b);
     }

}
