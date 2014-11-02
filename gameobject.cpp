#include "gameobject.h"
#include <math.h>
#include <iostream>

GameObject::GameObject()//sf::Texture& texture)
{
    nodeList.push_back(new Node());
    nodeList[0]->position = sf::Vector2f(50, 50);
    numOfNodes = 1;
    speed = 0.1;
    angle = -3.14/8;
    //sprite.setTexture(texture);
    sprite = sf::CircleShape(12, 30);
    sprite.setFillColor(sf::Color::Red);
}

void GameObject::handleEvents()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        angle += 0.034;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        angle -= 0.034;
}

void GameObject::update(float dt)
{
    //std::cout << nodeList[0]->position.x << ", " << nodeList[0]->position.y << std::endl;
    nodeList.push_back(new Node());
    numOfNodes++;
    nodeList[numOfNodes-1]->position.x = nodeList[numOfNodes-2]->position.x + speed*cos(angle)*dt;
    nodeList[numOfNodes-1]->position.y = nodeList[numOfNodes-2]->position.y - speed*sin(angle)*dt;
    nodeList[numOfNodes-1]->lastNode = nodeList[numOfNodes-2];
    //std::cout << nodeList.back()->position.x << ", " << nodeList.back()->position.y << std::endl;
}

void GameObject::draw(sf::RenderWindow& window)
{
    for(int i = 0; i < numOfNodes-1; i++)
    {
        sf::RectangleShape wall = sf::RectangleShape();
        wall.setFillColor(sf::Color::Red);
        //wall.setPosition(nodeList[i]->position);
        float currentAngle;
        float dx, dy;
        dy = nodeList[i+1]->position.y - nodeList[i]->position.y;
        dx = nodeList[i+1]->position.x - nodeList[i]->position.x;
        currentAngle = tan(dy/dx);
        wall.setSize(sf::Vector2f{sqrt((dx*dx) + (dy*dy))+12, 24});
        wall.setPosition(nodeList[i+1]->position.x+12, nodeList[i+1]->position.y+12);
        wall.rotate(currentAngle);
        window.draw(wall);
        if(i == numOfNodes-2)
        {
            sprite.setPosition(nodeList.back()->position.x, nodeList.back()->position.y);
            window.draw(sprite);
        }
        //wall.
    }
    //sprite.setPosition(nodeList.back()->position);
    //sprite.setPosition(nodeList[0]->position);
    //window.draw(sprite);
    /*sf::RectangleShape wall;
    wall.setFillColor(sf::Color::Red);
    wall.setSize(sf::Vector2f{50,30});
    wall.setPosition(50, 50);
    window.draw(wall);
    wall.setFillColor(sf::Color::Blue);
    wall.rotate(0.5);
    window.draw(wall);*/
}
