#include "movementControl.h"
#include "globalVal.h"
#include "GameScene.h"

USING_NS_CC;

bool movementCtrl::init() {
    if (!Node::init())
        return false;

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(movementCtrl::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(movementCtrl::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    this->scheduleUpdate();

    return true;
}

movementCtrl* movementCtrl::getInstance()
{
    static movementCtrl instance;
    return &instance;
}

void movementCtrl::setBodySprite(Sprite* sprite)
{
    _bodySprite = sprite;
}

void movementCtrl::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    heldKeyAWDS.insert(keyCode);
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        heldKeyAWDS.erase(keyCode);
        Director::getInstance()->getRunningScene()->pause(); // Hoặc gọi pause scene nào đó
    }
}

void movementCtrl::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    heldKeyAWDS.erase(keyCode);
}

void movementCtrl::update(float dt)
{
    updateMovement(dt);
}

void movementCtrl::updateMovement(float dt)
{
    if (!_bodySprite) return;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    float step = 5.0f;

    auto gV = globalVal::getInstance();
    auto tileSize = gV->getTileSize();
    auto sizeMap = gV->getSizeMap();

    int temp1 = visibleSize.height / 100;
    auto posX = _bodySprite->getPositionX();
    auto posY = _bodySprite->getPositionY();

    
    if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_W) &&
        gV->getPlayerPosY() + step <= sizeMap * tileSize){
        gV->setPlayerPosY(gV->getPlayerPosY() + step);
        if (gV->getPlayerPosY() + step >= tileSize * (sizeMap - temp1)) {
            _bodySprite->setPositionY(posY + step);
        }
		CCLOG("Player Position Y: %f", gV->getPlayerPosY());
    }

    if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_S) &&
        gV->getPlayerPosY() - step >= 0) {
        gV->setPlayerPosY(gV->getPlayerPosY() - step);
        if (gV->getPlayerPosY() - step <= tileSize * temp1) {
            _bodySprite->setPositionY(posY - step);
        }

    }

  /*  if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_A)) {
        if (gV->getPlayerPosX() - step >= tileSize * temp1) {
            gV->setPlayerPosX(gV->getPlayerPosX() - step);
        }
    }

    if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_D)) {
        if (gV->getPlayerPosX() + step <= tileSize * (sizeMap - temp1)) {
            gV->setPlayerPosX(gV->getPlayerPosX() + step);
        }
    }*/
}
