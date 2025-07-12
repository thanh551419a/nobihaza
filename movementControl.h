#ifndef __MOVEMENT_CONTROL_H__
#define __MOVEMENT_CONTROL_H__

#include "cocos2d.h"
#include <set>

class movementCtrl : public cocos2d::Node
{
private:
    std::set<cocos2d::EventKeyboard::KeyCode> heldKeyAWDS;
    cocos2d::Sprite* _bodySprite = nullptr;

public:
    static movementCtrl* getInstance();

    virtual bool init();
    virtual void update(float dt) override;

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void updateMovement(float dt);

    void setBodySprite(cocos2d::Sprite* sprite);  // Thêm hàm setter
};

#endif // __MOVEMENT_CONTROL_H__
