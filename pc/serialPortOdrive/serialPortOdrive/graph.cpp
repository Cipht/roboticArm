#include "graph.h"
#include <imgui.h>
#include <string>
#include <atlbase.h>
#include "imgui-SFML.h"
#include "Serial.h"
#include <limits>
#include <iostream>
#include <array>
#include "imgui_memory_editor.h"
graphC::graphC(sf::RenderWindow* windIn) {
	sfWindow = windIn;
	ImGui::SFML::Init(*sfWindow);
	myColor[0] = 0.4;//r
	myColor[1] = 0.2;//g
	myColor[2] = 0.6;//b
	myColor[3] = 1.0;//alpha

	renderPoints.setPrimitiveType(sf::PrimitiveType::LineStrip);
	renderPoints.resize(100000);
	staticLines.setPrimitiveType(sf::PrimitiveType::Lines);
	sf::Vertex p1(sf::Vector2f(0,-1000),sf::Color::Red);
	sf::Vertex p2(sf::Vector2f(1000000,-1000),sf::Color::Red);
	staticLines.append(p1);
	staticLines.append(p2);

	sf::Vertex w1(sf::Vector2f(0,0),sf::Color::White);
	sf::Vertex w2(sf::Vector2f(1000000,0),sf::Color::White);
	staticLines.append(w1);
	staticLines.append(w2);

	sf::Vertex g1(sf::Vector2f(0,-400),sf::Color::Green);
	sf::Vertex g2(sf::Vector2f(1000000,-400),sf::Color::Green);
	staticLines.append(g1);
	staticLines.append(g2);
	
	for (int i = 0; i < 1000000; i=i+6000) {
		int height = -10;
		if (i % 30*60 == 0)
			height = -25;
		sf::Vertex s1(sf::Vector2f(i,height),sf::Color::White);
		sf::Vertex s2(sf::Vector2f(i,0),sf::Color::White);
		staticLines.append(s1);
		staticLines.append(s2);
	}
	for (int i = 0; i < 1000000; i = i + 60 * 6000) {
		sf::Vertex s1(sf::Vector2f(i, -50), sf::Color::Yellow);
		sf::Vertex s2(sf::Vector2f(i, 0), sf::Color::Yellow);
		staticLines.append(s1);
		staticLines.append(s2);
	}
	renderPoints.append(sf::Vertex(sf::Vector2f(65*60, 100),sf::Color::Transparent));
	renderPoints.append(sf::Vertex(sf::Vector2f(0, -1100),sf::Color::Transparent));

}


graphC::~graphC() {

}

void graphC::addPoint(co2val point) {
	int timeScale = 5;//seconds per point
	float xPoint = point.xAxis / timeScale;

	//points.push_back(point);
	sf::Vector2f v2f((float)xPoint, -(float)point.yAxis);
	renderPoints.append(sf::Vertex(v2f,sf::Color(myColor[0] * 255.f,myColor[1] * 255.f,myColor[2] * 255.f,myColor[3] * 255.f)));
}

