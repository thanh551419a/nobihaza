#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include<vector>
#include<iostream>
using namespace std;
using namespace cocos2d;
class GameScene : public cocos2d::Scene
{
private:

    cocos2d::Sprite* bodySprite;
    cocos2d::Sprite* leftArmSprite;
    cocos2d::Sprite* rightArmSprite;
    cocos2d::Sprite* picturemap;
public:
    // there is no 'id' in cpp so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // method 'init' in cocos2d-x returns bool, instead od returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);


    void GoToPauseScene(Ref* pSender);
    void GoToGameOverScene(Ref* pSender);
    //void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // Handle key release events if needed
    //void onMouseMove(cocos2d::Event* event);// Handle mouse move events if needed

    virtual void update(float dt) override;// Update logic can be added here if needed
    static GameScene* getInstance();
    cocos2d::Sprite* getBodySprite() const;

};

#endif // __GAME_SCENE_H__