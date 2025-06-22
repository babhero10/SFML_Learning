#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>

#include <filesystem> // For std::filesystem


int main(void) {

  unsigned int width = 640;
  unsigned int height = 360;

  std::unique_ptr<sf::RenderWindow> window =
        std::make_unique<sf::RenderWindow>(sf::VideoMode({width, height}), "Turtorl");

  window->setFramerateLimit(144);

  std::vector<sf::Texture> textures;
  std::string path_to_directory = "src/Sprites/Golem_1/PNG/PNG Sequences/Walking"; // Replace with your directory path

  // Check if the path exists and is a directory
  if (std::filesystem::exists(path_to_directory) && std::filesystem::is_directory(path_to_directory)) {
    // Iterate over entries in the directory
    for (const auto& entry : std::filesystem::directory_iterator(path_to_directory)) {

      // Check if the entry is a regular file
      if (std::filesystem::is_regular_file(entry.status())) {
        sf::Texture texture;
        if (texture.loadFromFile(entry.path())) {
          textures.push_back(texture);
        }
      }
    }
  } else {
    std::cerr << "Error: Directory not found or not a valid directory." << std::endl;
  }

  sf::Sprite sprite(textures[0]);
  unsigned char current_animation_index = 0;
  unsigned char update_rate = 5;
  unsigned char update_rate_counter = 0;

  sprite.setOrigin({textures[0].getSize().x/2.0f, textures[0].getSize().y/2.0f});
  sprite.setPosition({width/2.0f, height/2.0f});
  sprite.setScale({0.25f, 0.25f});

  while (window->isOpen()) {
    while (const std::optional event = window->pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window->close();
      } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
          window->close();
        }
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
      char dir = 1;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        sprite.setScale({std::abs(sprite.getScale().x), sprite.getScale().y});
        dir = 1;
      } else {
        sprite.setScale({std::abs(sprite.getScale().x) * -1, sprite.getScale().y});
        dir = -1;
      }

      if (current_animation_index >= textures.size()) {
        current_animation_index = 0;
      }

      if (update_rate_counter++ == update_rate) {
        sprite.setTexture(textures[current_animation_index++]);
        sprite.move({dir * 1.0f, 0.0f});
        update_rate_counter = 0;
      }
    }

    // Rendering
    window->clear(sf::Color(0x000000FF));

    // Drawing
    window->draw(sprite);

    window->display();
  }

  return 0;
}
