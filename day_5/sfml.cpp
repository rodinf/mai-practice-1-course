/*
  Rodin Fedor m3o-121b-20
*/

#include "SFML/Graphics.hpp"
#include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "SFML");

  sf::VertexArray triangle(sf::Triangles, 3);

  triangle[0].position = sf::Vector2f(100, 100);
  triangle[1].position = sf::Vector2f(200, 100);
  triangle[2].position = sf::Vector2f(200, 200);

    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Blue;
    triangle[2].color = sf::Color::Green;

  sf::Transform transform;

  sf::RenderStates states;
  

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          window.close();             
            break;

        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Right) {
            transform.rotate(1, sf::Vector2f(100, 100));
            states.transform = transform;
          }
          else if (event.key.code == sf::Keyboard::Left) {
            transform.rotate(-1, sf::Vector2f(100, 100));
            states.transform = transform;
          }
          break;
          
        default:
          break;
      }
    }

    window.clear();

    window.draw(triangle, states);

    window.display();
  }
}