#pragma once

#include "ofMain.h"
#include <entt/entt.hpp>

//Components
struct color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	color(unsigned char r, unsigned char g, unsigned char b) :red(r), green(g), blue(b){};
};

struct ninePatch
{
	float p1;
	float p2;
};

struct Position {
	float x;
	float y;
};

struct Name
{
	Name(std::string str)
	{
		name = str;
		show = true;
	}
	std::string name;
	bool show;
};

struct Velocity {
	float dx;
	float dy;
};

//systems

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		//ECS enTT
		entt::DefaultRegistry registry;
		std::uint64_t dt;

		void update(entt::DefaultRegistry &registry) {
			auto view = registry.view<Position, Velocity>();

			for (auto entity : view) {
				auto &velocity = view.get<Velocity>(entity);
				auto &position = view.get<Position>(entity);
				velocity.dx = 0.;
				velocity.dy = 0.;
			}
		}

		void update(std::uint64_t dt, entt::DefaultRegistry &registry) {
			registry.view<Position, Velocity>().each([dt](auto entity, auto &position, auto &velocity) {
				position.x += velocity.dx * dt;
				position.y += velocity.dy * dt;
			});
		}
};
