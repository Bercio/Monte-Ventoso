//
// Created by bercio on 05/12/16.
//
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
int main()
{
    std::vector<std::pair<int,int>> punti = ;
    int h = parete.get_end().Val2;
    int l =
    sf::RenderWindow window(sf::VideoMode(300, 600), "SFML works!");
    for(int i = 0; i < 600; i += 10) {
        sf::CircleShape shape(5.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(i/2, i);
        arr[i/10] = shape;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        for(int i = 0; i < 60; ++i){
            window.draw(arr[i]);
        }
        window.display();
    }

    return 0;
}

