#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Serial.h"
#include <array>
struct co2val{
	co2val(long x = 0, long y = 0) { xAxis = x; yAxis = y; };

	long xAxis;
	long yAxis;
};
struct comPort {
	std::string name, val;
};

class graphC {
public:
	graphC(sf::RenderWindow* windIn);
	~graphC();
	
	void addPoint(co2val point);
	void getComPorts();
	void render();
	sf::Clock readDelay;
	bool odrvReadStats();
	long calcDefaultViewBounds();
	std::vector<co2val> points;
	int xMaxp = 0;
	int yMaxp = 0;
	sf::VertexArray renderPoints;
	sf::VertexArray staticLines;
	sf::RenderWindow *sfWindow;
	sf::Clock deltaClock;
	std::vector<int> frameTimes;
	std::vector<std::string> imguiLog;
	std::vector<comPort> availableComPorts;
	CSerial *odriveComPort;
	float myColor[4];

	float odrv0axis0color[4];
	float odrv0axis0pos;
	float odrv0axis0setpoint;
	float odrv0axis1color[4];
	float odrv0axis1pos;
	float odrv0axis1setpoint;

	float odrv1axis0color[4];
	float odrv1axis0pos;
	float odrv1axis0setpoint;
	float odrv1axis1color[4];
	float odrv1axis1pos;
	float odrv1axis1setpoint;

	float odrv2axis0color[4];
	float odrv2axis0pos;
	float odrv2axis0setpoint;
	float odrv2axis1color[4];
	float odrv2axis1pos;
	float odrv2axis1setpoint;

	float adjustWidth = 3900;
	float adjustScroll = 0;
	bool widthToggle = false;
	float viewWidth;
};
