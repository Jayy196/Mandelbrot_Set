#include <SFML/Graphics.hpp>
#include <iostream>
#include "complexPlane.h"

using namespace std;
//Enum class state variable
enum class State {
	CALCULATING,
	DISPLAYING
};


int main()
{
	//Get Desktop Resolution
	int width = sf::VideoMode::getDesktopMode().width;
	int height = sf::VideoMode::getDesktopMode().height;

	//calculate aspect Ratio
	float aspectRatio = static_cast<float>(height) / static_cast<float>(width);

	//Construct window
	sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Set", sf::Style::Default);

	//construct an object
	ComplexPlane complexPlane(aspectRatio);


	// Construct Font and Text objects
	sf::Font font;
	if (!font.loadFromFile("./fonts/KOMIKAP_.ttf")) cout << "failed to load font..." << endl;
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(10, 10);

	//Construct a VertexArray
	sf::VertexArray pixels(sf::Points, width * height);

	//initialize state variable to Calculaing
	State currentState = State::CALCULATING;


	while (window.isOpen())
	{
		//Input segment
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Handle Event::Closed event to close the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			// Handle Event::MouseButtonPressed
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f coord = window.mapPixelToCoords(sf::Mouse::getPosition(window), complexPlane.getView());

				if (event.mouseButton.button == sf::Mouse::Left)
				{
					// Left click will zoomIn and setCenter of the ComplexPlane object
					complexPlane.zoomin();
					complexPlane.setCenter(coord);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					// Right click will zoomOut and setCenter of the ComplexPlane object
					complexPlane.zoomOut();
					complexPlane.setCenter(coord);
				}

				// Set the state to CALCULATING to generate the new complex plane view in the update segment
				currentState = State::CALCULATING;

			}

			//Handle Event::Mousemoved
			if (event.type == sf::Event::MouseMoved)
			{
				// Find the Vector2f coordinate in the ComplexPlane View that corresponds to the screen mouse location
				sf::Vector2f coord = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y), complexPlane.getView());

				//Set the mouse location on the complex plane object
				complexPlane.setMouseLocation(coord);

			}

		}
		// Check if Keyboard::isKeyPressed(Keyboard::Escape) to close the window
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}


		//update scne segment
		if (currentState == State::CALCULATING)
		{
			for (unsigned int i = 0; i < height; ++i)
			{
				for (unsigned int j = 0; j < width; ++j)
				{
					// Map screen coordinates to complex plane coordinates
					sf::Vector2f coord = window.mapPixelToCoords(sf::Vector2i(j, i), complexPlane.getView());

					// Count the Mandelbrot Set iterations and convert them to RGB color
					std::size_t count = complexPlane.countIterations(coord);
					sf::Uint8 r, g, b;
					complexPlane.iterationsToRGB(count, r, g, b);

					// Set the position and color of the vertex
					pixels[j + i * width].position = { static_cast<float>(j), static_cast<float>(i) };
					pixels[j + i * width].color = sf::Color(r, g, b);
				}

			}

			currentState = State::DISPLAYING;

			//call Load text
			complexPlane.loadText(text);
		}
		window.clear();


		window.draw(pixels);


		window.draw(text);

		// Display
		window.display();

	}

	return 0;
}