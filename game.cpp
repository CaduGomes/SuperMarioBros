#include <QGraphicsTextItem>
#include "game.h"

Game::Game(QWidget *parent)
{
    // criar scene
    scene = new QGraphicsScene();

    // fixar o tamanho em 800x600, que é infinito por definição
    scene->setSceneRect(0,0,800,600);

    // visualizar o objeto scene (cenario)
    setScene(scene);

    //desabilitar as barras de rolagem
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // fixar o tamanho
    setFixedSize(800,600);

    // criar o jogador
    player = new Player();

    // definir o tamanho do jogador 100 x 100
    player->setRect(0,0,100,100);

    // definir a posição padrão do jogador para ser em baixo da tela
    // por definição a visualização é centralizada para pegar todos os objetos
    player->setPos(400,500);

    // colocar o foco no jogador
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // adicionar o jogador no cenario
    scene->addItem(player);

    show();

}
