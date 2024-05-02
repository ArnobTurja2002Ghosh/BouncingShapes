#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Window Title");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Download Arial!\n";
    }

    sf::Text text;

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("CGreen");

    // set the character size
    text.setCharacterSize(18); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setOrigin(text.getLocalBounds().width / 2.f + text.getLocalBounds().left, text.getLocalBounds().height / 2.f + text.getLocalBounds().top);
    

    bool circleExists = true;
    float circleRadius = 50.0f;
    int circleSegments = 100;
    float circleColor[3] = { (float)0 / 255, (float)255 / 255, (float)0 / 255 };
    float circleSpeedX = -3.0f;
    float circleSpeedY = 2.0f;
    sf::CircleShape shape(circleRadius, circleSegments);
    shape.setFillColor(sf::Color
    (
        (int)(circleColor[0] * 255),
        (int)(circleColor[1] * 255),
        (int)(circleColor[2] * 255)
    )); // Color circle
    shape.setOrigin(circleRadius, circleRadius);
    shape.setPosition(100, 100); // Center circle
    text.setPosition(shape.getPosition());
    char displayString[255] = "CGreen";
    sf::Clock deltaClock;
    ImGui::GetStyle().ScaleAllSizes(1.0f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        //edw.is
        ImGui::Begin("Window title");
        ImGui::Text("Window text!");
        ImGui::Checkbox("Circle", &circleExists);
        ImGui::SliderFloat("Radius", &circleRadius, 50.0f, 100.0f);
        ImGui::SliderInt("Sides", &circleSegments, 3, 150);
        ImGui::ColorEdit3("Color Circle", circleColor);
        
        ImGui::InputText("Text", displayString, 255);
        if (ImGui::Button("Set Text")) {
            text.setString(displayString);
        }
        ImGui::End();

        shape.setRadius(circleRadius);
        shape.setOrigin(circleRadius, circleRadius);
        shape.setPosition(shape.getPosition().x + circleSpeedX, shape.getPosition().y + circleSpeedY);
        text.setPosition(shape.getPosition().x, shape.getPosition().y);
        if (shape.getPosition().x + circleRadius >= window.getSize().x || shape.getPosition().x - circleRadius <= 0) {
            circleSpeedX *= -1;
        }
        if (shape.getPosition().y + circleRadius >= window.getSize().y || shape.getPosition().y - circleRadius <= 0) {
            circleSpeedY *= -1;
        }
        shape.setPointCount(circleSegments);
        shape.setFillColor(sf::Color
        (
            (int)(circleColor[0] * 255),
            (int)(circleColor[1] * 255),
            (int)(circleColor[2] * 255)
        )); // Color circle

        window.clear(sf::Color(18, 33, 43)); // Color background
        if (circleExists) {
            window.draw(shape);
            window.draw(text);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}