#define BUFF_SIZE 500
void graphC::getComPorts(){
	CRegKey regkey;
	DWORD dwI = 0, nBuffSize = BUFF_SIZE;
	TCHAR szKeyName[BUFF_SIZE], szKeyVal[BUFF_SIZE];
	LONG nCode = ERROR_SUCCESS;
	UINT nCOMPort = 0;
	availableComPorts.clear();
	memset(szKeyName, 0, BUFF_SIZE);
	memset(szKeyVal, 0, BUFF_SIZE);
	if (regkey.Open(HKEY_LOCAL_MACHINE, L"HARDWARE\\DEVICEMAP\\SERIALCOMM", KEY_READ) == ERROR_SUCCESS)
	{
		do
		{
			nCode = RegEnumValue(regkey.m_hKey, dwI, (LPWSTR)szKeyName, &nBuffSize, NULL, NULL, NULL, NULL);
			if (nCode != ERROR_NO_MORE_ITEMS)
			{
				nBuffSize = BUFF_SIZE;
				regkey.QueryStringValue(szKeyName, szKeyVal, &nBuffSize);
				nBuffSize = BUFF_SIZE;
				comPort port;
				char output[256];
				sprintf_s(output, "%ws", szKeyName);
				port.name = std::string(output);
				sprintf_s(output, "%ws", szKeyVal);
				port.val= std::string(output);
				availableComPorts.push_back(port);
				imguiLog.push_back(port.name + " " + port.val);
				//std::wcout << szKeyName << "  " << szKeyVal << std::endl;
		
				ImGui::Text("%s: width %s: height",szKeyName, szKeyVal);
				dwI++;
			}
		} while (nCode != ERROR_NO_MORE_ITEMS);
	}
}
int motor0pos = 0;
int motor1pos = 0;
char comSendBuf[512] = "\0\0";
void graphC::render() {
	if (sfWindow->isOpen()) {
		sf::Event event;
		while (sfWindow->pollEvent(event)){
       // Request for closing the window
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) {
				sfWindow->close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					sfWindow->close();
				}

			}
		}

		sf::FloatRect bounds = renderPoints.getBounds();
		deltaClock.getElapsedTime().asMilliseconds();
        ImGui::SFML::Update(*sfWindow, deltaClock.restart());


		ImGui::Begin("log");
		
		ImGui::InputText("", comSendBuf, 512);
		if (ImGui::Button("send", ImVec2(200, 20))) {
			std::string strBuffer(comSendBuf);
			strBuffer += "\n";
			odriveComPort->SendData(strBuffer.c_str(), strBuffer.length());
			imguiLog.push_back(strBuffer);
		}
		for (int i = imguiLog.size() - 1; i >= 0; i--) {
			ImGui::Text("%s", imguiLog[i].c_str());
		}
		ImGui::End();

		ImGui::Begin("com ports");
		if (ImGui::Button("refresh", ImVec2(200, 20))) {
			getComPorts();
		}
		for (int i = 0; i < availableComPorts.size();i++) {
			ImGui::Button(std::string(availableComPorts[i].name + " " + availableComPorts[i].val).c_str(),ImVec2(200,20));
		}
		ImGui::End();
		//odrives

		ImGui::Begin("odrv 0");
		ImGui::BeginChild("axis0",ImVec2(200,120));
		ImGui::Text("axis0");
		//calibrate
		if (ImGui::Button("calibrate", ImVec2(200, 20))) {
			std::string strBuffer("w axis0.requested_state 3\n");
			odriveComPort->SendData( strBuffer.c_str(), strBuffer.length());
			imguiLog.push_back(strBuffer);
		}
		//closed loop control
		if (ImGui::Button("closed loop", ImVec2(200, 20))) {
			std::string strBuffer("w axis0.requested_state 8\n");
			odriveComPort->SendData( strBuffer.c_str(), strBuffer.length());
			imguiLog.push_back(strBuffer);
		}

		ImGui::SliderInt("motor pos", &motor0pos, -350000, 350000);

		if (ImGui::Button("t move", ImVec2(200, 20))) {
			std::string strBuffer("t 0 ");
			char itoaBuff[64];
			_itoa_s(motor0pos, itoaBuff, 63,10);
			strBuffer += itoaBuff;
			strBuffer += "\n";
			odriveComPort->SendData( strBuffer.c_str(), strBuffer.length());
			imguiLog.push_back(strBuffer);
		}

		ImGui::EndChild();

		ImGui::BeginChild("axis1",ImVec2(200,120));
		ImGui::Text("axis1");
		//calibrate
		if (ImGui::Button("calibrate", ImVec2(200, 20))) {
			std::string strBuffer("w axis1.requested_state 3\n");
			odriveComPort->SendData(strBuffer.c_str(), strBuffer.length());
			imguiLog.push_back(strBuffer);
		}
		//closed loop control
		if (ImGui::Button("closed loop", ImVec2(200, 20))) {
			std::string strBuffer("w axis1.requested_state 8\n");
			odriveComPort->SendData(strBuffer.c_str(), strBuffer.length());
			imguiLog.push_back(strBuffer);
		}

		ImGui::SliderInt("motor pos", &motor1pos, -350000, 350000);

		if (ImGui::Button("t move", ImVec2(200, 20))) {
			std::string strBuffer("t 1 ");
			char itoaBuff[64];
			_itoa_s(motor1pos, itoaBuff, 63, 10);
			strBuffer += itoaBuff;
			strBuffer += "\n";
			odriveComPort->SendData(strBuffer.c_str(), strBuffer.length());
			imguiLog.push_back(strBuffer);
		}

		ImGui::EndChild();
		ImGui::End();

		//static MemoryEditor mEdit;
		//ImGui::Begin("mem");
		//mEdit.DrawContents(&imguiLog.at(0), dsize, 0x000000);
		//ImGui::End();

		if (widthToggle) {
			bounds.width = adjustWidth;
			bounds.left = adjustScroll;
		}
		sfWindow->setView(sf::View((bounds)));
		//sfWindow->clear();

		sfWindow->draw(renderPoints);
		sfWindow->draw(staticLines);
		ImGui::SFML::Render(*sfWindow);
		//sfWindow->display();
	}
}

long graphC::calcDefaultViewBounds() {
	//scale view bounds based on total time and number of points/pixels
	long retv = 0;
	return retv;
}
std::array<std::string,3> odrvCommands {
	"r vbus_voltage\r\n",
	"r axis0.encoder.pos_estimate\r\n",
	"r axis1.encoder.pos_estimate\r\n"
};
bool graphC::odrvReadStats() {
	char recvBuf[513];
	if (readDelay.getElapsedTime().asMilliseconds() > 500) {
		readDelay.restart();
		for (int i = 0; i < odrvCommands.size(); i++) {
			odriveComPort->SendData(odrvCommands[i].c_str(), odrvCommands[i].length());
		}

		memset(recvBuf, 0, 513);
		Sleep(4);
		int numReplies = 0;
		std::string replies[odrvCommands.size()];
		while (numReplies < odrvCommands.size()) {

			int bytesRead = odriveComPort->ReadData(recvBuf, 127);

			if (bytesRead != 0){
				//bytes read
				replies[numReplies] += recvBuf;

			}

			else {
				//no bytes read
			}
			std::size_t pos  = replies[numReplies].find("\r\n");
			if (pos != 0) {

				numReplies++;
				if (numReplies < odrvCommands.size()) {
					replies[numReplies] = replies[numReplies - 1].substr(pos+2);
				}
			}
		}
		for (int i = 0; i < odrvCommands.size(); i++) {
			imguiLog.push_back(odrvCommands[i] + " " + replies[i]);
		}
	}
	



	return true;
}