#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

///Struct
struct Node
{
    sf::Vector2f position;
    Node *lastNode;

    Node(){position = sf::Vector2f(0,0); lastNode = NULL;}
};

///Class
class GameObject
{
protected:

    float angle; ///In radians
    float speed;
    std::vector<Node*> nodeList;
    int numOfNodes;
    std::string color;
    //sf::Sprite sprite;
    sf::CircleShape sprite;


public:

    //GameObject(sf::Texture& texture);
    GameObject();

    virtual void handleEvents();
    virtual void update(float dt);
    virtual void draw(sf::RenderWindow& window);

};

#endif


