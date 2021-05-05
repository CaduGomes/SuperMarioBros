#include <QGraphicsTextItem>
#include "game.h"

Game::Game(QWidget *parent)
{
    // criar scene
    scene = new QGraphicsScene();

    // fixar o tamanho em 800x600, que é infinito por definição
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush("#93bbec"));
    // visualizar o objeto scene (cenario)
    setScene(scene);

    //desabilitar as barras de rolagem
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // fixar o tamanho
    setFixedSize(800,600);

    for(int i=0;i < 12;i++){

       FloorBlock *block = new FloorBlock();
       block->setPos((i * 32),332);
       floorBlockList.push_back(block);

    }

    for(FloorBlock *b : floorBlockList){
        scene->addItem(b);
    }


    gameDirector = new GameDirector();
    scene->addItem(gameDirector->getPlayer());

    show();

}
