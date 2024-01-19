#include <iostream>

#include <SFML/Graphics.hpp>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML/Audio.hpp" 
#include <fstream>
#include <cstdlib>
#include <sstream>

class Zatvor {

public:
	int zatvori;

};


int main() {

	srand(time(NULL));

	sf::RenderWindow meni(sf::VideoMode(640, 480), "Izbornik");
	meni.setFramerateLimit(60);

	//varijabla za gasenje
	Zatvor Z;
	Z.zatvori = 0;
	
	int h = 0;
	int g = 0;

	//setanje fonta za "Play"
	sf::Font font1;
	font1.loadFromFile("arial.ttf");

	sf::Text play;
	play.setFont(font1);
	play.setPosition(280, 250);
	play.setCharacterSize(50);
	play.setFillColor(sf::Color::White);

	play.setString("Play");

	//setanje fonta za press ENTER

	sf::Font font2;
	font2.loadFromFile("arial.ttf");

	sf::Text enter;
	enter.setFont(font2);
	enter.setPosition(100,150);
	enter.setCharacterSize(50);
	enter.setFillColor(sf::Color::White);

	enter.setString("Press ENTER to play");

	sf::Clock clock1;
	sf::Time vrijeme1;

	//MENI
	while (meni.isOpen()) {

		sf::Event ev;

		while (meni.pollEvent(ev)) {


			if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) {



				meni.close();
				Z.zatvori=1;

			}

			if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter) {



				h = 1;
				vrijeme1 = clock1.getElapsedTime();
				std::cout << vrijeme1.asSeconds() << std::endl;

				clock1.restart();
			
				
			}

		}


		if (h == 1) {

			vrijeme1 = clock1.getElapsedTime();
			std::cout << vrijeme1.asSeconds() << std::endl;

			if (vrijeme1.asSeconds() >= 5)
				meni.close();
		
		}

		if (h == 1)
			meni.clear(sf::Color::Red);


		//meni.draw(play);
		meni.draw(enter);
		meni.draw(play);

		meni.display();
	}


	sf::RenderWindow window(sf::VideoMode(640, 480), "Agri");
	
	window.setFramerateLimit(60);

	//Trokut

	sf::Texture trokutTexture;
	sf::Sprite trokut;

	trokutTexture.loadFromFile("trokutr.png");

	trokut.setTexture(trokutTexture);

	//trokut.setScale(sf::Vector2f(0.8f, 0.8f));



	std::vector<sf::Sprite> trokuti;
	trokuti.push_back(sf::Sprite(trokut));

	int trokutSpwanTimer = 1;

	//Kvadrat
	sf::Texture kvadratTexture;
	sf::Sprite kvadrat;

	kvadratTexture.loadFromFile("kvadrat1.png");

	kvadrat.setTexture(kvadratTexture);

	kvadrat.setScale(sf::Vector2f(0.5f, 0.5f));

	std::vector<sf::Sprite> kvadrati;
	kvadrati.push_back(sf::Sprite(kvadrat));

	int kvadratSpawnTimer = 20;

	//Srca
	sf::Texture srceTexture;
	sf::Sprite srce;

	srceTexture.loadFromFile("Srcee.png");

	srce.setTexture(srceTexture);

	srce.setScale(sf::Vector2f(0.3f, 0.3f));

	std::vector<sf::Sprite> srca;
	srca.push_back(sf::Sprite(srce));

	int srceSpawnTimer = 1;

	//Glavni lik
	sf::Texture sefTexture;
	sf::Sprite sef;

	sefTexture.loadFromFile("batman.png");

	sef.setTexture(sefTexture);

	sef.setScale(sf::Vector2f(0.5f, 0.5f));


	//Health
	int hp = 5;

	sf::RectangleShape hpBar;
	hpBar.setFillColor(sf::Color::Cyan);
	hpBar.setSize(sf::Vector2f((float)hp * 20.f, 20.f));
	hpBar.setPosition(200.f, 10.f);

	//Tekst minuta ispisan
	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text tekst;
	tekst.setFont(font);
	tekst.setPosition(510, 20);
	tekst.setCharacterSize(15);
	tekst.setFillColor(sf::Color::Black);

	//Vrijeme clock
	sf::Clock clock;
	sf::Time vrijeme;



	std::stringstream ss;

	//Points (tekst)
	int point = 0;

	//Muzika
	//sf::Music music;
	//music.openFromFile("Snipes.ogg");
	//music.setVolume(50);

	//music.play();



	//Window
	while (window.isOpen() && hp > 0) {

		sf::Event e;

		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed || hp == 0) {


				window.close();

			}

			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape || Z.zatvori == 1) {
				

				window.close();

			}
		}

		//Kretanje Glavnog lika
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sef.getPosition().y > 0) {
			sef.move(0.f, -5.f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sef.getPosition().y + sef.getGlobalBounds().height < window.getSize().y) {
			sef.move(0.f, 5.f);
		}

		//Kretanje kvadrata
		for (int i = 0; i < kvadrati.size(); i++) {
			kvadrati[i].move(-7.f, 0.f);

			if (kvadrati[i].getPosition().x < 0 - kvadrat.getGlobalBounds().width) {
				kvadrati.erase(kvadrati.begin() + i);
				point++;
			}
		}

		//Kretanje trokuta
		for (int i = 0; i < trokuti.size(); i++) {
			trokuti[i].move(-7.f, 0.f);

			if (trokuti[i].getPosition().x < 0 - trokut.getGlobalBounds().width) {
				trokuti.erase(trokuti.begin() + i);
				point++;
			}
		}

		//Kretanje srca
		for (int i = 0; i < srca.size(); i++) {
			srca[i].move(-rand() % 9, rand() % 3);

			if (srca[i].getPosition().x < 0 - srce.getGlobalBounds().width) {
				srca.erase(srca.begin() + i);
			}
		}


		//Spawnanje trokuta
		if (trokutSpwanTimer < 80)
			trokutSpwanTimer++;

		if (trokutSpwanTimer >= 80) {
			trokut.setPosition(window.getSize().x, rand() % int(window.getSize().y - trokut.getGlobalBounds().height));
			trokuti.push_back(sf::Sprite(trokut));
			trokutSpwanTimer = 0;
		}

		//Spawnanje kvadrata
		if (kvadratSpawnTimer < 80)
			kvadratSpawnTimer++;

		if (kvadratSpawnTimer >= 80) {
			kvadrat.setPosition(window.getSize().x, rand() % int(window.getSize().y - kvadrat.getGlobalBounds().height));
			kvadrati.push_back(sf::Sprite(kvadrat));
			kvadratSpawnTimer = 0;
		}

		//Spawnanje srca
		if (srceSpawnTimer < 200)
			srceSpawnTimer++;

		if (srceSpawnTimer >= 200) {
			srce.setPosition(window.getSize().x, rand() % int(window.getSize().y - srce.getGlobalBounds().height));
			srca.push_back(sf::Sprite(srce));
			srceSpawnTimer = 0;
		}


		//Sudari
		//sudari izmedju glavnog lika(sefa) i trokuta

		for (int i = 0; i < trokuti.size(); i++) {
			if (sef.getGlobalBounds().intersects(trokuti[i].getGlobalBounds())) {

				hp--;
				trokuti.erase(trokuti.begin() + i);

			}
		}
		//sudari izmedju glavnog lika(sefa) i kvadrata

		for (int i = 0; i < kvadrati.size(); i++) {
			if (sef.getGlobalBounds().intersects(kvadrati[i].getGlobalBounds())) {

				hp--;
				kvadrati.erase(kvadrati.begin() + i);
			}
		}

		//sudari izmedju glavnog lika(sefa) i srca
		for (int i = 0; i < srca.size(); i++) {
			if (sef.getGlobalBounds().intersects(srca[i].getGlobalBounds())) {

				hp++;
				srca.erase(srca.begin() + i);
			}
		}

		//sudari(Brisanje) trokuta i kvadrata ZA SVAKI SLUCAJ!!!!!
		for (int i = 0; i < kvadrati.size(); i++) {
			for (int j = 0; j < trokuti.size(); j++) {
				if (trokuti[j].getGlobalBounds().intersects(kvadrati[i].getGlobalBounds())) {


					kvadrati.erase(kvadrati.begin() + i);
					trokuti.erase(trokuti.begin() + j);
					std::cout << "1" << std::endl;
				}
			}
		}

		//Vrijeme 2 Update i GUI
		vrijeme = clock.getElapsedTime();
		std::cout << vrijeme.asSeconds() << std::endl;

		ss.str(std::string());
		ss << "Sekunde: ";
		ss << vrijeme.asSeconds();
		tekst.setString(ss.str().c_str());
		ss << vrijeme.asSeconds();

		//ispisuje vrijeme nakon smrti

		if (hp == 0) {
			std::ofstream vrijemeFile;
			vrijemeFile.open("Najbolje_vrijeme.txt");
			vrijemeFile << "Vrijeme: " << vrijeme.asSeconds() << std::endl;
			vrijemeFile.close();
		}



		//GUI
		hpBar.setSize(sf::Vector2f((float)hp * 20.f, 20.f));

		

		//Update
		window.clear(sf::Color::Red);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			window.clear(sf::Color::Red);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			window.clear(sf::Color::Blue);

		//Draw

		for (int i = 0; i < kvadrati.size(); i++) {
			window.draw(kvadrati[i]);
		}

		for (int j = 0; j < trokuti.size(); j++) {
			window.draw(trokuti[j]);
		}

		for (int k = 0; k < srca.size(); k++) {
			window.draw(srca[k]);
		}

		window.draw(sef);

		window.draw(hpBar);

		window.draw(tekst);

		window.display();

	}


	return 0;

}