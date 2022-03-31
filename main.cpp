#include <SFML\Graphics.hpp>
#include <windows.h>
#include <algorithm>
#include <string>
#include <ctime>

using namespace sf;
using namespace std;

// ZXC Dodger by manda(ZXC Team)

// Function "to_string" not my!

std::string to_string(int param)
{
    std::string str = "";
    for(str = ""; param ; param /= 10)
        str += (char)('0' + param % 10);
    reverse(str.begin(), str.end());
    return str;
}

bool isBtnPressed(RenderWindow &window, RectangleShape btn, Event ev)
{
	float mx = Mouse::getPosition(window).x;
	float my = Mouse::getPosition(window).y;
		
	float bx = btn.getPosition().x;
	float by = btn.getPosition().y;
		
	float bw = btn.getPosition().x + btn.getLocalBounds().width;
	float bh = btn.getPosition().y + btn.getLocalBounds().height;
	
	if (mx < bw && mx > bx && my < bh && my > by && ev.type == Event::MouseButtonPressed)
	{
		return true;
	}
	else
	{
		return false;
	}
}

enum State
{
	LEFT, RIGHT
};

int main()
{
	
	State pstate;
	
	srand(time(0));
	
	int cht = 0;
	int i = 0;
	int score = 0;
	
	float bgy;
	float abgy = -720.0f;
	float my = -120;
	float nmy = -140;
	float px = 65;
	
	bool m2go = false;
	bool exit = false;
	bool isGameStarted = false;
	
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	Texture tplayer;
	if (!tplayer.loadFromFile("assets/ball.png"))
	{
		MessageBox(NULL, "Can't load file 'ball.png' from 'assets' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	Texture tlogo;
	if (!tlogo.loadFromFile("assets/logo.png"))
	{
		MessageBox(NULL, "Can't load file 'logo.png' from 'assets' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	
	Texture tplaybtn;
	if (!tplaybtn.loadFromFile("assets/buttons/playbtn.png"))
	{
		MessageBox(NULL, "Can't load file 'playbtn.png' from 'assets' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	Texture texitbtn;
	if (!texitbtn.loadFromFile("assets/buttons/exitbtn.png"))
	{
		MessageBox(NULL, "Can't load file 'exitbtn.png' from 'assets' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	Texture tplaybtnprsd;
	if (!tplaybtnprsd.loadFromFile("assets/buttons/playbtnpressed.png"))
	{
		MessageBox(NULL, "Can't load file 'playbtnpressed.png' from 'assets' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	Texture texitbtnprsd;
	if (!texitbtnprsd.loadFromFile("assets/buttons/exitbtnpressed.png"))
	{
		MessageBox(NULL, "Can't load file 'exitbtnpressed.png' from 'assets' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	Texture tbg;
	if (!tbg.loadFromFile("assets/bg.png"))
	{
		MessageBox(NULL, "Can't load file 'bg.png' from 'assets' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	Texture tmachine;
	if (!tmachine.loadFromFile("assets/machines/machine1.png"))
	{
		MessageBox(NULL, "Can't load file 'machine1.png' from 'assets' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	Texture tmachine2;
	if (!tmachine2.loadFromFile("assets/machines/machine2.png"))
	{
		MessageBox(NULL, "Can't load file 'machine2.png' from 'assets' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	Texture tmachine3;
	if (!tmachine3.loadFromFile("assets/machines/machine3.png"))
	{
		MessageBox(NULL, "Can't load file 'machine3.png' from 'assets' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	Texture tmachine4;
	if (!tmachine4.loadFromFile("assets/machines/machine4.png"))
	{
		MessageBox(NULL, "Can't load file 'machine4.png' from 'assets' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	Font font;
	if (!font.loadFromFile("fonts/font.ttf"))
	{
		MessageBox(NULL, "Can't load file 'font.ttf' from 'fonts' folder", "Error", MB_ICONEXCLAMATION);
		return 0;
	}
	
	Text tscore;
	tscore.setCharacterSize(56);
	tscore.setFont(font);
	tscore.setFillColor(Color::Red);
	tscore.setString("0");
	tscore.setPosition(Vector2f(167, 25));
	
	RectangleShape player(Vector2f(50, 50));
	player.setTexture(&tplayer);
	player.setPosition(Vector2f(65, 480));
	
	RectangleShape playbtn(Vector2f(168, 90));
	playbtn.setTexture(&tplaybtn);
	playbtn.setPosition(Vector2f(95, 350));
	
	RectangleShape exitbtn(Vector2f(168, 90));
	exitbtn.setTexture(&texitbtn);
	exitbtn.setPosition(Vector2f(95, 480));
	
	RectangleShape bg(Vector2f(360, 720));
	bg.setTexture(&tbg);
	
	RectangleShape logo(Vector2f(248, 128));
	logo.setTexture(&tlogo);
	logo.setPosition(Vector2f(60, 50));
	
	RectangleShape abg(Vector2f(360, 720));
	abg.setTexture(&tbg);
	abg.setPosition(Vector2f(0, -720));
	
	RectangleShape machine(Vector2f(100, 130));
	machine.setTexture(&tmachine);
	
	RectangleShape nmachine(Vector2f(100, 130));
	nmachine.setTexture(&tmachine);
	
	Image icon;
	icon.loadFromFile("icon.png");
	
	RenderWindow window(VideoMode(360, 720), "ZXC Dodger");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		
	while (window.isOpen())
	{
		
		if (score >= 10)
		{
			tscore.setPosition(Vector2f(161, 25));
		}
		
		if (nmy != 720 && m2go == true)
		{
			nmy += 0.05 + score * 0.002;
		}
		
		if (my != 720)
		{
			my += 0.05 + score * 0.002;
		}
		
		if (my >= 300)
		{
			m2go = true;
		}
		
		if (my >= 720)
		{
			cht = 1 + rand() % 4;
			switch (cht)
			{
				case 1:
					machine.setTexture(&tmachine);
					break;
				case 2:
					machine.setTexture(&tmachine2);
					break;
				case 3:
					machine.setTexture(&tmachine3);
					break;
				case 4:
					machine.setTexture(&tmachine4);
					break;
			}
			my = -140;
			score++;
		}
		
		if (nmy >= 720)
		{
			cht = 1 + rand() % 4;
			switch (cht)
			{
				case 1:
					nmachine.setTexture(&tmachine);
					break;
				case 2:
					nmachine.setTexture(&tmachine2);
					break;
				case 3:
					nmachine.setTexture(&tmachine3);
					break;
				case 4:
					nmachine.setTexture(&tmachine4);
					break;
			}
			nmy = -140;
			m2go = false;
			score++;
		}
		
		if (exit == true)
		{
			Sleep(970);
			return 0;
		}
		
		nmachine.setPosition(Vector2f(215, nmy));
		machine.setPosition(Vector2f(45, my));
		bg.setPosition(Vector2f(0, bgy));
		abg.setPosition(Vector2f(0, abgy));
		player.setPosition(Vector2f(px, 480));
		
		if (bgy != 720)
		{
			bgy += 0.05 + score * 0.002;
		}
		
		if (bgy >= 720)
		{
			bgy = -720;
		}
		
		if (abgy != 720)
		{
			abgy += 0.05 + score * 0.002;
		}
		
		if (abgy >= 720)
		{
			abgy = -720;
		}
		
		Event myEvent;
		while (window.pollEvent(myEvent))
		{
			if (myEvent.type == Event::Closed)
			{
				window.close();
			}
			
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				px = 65;
				pstate = LEFT;
			}
			
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				px = 240;
				pstate = RIGHT;
			}
		}
		
		if (isBtnPressed(window, playbtn, myEvent) == true)
		{
			playbtn.setTexture(&tplaybtnprsd);
			isGameStarted = true;
			m2go = false;
		}
		else
		{
			playbtn.setTexture(&tplaybtn);
		}
		
		if (isBtnPressed(window, exitbtn, myEvent) == true)
		{
			exitbtn.setTexture(&texitbtnprsd);
			exit = true;
		}
		else
		{
			exitbtn.setTexture(&texitbtn);
		}
		
		if (isGameStarted == true)
		{
			i++;
		}
		
		window.clear();
		window.draw(bg);
		window.draw(abg);
		
		if (isGameStarted == false || i < 1000)
 		{
			window.draw(playbtn);
			window.draw(exitbtn);
			window.draw(logo);
			nmy = -140;
			my = -140;
		}
		
		if (isGameStarted == true)
		{
			window.draw(tscore);
			window.draw(machine);
			window.draw(nmachine);
		}
		
		window.draw(player);
		window.display();
		
		if (nmy > 350 && nmy < 520 && pstate == RIGHT)
		{
			isGameStarted = false;
			m2go = false;
			score = 0;
			tscore.setString("0");
			tscore.setPosition(Vector2f(167, 25));
		}
		
		if (my > 350 && my < 520 && pstate == LEFT)
		{
			isGameStarted = false;
			m2go = false;
			score = 0;
			tscore.setString("0");
			tscore.setPosition(Vector2f(167, 25));
		}
		
		if (score > 0)
		{
			tscore.setString(to_string(score));
		}
	}
}
