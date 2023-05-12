#ifndef COMPLEX_PLANE_H
#define COMPLEX_PLANE_H

#include <SFML/Graphics.hpp>

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;


class ComplexPlane
{
public:
	ComplexPlane(float aspectRatio);
	void zoomin();
	void zoomOut();
	void setCenter(sf::Vector2f coord);
	sf::View getView();
	void setMouseLocation(sf::Vector2f coord);
	void loadText(sf::Text& text);
	std::size_t countIterations(sf::Vector2f coord);
	void iterationsToRGB(std::size_t count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b);

private:
	sf::Vector2f m_mouseLocation;
	sf::View m_view;
	int m_zoomCount;
	float m_aspectRatio;


};

#endif                                   