// serialPort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

#include <imgui.h>
#include "imgui-SFML.h"

#include <iostream>
#include <fstream>
#include <atlbase.h>
#include <cstring>
#include <sstream>
#include "Serial.h"

#include "graph.h"
#include "imgui_memory_editor.h"

std::string logName = "log.txt";

int main(){
	CSerial serial;
	sf::RenderWindow rWindow(sf::VideoMode(1280, 800), "Graph");
	graphC graphWindow(&rWindow);
	std::fstream logStream;
	logStream.open(logName, std::fstream::in | std::fstream::out | std::fstream::app);
	graphWindow.odriveComPort = &serial;
	if (serial.Open(3, 2000000)) {
		std::cout << "Port opened successfully" << std::endl;
		sf::Clock timerPoint;
		timerPoint.restart();
		
		char lpBuffer[256];
		memset(lpBuffer, 0,256);
		while (serial.IsOpened()) {

		int nBytesRead = serial.ReadData(lpBuffer,256);
		if (nBytesRead) {
			std::stringstream ss;
			for (int i = 0; i < 256 && i < nBytesRead; ++i) {
				ss << std::hex << (int)lpBuffer[i];
			}
			std::string mystr = ss.str();
			std::cout << mystr << std::endl;
			graphWindow.imguiLog.push_back(std::string(lpBuffer));
			memset(lpBuffer, 0,256);

		}

		if (!rWindow.isOpen()) {
			if (logStream.is_open()) {
				logStream.close();
			}
			return 0;
		}
		rWindow.clear();
		//graphWindow.odrvReadStats();
		graphWindow.render();
		rWindow.display();
	}
	}

}

