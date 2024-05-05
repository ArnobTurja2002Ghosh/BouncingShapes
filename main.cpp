#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>

class AShape {       // The class
public:             // Access specifier
    sf::CircleShape circle;        // Attribute (int variable)
    sf::RectangleShape rectangle;  // Attribute (string variable)
    float speedX,speedY;
    sf::Text name;
    AShape() {
    }
};


int main()
{
    sf::RenderWindow window;
    sf::Font font;

    std::ifstream fin("config.txt");
    std::string temp;
    int characterSize, textR, textG, textB;
    std::vector<AShape> circles;

    while (fin >> temp) {
        if (temp.compare("Window") == 0) {
            int windowWidth, windowHeight;
            fin >> windowWidth >> windowHeight;
            window.create(sf::VideoMode(windowWidth, windowHeight), "Window Title"); 
        }
        else if (temp.compare("Font") == 0) {
            std::string font1;
            
            fin >> font1>> characterSize>>textR>>textG>>textB;
            if (!font.loadFromFile(font1))
            {
                std::cout << "Download Arial!\n";
            }
        }
        else if (temp.compare("Circle") == 0) {
            AShape circle1;

            fin >> temp;
            circle1.name.setFont(font); // font is a sf::Font
            circle1.name.setString(temp);
            circle1.name.setCharacterSize(characterSize); // in pixels, not points!
            circle1.name.setFillColor(sf::Color(textR, textG, textB));
            circle1.name.setStyle(sf::Text::Bold | sf::Text::Underlined);
            circle1.name.setOrigin(circle1.name.getLocalBounds().width / 2.f + circle1.name.getLocalBounds().left, circle1.name.getLocalBounds().height / 2.f + circle1.name.getLocalBounds().top);
            
            int temp1, temp2;
            fin >> temp1 >> temp2;
            circle1.circle.setPosition(temp1, temp2); // Center circle
            std::cout << temp1 << temp2;
            fin >> temp1 >> temp2;
            circle1.speedX = temp1;
            circle1.speedY = temp2;

            int temp3;
            fin >> temp1 >> temp2>>temp3;
            circle1.circle.setFillColor(sf::Color
            (
                (int)(temp1),
                (int)(temp2),
                (int)(temp3)
            ));


            fin >> temp3;
            circle1.circle.setRadius(temp3);
            circle1.circle.setOrigin(temp3, temp3);
            
            
            // select the font
            

            circles.push_back(circle1);
        }
        else if (temp.compare("Rectangle") == 0) {
            AShape circle1;

            fin >> temp;
            circle1.name.setFont(font); // font is a sf::Font
            circle1.name.setString(temp);
            circle1.name.setCharacterSize(characterSize); // in pixels, not points!
            circle1.name.setFillColor(sf::Color(textR, textG, textB));
            circle1.name.setStyle(sf::Text::Bold | sf::Text::Underlined);
            circle1.name.setOrigin(circle1.name.getLocalBounds().width / 2.f + circle1.name.getLocalBounds().left, circle1.name.getLocalBounds().height / 2.f + circle1.name.getLocalBounds().top);

            int temp1, temp2;
            fin >> temp1 >> temp2;
            circle1.rectangle.setPosition(temp1, temp2); // Center circle
            std::cout << temp1 << temp2;
            fin >> temp1 >> temp2;
            circle1.speedX = temp1;
            circle1.speedY = temp2;

            int temp3;
            fin >> temp1 >> temp2 >> temp3;
            circle1.rectangle.setFillColor(sf::Color
            (
                (int)(temp1),
                (int)(temp2),
                (int)(temp3)
            ));


            fin >> temp1>>temp2;
            circle1.rectangle.setSize(sf::Vector2f(temp1, temp2));
            circle1.rectangle.setOrigin(temp1/2, temp2/2);


            // select the font


            circles.push_back(circle1);
        }
    }
    
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    
    
       

    bool circleExists = true;
    float circleRadius = 50.0f;
    int circleSegments = 100;
    float circleColor[3] = { (float)0 / 255, (float)255 / 255, (float)0 / 255 };

    
    
   
    //text.setPosition(shape.getPosition());
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
            //text.setString(displayString);
        }
        ImGui::End();

        for (auto& c : circles) {
            //c.circle.setRadius(circleRadius);
            //c.circle.setOrigin(circleRadius, circleRadius);
            std::string name_string = c.name.getString();
            if (name_string[0] == 'C') {
            
                c.circle.setPosition(c.circle.getPosition().x + c.speedX, c.circle.getPosition().y + c.speedY);
                std::cout << c.circle.getPosition().x << c.circle.getPosition().y << "\n";
                c.name.setPosition(c.circle.getPosition());

                if (c.circle.getPosition().x + c.circle.getRadius() >= window.getSize().x || c.circle.getPosition().x - c.circle.getRadius() <= 0) {
                    c.speedX *= -1;
                }
                if (c.circle.getPosition().y + c.circle.getRadius() >= window.getSize().y || c.circle.getPosition().y - c.circle.getRadius() <= 0) {
                    c.speedY *= -1;
                }
            }
            else if (name_string[0] == 'R') {
                c.rectangle.setPosition(c.rectangle.getPosition().x + c.speedX, c.rectangle.getPosition().y + c.speedY);
                c.name.setPosition(c.rectangle.getPosition());
                if (c.rectangle.getPosition().x + c.rectangle.getSize().x/2 >= window.getSize().x || c.rectangle.getPosition().x - c.rectangle.getSize().x / 2 <= 0) {
                    c.speedX *= -1;
                }
                if (c.rectangle.getPosition().y + c.rectangle.getSize().y / 2 >= window.getSize().y || c.rectangle.getPosition().y - c.rectangle.getSize().y / 2 <= 0) {
                    c.speedY *= -1;
                }
            }
        }

        
        //text.setPosition(shape.getPosition().x, shape.getPosition().y);
        

        window.clear(sf::Color(18, 33, 43)); // Color background
        if (circleExists) {
            //window.draw(text);
        }
        for (auto a : circles) {
            window.draw(a.circle);
            window.draw(a.rectangle);
            window.draw(a.name);
        }  
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}