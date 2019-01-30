#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


Vector2f ballVelocity;
bool server = false;

Font font;
Text text;
int player1Score = 0;
int player2Score = 0;


bool changeBallDir = true;
float randNumx;
bool aiEnabled = false;

const Keyboard::Key controls[5] = {
	Keyboard::A,   // Player1 UP
	Keyboard::Z,   // Player1 Down
	Keyboard::Up,  // Player2 UP
	Keyboard::Down, // Player2 Down
	Keyboard::G,   // Enable/Disable AI
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];




void SetPaddleandBallPos() {
	// reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth / 2 + 377, gameHeight / 2);
	// reset Ball Position
	ball.setPosition(gameWidth / 2, gameHeight / 2);

	//ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

	randNumx = rand() % (190 - 170 + 1) + 170;

	if (changeBallDir) {
		ballVelocity = { randNumx ,60.0f };
	}
	else {
		ballVelocity = { -randNumx ,60.0f };
	}
	
	changeBallDir = !changeBallDir;
}

void Load() {
	// Set size and origin of paddles
	for (auto &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);

	SetPaddleandBallPos();


	// Load font-face from res dir
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	// set the character size to 24 pixels
	text.setCharacterSize(24);
	// Set Initial Score Text
	text.setString(to_string(player1Score) + " : " + to_string(player2Score));
	// Keep Score Text Centered
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);
}
//
void Reset() {

	// Update Score Text
	text.setString(to_string(player1Score) + " : " + to_string(player2Score));
	// Keep Score Text Centered
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);

	SetPaddleandBallPos();
}


void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}





	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	// handle left paddle movement
	float leftDirection = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		leftDirection--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		leftDirection++;
	}
	paddles[0].move(0, leftDirection * paddleSpeed * dt);


	//Enable/Disable AI
	if (Keyboard::isKeyPressed(controls[4])) {
		aiEnabled = !aiEnabled;
	}

	if (!aiEnabled) {
		// handle right paddle movement
		float rightDirection = 0.0f;
		if (Keyboard::isKeyPressed(controls[2])) {
			rightDirection--;
		}
		if (Keyboard::isKeyPressed(controls[3])) {
			rightDirection++;
		}
		paddles[1].move(0, rightDirection * paddleSpeed * dt);
	}
	else {
		paddles[1].move(0, (ball.getPosition().y - paddles[1].getPosition().y) + paddleSpeed * dt);
	}
	




	ball.move(ballVelocity * dt);

	//BALL COLLISIONS
	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight) { //bottom wall
	  // bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) { //top wall
   // top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth) {
		// right wall
		player2Score++;
		Reset();
	}
	else if (bx < 0) {
		// left wall
		player1Score++;
		Reset();
	}
	else if (
		//ball is inline or behind paddle
		bx < paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) {
		// bounce off left paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(10, 0);
	}
	else if (
		//ball is inline or behind paddle
		bx > gameWidth - paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		) {
		// bounce off left paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(-10, 0);
	}



}

//void Update(double dt) {
//	// Update Everything
//}



void Render(RenderWindow &window) {
	// Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
}

//void Render() {
//	// Draw Everything
//}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}



















//
//int main(){
//  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//  sf::CircleShape shape(100.f);
//  shape.setFillColor(sf::Color::Green);
//
//  while (window.isOpen()){
//      sf::Event event;
//      while (window.pollEvent(event)){
//      if (event.type == sf::Event::Closed){
//        window.close();
//      }
//    }
//    window.clear();
//    window.draw(shape);
//    window.display();
//  }
//  return 0;
//}