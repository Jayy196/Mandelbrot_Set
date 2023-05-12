#include "complexPlane.h"
#include <cmath>
#include <sstream>
#include <complex>

using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(float aspectRatio)
	: m_aspectRatio(aspectRatio)
{
	Vector2f size(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	Vector2f center(-0.5f, 0.0f);
	m_view.setSize(size);
	m_view.setCenter(center);
	m_zoomCount = 0;

}

void ComplexPlane::zoomin()
{
	m_zoomCount++;
	float newSizeX = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float newSizeY = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(newSizeX, newSizeY);
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float newSizeX = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float newSizeY = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(newSizeX, newSizeY);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

sf::View ComplexPlane::getView()
{
	return m_view;
}

void ComplexPlane::loadText(Text& text)
{
	stringstream ss;
	ss << "Mandelbrot Set\n";
	ss << "Center: (" << m_view.getCenter().x << ", " << m_view.getCenter().y << ")\n";
	ss << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n";
	ss << "Left-click to Zoom in\n";
	ss << "Right-click to Zoom out\n";

	text.setString(ss.str());
}


size_t ComplexPlane::countIterations(Vector2f coord)
{
	complex<float> c(coord.x, coord.y);
	complex<float> z(0, 0);

	for (size_t i = 0; i < MAX_ITER; i++)
	{
		z = z * z + c;
		if (abs(z) > 2.0)
		{
			return i;
		}
	}

	return MAX_ITER;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count >= MAX_ITER) {

		r = 0;
		g = 0;
		b = 0;
	}
	else {

		Uint8 intensity = static_cast<Uint8>(255 * (static_cast<float>(count) / MAX_ITER));
		r = intensity;
		g = intensity;
		b = intensity;
	}
}