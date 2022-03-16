#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <string>

using namespace std;
using namespace sf;

#define WIDTH 1600
#define HEIGHT 900

class Object {
private:
	float x;
	float y;
public:
	float getX() { return x; }
	float getY() { return y; }
	void setX(float xval) { x = xval; }
	void setY(float yval) { y = yval; }
};

class Player : public Object {
private:
	int score;
	bool isJumping;
	bool isBottom;
	bool isDiving;
public:
	bool getIsJumping() { return isJumping; }
	bool getIsBottom() { return isBottom; }
	bool getIsDiving() { return isDiving; }
	void setIsJumping(bool jumping) { isJumping = jumping; }
	void setIsBottom(bool bottom) { isBottom = bottom; }
	void setIsDiving(bool diving) { isDiving = diving; }
	void setScore(int s) { score = s; }
	int getScore() { return score; }
};

int main() {
	Player p1C;
	Player p2C;
	Object ballC;

	bool start = false;
	bool setting = false;
	bool over = false;
	const int gravity = 10;
	static const float X_Vel = 15;
	float dx = 0;
	float dy = 10;
	int p1Index = 0;
	int p2Index = 0;
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "BEARS Volleyball");
	window.setFramerateLimit(60);
	Image icon;
	icon.loadFromFile("images/ball.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	Font font;
	font.loadFromFile("font/NanumSquareRoundB.ttf");
	Text title("\n      BEARS Volleyball", font, 150);
	Text startText("\n\n\n\n\n\n\n\n\n                                        Press Enter to continue!!", font, 50);
	Text Score,p1Score,p2Score;
	Text endText;
	Score.setFont(font);
	Score.setCharacterSize(150);
	Score.setFillColor(Color::Black);
	Score.setStyle(Text::Bold);
	Score.setString(":");
	Score.setPosition(777, 0);
	p1Score.setFont(font);
	p1Score.setCharacterSize(150);
	p1Score.setFillColor(Color::Black);
	p1Score.setStyle(Text::Bold);
	p1Score.setPosition(250, 0);
	p2Score.setFont(font);
	p2Score.setCharacterSize(150);
	p2Score.setFillColor(Color::Black);
	p2Score.setStyle(Text::Bold);
	p2Score.setPosition(1200, 0);
	title.setFillColor(Color::Black);
	title.setStyle(Text::Bold);
	startText.setFillColor(Color::Black);
	endText.setFont(font);
	endText.setCharacterSize(90);
	endText.setFillColor(Color::Black);
	endText.setPosition(500,300);

	Music music;
	music.openFromFile("musics/mainMusic.wav");
	Sound bounce, crowd, scoreM;
	SoundBuffer bounceb,crowdb, scoreb;
	bounceb.loadFromFile("musics/Bounce.wav");
	bounce.setBuffer(bounceb);
	crowdb.loadFromFile("musics/Crowd.wav");
	crowd.setBuffer(crowdb);
	scoreb.loadFromFile("musics/ScoreM.wav");
	scoreM.setBuffer(scoreb);

	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;
	t1.loadFromFile("images/main.jpg");
	t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/ball.png");
	t4.loadFromFile("images/bear1.png");
	t5.loadFromFile("images/bear2.png");
	t6.loadFromFile("images/bear3.png");
	t7.loadFromFile("images/bear4.png");
	t8.loadFromFile("images/winbear1.png");
	t9.loadFromFile("images/winbear2.png");
	t10.loadFromFile("images/bear5.png");
	t11.loadFromFile("images/bear6.png");

	RectangleShape wall(Vector2f(20, 330));
	Sprite mainBackground(t1), background(t2), ball(t3);
	Sprite p1[4], p2[4];
	p1[0] = Sprite(t4);
	p1[1] = Sprite(t6);
	p1[2] = Sprite(t7);
	p1[3] = Sprite(t8);
	p2[0] = Sprite(t5);
	p2[1] = Sprite(t10);
	p2[2] = Sprite(t11);
	p2[3] = Sprite(t9);

	ballC.setX(250);
	ballC.setY(150);
	p1C.setX(200);
	p1C.setY(840);
	p2C.setX(1400);
	p2C.setY(840);
	wall.setFillColor(Color::Transparent);
	wall.setOrigin(10, 0);
	wall.setPosition(800, 515);
	ball.setOrigin(96, 96);
	ball.setScale(0.7f, 0.7f);
	ball.setPosition(ballC.getX(), ballC.getY());
	p1[0].setOrigin(0, 666);
	p1[0].setPosition(p1C.getX(), p1C.getY());
	p1[0].setScale(0.3f, 0.3f);
	p1[1].setOrigin(1267, 840);
	p1[1].setPosition(p1C.getX(), p1C.getY());
	p1[1].setScale(0.17f, 0.17f);
	p1[2].setOrigin(0, 840);
	p1[2].setPosition(p1C.getX(), p1C.getY());
	p1[2].setScale(0.17f, 0.17f);
	p1[3].setOrigin(619, 1925);
	p1[3].setScale(0.15f, 0.15f);
	p1[3].setPosition(p1C.getX(), p1C.getY());
	p2[0].setOrigin(347, 666);
	p2[0].setPosition(p2C.getX(), p2C.getY());
	p2[0].setScale(0.3f, 0.3f);
	p2[1].setOrigin(1267, 871);
	p2[1].setPosition(p2C.getX(), p2C.getY());
	p2[1].setScale(0.15f, 0.15f);
	p2[2].setOrigin(0, 871);
	p2[2].setPosition(p2C.getX(), p2C.getY());
	p2[2].setScale(0.15f, 0.15f);
	p2[3].setOrigin(619, 1925);
	p2[3].setPosition(p2C.getX(), p2C.getY());
	p2[3].setScale(0.11f, 0.11f);
	p1C.setIsJumping(false);
	p1C.setIsBottom(true);
	p1C.setIsDiving(false);
	p1C.setScore(0);
	p2C.setIsJumping(false);
	p2C.setIsBottom(true);
	p2C.setIsDiving(false);
	p2C.setScore(0);

	static const float Y_BOTTOM = p1C.getY();

	music.play();
	while (window.isOpen()) {
		Event event;
		if (!start) {
			window.clear();
			window.draw(mainBackground);
			window.draw(title);
			window.draw(startText);
		}
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter) && !start) {
			start = true;
			window.clear();
		}
		if (start) {
			music.stop();
			window.draw(background);
			window.draw(ball);
			ball.setPosition(250, 150);
			window.draw(p1[p1Index]);
			window.draw(p2[p2Index]);
			window.draw(wall);
			ball.rotate(10);
			window.draw(Score);
			window.draw(p1Score);
			p1Score.setString(to_string(p1C.getScore()));
			p2Score.setString(to_string(p2C.getScore()));
			window.draw(p2Score);
			setting = true;
		}

		//p1Moving
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				p1C.setX(p1C.getX() - 20.0f);
				if (p1C.getIsBottom() && !p1C.getIsJumping()) {
					p1C.setIsDiving(true);
					p1C.setIsBottom(false);
					p1Index = 2;
				}
			}
			else {
				p1C.setX(p1C.getX() - 10.0f);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				p1C.setX(p1C.getX() + 20.0f);
				if (p1C.getIsBottom() && !p1C.getIsJumping()) {
					p1C.setIsDiving(true);
					p1C.setIsBottom(false);
					p1Index = 1;
				}
			}
			else {
				p1C.setX(p1C.getX() + 10.0f);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			if (p1C.getIsBottom() && !p1C.getIsJumping()) {
				p1C.setIsJumping(true);
				p1C.setIsBottom(false);
			}
		}
		if (p1C.getIsBottom() && !over) {
			p1Index = 0;
		}
		if (p1C.getIsJumping() || p1C.getIsDiving()) {
			p1C.setY(p1C.getY() - gravity);
		}
		else {
			p1C.setY(p1C.getY() + gravity);
		}
		if (p1C.getY() >= Y_BOTTOM) {
			p1C.setY(Y_BOTTOM);
			p1C.setIsBottom(true);
		}
		if (p1C.getY() <= Y_BOTTOM - 250) {
			p1C.setIsJumping(false);
		}
		if (p1C.getY() <= Y_BOTTOM - 100) {
			p1C.setIsDiving(false);
		}
		if (p1C.getX() <= 0) {
			p1C.setX(0);
		}
		if (p1Index == 0) {
			p1[1].setPosition(-1000, 0);
			p1[2].setPosition(-1000, 500);
			if (p1C.getX() + (347 * 0.3f) >= 790) {
				p1C.setX(790 - (347 * 0.3f));
			}
		}
		if (p1Index == 1 || p1Index == 2) {
			p1[0].setPosition(-1000, 0);
			if (p1Index == 1) {
				if (p1C.getX() >= 790) {
					p1C.setX(790);
				}
				if (p1C.getX() - (1267 * 0.17f) <= 0) {
					p1C.setX((1267 * 0.17f));
				}
			}
			if (p1Index == 2) {
				if (p1C.getX() + (1267*0.17f) >= 790) {
					p1C.setX(790-(1267*0.17f));
				}
				if (p1C.getX() <= 0) {
					p1C.setX(0);
				}
			}
		}

		//p2Moving
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Numpad4)) {
			if (Keyboard::isKeyPressed(Keyboard::RShift)) {
				p2C.setX(p2C.getX() - 20.0f);
				if (p2C.getIsBottom() && !p2C.getIsJumping()) {
					p2C.setIsDiving(true);
					p2C.setIsBottom(false);
					p2Index = 2;
				}
			}
			else {
				p2C.setX(p2C.getX() - 10.0f);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Numpad6)) {
			if (Keyboard::isKeyPressed(Keyboard::RShift)) {
				p2C.setX(p2C.getX() + 20.0f);
				if (p2C.getIsBottom() && !p2C.getIsJumping()) {
					p2C.setIsDiving(true);
					p2C.setIsBottom(false);
					p2Index = 1;
				}
			}
			else {
				p2C.setX(p2C.getX() + 10.0f);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Numpad8)) {
			if (p2C.getIsBottom() && !p2C.getIsJumping()) {
				p2C.setIsJumping(true);
				p2C.setIsBottom(false);
			}
		}
		if (p2C.getIsBottom() && !over) {
			p2Index = 0;
		}
		if (p2C.getIsJumping() || p2C.getIsDiving()) {
			p2C.setY(p2C.getY() - gravity);
		}
		else {
			p2C.setY(p2C.getY() + gravity);
		}
		if (p2C.getY() >= Y_BOTTOM)  
		{
			p2C.setY(Y_BOTTOM);
			p2C.setIsBottom(true);
		}
		if (p2C.getY() <= Y_BOTTOM - 250) 
		{
			p2C.setIsJumping(false);
		}
		if (p2C.getY() <= Y_BOTTOM - 100) {
			p2C.setIsDiving(false);
		}
		if (p2C.getX() >= 1600) {
			p2C.setX(1600);
		}
		if (p2Index == 0) {
			p2[1].setPosition(-2000, 0);
			p2[2].setPosition(-2000, 500);
			if (p2C.getX() - (347 * 0.3f) <= 810) {
				p2C.setX(810 + (347 * 0.3f));
			}
		}
		if (p2Index == 1 || p2Index == 2) {
			p2[0].setPosition(-2000, 0);
			if (p2Index == 1) {
				if (p2C.getX() >= WIDTH) {
					p2C.setX(WIDTH);
				}
				if (p2C.getX() - (1267 * 0.17f) <= 810) {
					p2C.setX(810+(1267 * 0.17f));
				}
			}
			if (p2Index == 2) {
				if (p2C.getX() + (1267 * 0.17f) >= WIDTH) {
					p2C.setX(810 + (1267 * 0.17f));
				}
				if (p2C.getX() <= 810) {
					p2C.setX(810);
				}
			}
		}

		//ball Moving
		ballC.setX(ballC.getX() + dx);
		ballC.setY(ballC.getY() + dy);
		if (FloatRect(ballC.getX() - (96 * 0.7f), ballC.getY() - (96 * 0.7f), 96 * 0.7f * 2, 96 * 0.7f * 2).intersects(wall.getGlobalBounds())) {
			if (ballC.getY() <= 490) {
				dy = -dy;
				ballC.setY(520 - (96 * 0.7f));
			}
			else {
				dx = -dx;
			}
		}
		if (FloatRect(ballC.getX() - (96 * 0.7f), ballC.getY() - (96 * 0.7f), 96 * 0.7f * 2, 96 * 0.7f * 2).intersects(p1[0].getGlobalBounds())) {
			bounce.play();
			if (ballC.getY() <= 630) {
				if (Keyboard::isKeyPressed(Keyboard::D)) {
					dx = abs(dx);
					dx = dx + 10;
				}
				if (Keyboard::isKeyPressed(Keyboard::A)) {
					dx = -abs(dx);
					dx = dx - 10;
				}
				if (Keyboard::isKeyPressed(Keyboard::W)) {
					dy *= 1.5f;
				}
				else {
					dy = gravity;

				}
				dy = -dy;

				ballC.setY(p1C.getY() - (666 * 0.3f) - (96 * 0.7f));
			}
			else {
				if (Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::Space)) {
					dx *= 1.7f;
				}
				else if (Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::Space)) {
					dx *= 1.7f;
				}
				else {
					dx = X_Vel;
				}
				dx = -dx;
			}
		}
		if (FloatRect(ballC.getX() - (96 * 0.7f), ballC.getY() - (96 * 0.7f), 96 * 0.7f * 2, 96 * 0.7f * 2).intersects(p1[1].getGlobalBounds())) {
			bounce.play();
			if (ballC.getY() <= (Y_BOTTOM - (632 * 0.18f))) {
				dy = -gravity;
				if (dx < 0) {
					dx = -10;
				}
				else {
					dx = 10;
				}
			}
		}
		if (FloatRect(ballC.getX() - (96 * 0.7f), ballC.getY() - (96 * 0.7f), 96 * 0.7f * 2, 96 * 0.7f * 2).intersects(p1[2].getGlobalBounds())) {
			bounce.play();
			if (ballC.getY() <= (Y_BOTTOM - (632 * 0.18f))) {
				dy = -gravity;
				if (dx < 0) {
					dx = -10;
				}
				else {
					dx = 10;
				}
			}
		}
		if (FloatRect(ballC.getX() - (96 * 0.7f), ballC.getY() - (96 * 0.7f), 96 * 0.7f * 2, 96 * 0.7f * 2).intersects(p2[0].getGlobalBounds())) {
			bounce.play();
			if (ballC.getY() <= 630) {
				if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Numpad4)) {
					dx = -abs(dx);
					dx = dx - 10;
				}
				if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Numpad6)) {
					dx = abs(dx);
					dx = dx + 10;
				}
				if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Numpad8)) {
					dy *= 1.5f;
				}
				else {
					dy = gravity;
				}
				dy = -dy;
				ballC.setY(p2C.getY() - (666 * 0.3f) - (96 * 0.7f));
			}
			else {
				if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Numpad4)) && !Keyboard::isKeyPressed(Keyboard::RShift)) {
					dx *= 1.7f;
				}
				else if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Numpad4)) && !Keyboard::isKeyPressed(Keyboard::RShift)) {
					dx *= 1.7f;
				}
				else {
					dx = X_Vel;
				}
				dx = -dx;
			}
		}
		if (FloatRect(ballC.getX() - (96 * 0.7f), ballC.getY() - (96 * 0.7f), 96 * 0.7f * 2, 96 * 0.7f * 2).intersects(p2[1].getGlobalBounds())) {
			bounce.play();
			if (ballC.getY() <= (Y_BOTTOM - (632 * 0.18f))) {
				dy = -gravity;
				if (dx < 0) {
					dx = -10;
				}
				else {
					dx = 10;
				}
			}
		}
		if (FloatRect(ballC.getX() - (96 * 0.7f), ballC.getY() - (96 * 0.7f), 96 * 0.7f * 2, 96 * 0.7f * 2).intersects(p2[2].getGlobalBounds())) {
			bounce.play();
			if (ballC.getY() <= (Y_BOTTOM - (632 * 0.18f))) {
				dy = -gravity;
				if (dx < 0) {
					dx = -10;
				}
				else {
					dx = 10;
				}
			}
		}
		if (ballC.getX() + (96 * 0.7) >= WIDTH || ballC.getX() - (96 * 0.7) <= 0) {
			dx = -dx;
		}
		if (ballC.getY() - (96 * 0.7) <= 0) {
			dy = -dy;
		}
		if (ballC.getY() + (96 * 0.7) >= Y_BOTTOM)
		{
			scoreM.play();
			ballC.setY(Y_BOTTOM);
			ballC.setY(150);
			p1C.setX(200);
			p1C.setY(Y_BOTTOM);
			p2C.setX(1400);
			p2C.setY(Y_BOTTOM);
			if (ballC.getX() <= 790) {
				ballC.setX(200 + (347 * 0.3f));
				p2C.setScore(p2C.getScore() + 1);
			}
			else if (ballC.getX() >= 810) {
				ballC.setX(1400 - (347 * 0.3f));
				p1C.setScore(p1C.getScore() + 1);
			}
			Sleep(1000);
			dx = 0;
			dy = gravity;
		}
		if (abs(dx) >= 30) {
			if (dx < 0) {
				dx = -30;
			}
			else {
				dx = 30;
			}
		}
		if (abs(dy) >= 30) {
			if (dy < 0) {
				dy = -30;
			}
			else {
				dy = 30;
			}
		}


		if (p1C.getScore() == 21) {
			over = true;
			p1Index = 3;
			endText.setString("Player 1 Win!!");
			window.draw(endText);
			crowd.play();
			while (crowd.getStatus() != Sound::Stopped) {
			}
		}
		if (p2C.getScore() == 21) {
			over = true;
			p2Index = 3;
			endText.setString("Player 2 Win!!");
			window.draw(endText);
		}
		if (!over) {
			ball.setPosition(ballC.getX(), ballC.getY());
			p1[p1Index].setPosition(p1C.getX(), p1C.getY());
			p2[p2Index].setPosition(p2C.getX(), p2C.getY());
		}
		else {
			dx = 0;
			dy = 0;
		}
		window.display();
	}
	return 0;
}