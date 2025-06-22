
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>

int main(void) {

  unsigned int width = 640;
  unsigned int height = 360;

  std::unique_ptr<sf::RenderWindow> window =
        std::make_unique<sf::RenderWindow>(sf::VideoMode({width, height}), "Turtorl");

  window->setFramerateLimit(144);

  float time = 0.0f;
  float amp = 10.0f;
  unsigned int sample_rate = 1000;
  unsigned int freq = 10;

  sf::VertexArray sine_wave;
  sine_wave.setPrimitiveType(sf::PrimitiveType::LineStrip);
  sine_wave.resize(sample_rate);



  while (window->isOpen()) {
    time += 0.0069 * -8;
    if (time > 2 * M_PI) time -= 2 * M_PI;

    for (int i = 0; i < sample_rate; i++) {
      float x = static_cast<float>(i) / (sample_rate - 1.0f) * width;
      float y = amp * std::sin(freq * x + time) + height / 2.0f;
      sine_wave[i].position = {x, y};
      sine_wave[i].color = sf::Color::White;
    }

    while (const std::optional event = window->pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window->close();
      } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
          window->close();
        }
      }
    }

    // Rendering
    window->clear(sf::Color(0x000000FF));

    // Drawing
    window->draw(sine_wave);

    window->display();
  }

  return 0;
}
