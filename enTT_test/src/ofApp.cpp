#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	int expectedFrameRate = 60;
	dt = 1000/ expectedFrameRate;
	ofSetFrameRate(expectedFrameRate);
	for (auto i = 0; i < 10; ++i)
	{
		auto entity = registry.create();
		registry.assign<Position>(entity, i * 1.f, i * 1.f);
		if (i % 2 == 0)
		{
			registry.assign<Velocity>(entity, i * .1f, i * .1f);
		}
		registry.assign<Name>(entity, "Entity_" + std::to_string(i));
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());

	//Some test...nonsense

	auto viewPos = registry.view<Position>();
	for (auto entity : viewPos)
	{

		if (registry.has<Velocity>(entity) == false)
		{
			auto &position = viewPos.get(entity);
			position.x = position.x + entity;
			if (registry.has<Name>(entity) == true)
			{
				auto &name = registry.get<Name>(entity);
				if (name.show)
				{
					std::cout << "Entity name: " << name.name << "\n";
					name.show = false;
				}
			}
		}
	}
	auto viewPosVel = registry.view<Position, Velocity>();
	for (auto entity : viewPosVel) {
		// gets only the components that are going to be used ...

		auto &velocity = viewPosVel.get<Velocity>(entity);
		auto &position = viewPosVel.get<Position>(entity);

		position.x = position.x + velocity.dx;
		position.y = position.y + velocity.dy;

		if (position.x > entity * 100 || position.x < 0)
		{
			velocity.dx = -velocity.dx;
		}

		if (position.y > entity * 100 || position.y < 0)
		{
			velocity.dy = -velocity.dy*0.7f;
		}
	}

	registry.view<Position, Velocity>().each([this](auto entity, auto &position, auto &velocity) 
	{
		position.x += velocity.dx * dt;
		position.y += velocity.dy * dt;
	});
	update(dt, registry);
}

//--------------------------------------------------------------
void ofApp::draw(){	
	registry.view<Position>().each([this](auto entity, auto &position)
	{
		ofSetColor(entity * 255 / 16.0f, entity * 255, entity * 255 / 16.0f, 200);
		ofDrawCircle(position.x, position.y, 10);
	});
	ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
