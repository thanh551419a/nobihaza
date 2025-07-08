#ifndef __MOVEMENT_CONTROL_H__
#define __MOVEMENT_CONTROL_H__

#include "cocos2d.h"
#include<vector>
#include<iostream>
using namespace std;
using namespace cocos2d;
class movementCtrl: public cocos2d::Node
{
	private:
		set<cocos2d::EventKeyboard::KeyCode> heldKeyAWDS; // Set to track held keys, save key codes of pressed keys
		cocos2d::Vec2 playerPos; // Position of the player in the game scene
		// Add other private members as needed for your game logic
	public:
		static movementCtrl* getInstance(); // Singleton instance
		
		virtual bool init();
		void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
		void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // Handle key release events if needed
		void updateMovement(float dt); // Update player movement based on held keys
		virtual void update(float dt) override;// Update logic can be added here if needed
};

#endif // __MOVEMENT_CONTROL_H__
