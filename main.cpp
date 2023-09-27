#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rect3D.hpp"
#include "Cube.hpp"
#include "Renderer.hpp"

int main() {

    int framerate = 60;

    sf::Font font;
    auto time = std::chrono::steady_clock::now();
    if(!font.loadFromFile("/Users/cameron/Desktop/CProjects/Drone/roboto/Roboto-Regular.ttf")){
        return 1;
    }

    // testing matMul
//    float m1[] = {1,2,3};
//    float m2[] = {1,2,3};
//    float* m3 = Rect3D::matMul(m1, 1, 3, m2, 3, 1);
//    for(int i = 0; i < 9; i++){
//        std::cout << m3[i] << std::endl;
//    }
//    delete [] m3;

    const uint32_t window_width  = 2560;
    const uint32_t window_height = 1600;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "3D Rendering");
    window.setFramerateLimit(framerate);
//    sf::RenderWindow window;
//    window.create(sf::VideoMode(800, 600), "Window Fullscreen", sf::Style::Fullscreen);

//    Rect rect{{window_width/2.0, window_height/2.0}, {200, 100}};
    Vector3f rectPos[4] = {{-10, 5, 0}, {10, 5, 0}, {10, -5, 0}, {-10, -5, 0}};
//    Rect3D rect3D{{0, 0, 0}, rectPos};
//    rect3D.setPointColor(0, sf::Color::Red);
//    rect3D.setPointColor(2, sf::Color::Blue);
//    rect3D.setPointColor(3, sf::Color::Green);
    int selected = 0;

    Cube cube{{0, 0, 10}, 10};
    cube.setFaceColor(0, sf::Color::Red);
    cube.setFaceColor(1, sf::Color::Green);
    cube.setFaceColor(2, sf::Color::Blue);
    cube.setFaceColor(3,sf::Color::Yellow);
    cube.setFaceColor(4, sf::Color::Magenta);
    cube.setFaceColor(5, sf::Color::Cyan);

    Cube cube2{{0, 0, -10}, 9};

    cube2.setFaceColor(0, sf::Color::White);
    cube2.setFaceColor(1, sf::Color::White);
    cube2.setFaceColor(2, sf::Color::White);
    cube2.setFaceColor(3,sf::Color::White);
    cube2.setFaceColor(4, sf::Color::White);
    cube2.setFaceColor(5, sf::Color::White);

    Vector2f cameraPos{0, 0};
    Vector3f cameraPos3D{0, 0, -10};

    Renderer renderer{window};
    renderer.setCameraPos(cameraPos3D);

    renderer.addObject(cube);
//    renderer.addObject(cube2);

    while(window.isOpen()){
//        window.clear();

        time = std::chrono::steady_clock::now();

        sf::Event event{};
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
//            rect3D.rotate({-.1, 0, 0});
            cube.rotate({-.1, 0, 0});
            cube2.rotate({-.1, 0, 0});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//            rect3D.rotate({.1, 0, 0});
            cube.rotate({.1, 0, 0});
            cube2.rotate({.1, 0, 0});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
//            rect3D.rotate({0, .1, 0});
            cube.rotate({0, .1, 0});
            cube2.rotate({0, .1, 0});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
//            rect3D.rotate({0, -.1, 0});
            cube.rotate({0, -.1, 0});
            cube2.rotate({0, -.1, 0});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)){
            cube.rotate({0, 0, .1});
            cube2.rotate({0, 0, .1});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Period)){
            cube.rotate({0, 0, -.1});
            cube2.rotate({0, 0, -.1});
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            renderer.mode = Renderer::PERSPECTIVE;
            Vector2f mousePos(sf::Mouse::getPosition(window));
//            rect3D.setPointPos(selected, {mousePos.x - window.getSize().x/2, mousePos.y - window.getSize().y/2, rect3D.pos.z});
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            renderer.mode = Renderer::ORTHOGRAPHIC;
            Vector2f mousePos(sf::Mouse::getPosition(window));
//            rect.setPos(mousePos);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
//            cameraPos3D.y += 1;
//            rect3D.move({0, 1, 0});
            cube.move({0, 1, 0});
            cube2.move({0, 1, 0});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
//            cameraPos3D.y -= 1;
//            rect3D.move({0, -1, 0});
            cube.move({0, -1, 0});
            cube2.move({0, -1, 0});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
//            cameraPos3D.x += 1;
//            rect3D.move({1, 0, 0});
            cube.move({1, 0, 0});
            cube2.move({1, 0, 0});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
//            cameraPos3D.x -= 1;
//            rect3D.move({-1, 0, 0});
            cube.move({-1, 0, 0});
            cube2.move({-1, 0, 0});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket)){
//            cameraPos3D.z += .1;
//            rect3D.move({0, 0, -1});
            cube.move({0, 0, -.1});
            cube2.move({0, 0, -.1});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket)){
//            cameraPos3D.z -= .1;
//            rect3D.move({0, 0, 1});
            cube.move({0, 0, .1});
            cube2.move({0, 0, .1});
        }

//        rect.draw(window, cameraPos);
//        rect3D.draw(window, cameraPos3D);
        renderer.render();
//        cube.draw(window, cameraPos3D);

        std::string s = std::to_string((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - time)).count());
        sf::Text time_text;
        time_text.setFont(font);
        std::string sTime = std::to_string(((std::chrono::steady_clock::now() - time)/1000000.0).count());
        time_text.setString("Delay: " + sTime + "ms");

        window.draw(time_text);


        window.display();
    }

    return 0;
}

