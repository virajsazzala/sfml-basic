#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Animation.h"
#include "Player.h"
#include "Platform.h"

constexpr auto VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "sfml test", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
    
    sf::Texture playerTexture;
    playerTexture.loadFromFile("baldbaby.png");

    Player player(&playerTexture, sf::Vector2u(8, 8), 0.1f, 100.0f, 100.0f);

    std::vector<Platform> platforms;

    platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));

    // (w, h), (x,  y)
    platforms.push_back(Platform(nullptr, sf::Vector2f(80.0f, 10.0f), sf::Vector2f(300.0f, 350.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(80.0f, 10.0f), sf::Vector2f(450.0f, 300.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(80.0f, 10.0f), sf::Vector2f(550.0f, 250.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(80.0f, 10.0f), sf::Vector2f(650.0f, 200.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(80.0f, 10.0f), sf::Vector2f(750.0f, 150.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(80.0f, 10.0f), sf::Vector2f(850.0f, 100.0f)));

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        if (deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;

        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            }
        }
        
        player.update(deltaTime);


        sf::Vector2f direction;

        Collider pc = player.getCollider();
        for (Platform& platform : platforms)
            if (platform.getCollider().checkCollision(pc, direction, 1.0f))
                player.onCollision(direction);


        view.setCenter(player.getPosition());

        window.clear(sf::Color(135, 206, 235));
        window.setView(view);
        player.draw(window);

        for (Platform& platform : platforms)
            platform.draw(window);

        window.display();
    }
    return 0;
}