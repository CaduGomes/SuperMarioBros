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

    QList <FloorBlock*> floorBlockListTop;

    for(int i=0;i < 100;i++){

        FloorBlock *block = new FloorBlock();
        block->setPos((i * 32),350);
        floorBlockListTop.push_back(block);

    }

    for(FloorBlock *b : floorBlockListTop){
        scene->addItem(b);
    }

    QList <FloorBlock*> floorBlockListBottom;

    for(int i=0;i < 25;i++){

        FloorBlock *block = new FloorBlock();
        block->setPos((i * 32),382);
        floorBlockListBottom.push_back(block);

    }

    for(FloorBlock *b : floorBlockListBottom){
        scene->addItem(b);
    }

    scene->setStickyFocus(true);
    show();

}

void Game::moveScreen(double quant)
{
    qDebug() << quant;
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
