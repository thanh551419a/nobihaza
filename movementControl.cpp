#include "globalVal.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "movementControl.h"
#include "loadMap.h"

bool movementCtrl::init() {
    if (!Node::init())
        return false;

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(movementCtrl::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(movementCtrl::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    this->scheduleUpdate(); // Gọi update mỗi frame

    return true;
}

movementCtrl* movementCtrl::getInstance() {
    static movementCtrl instance;
    return &instance;
}

void movementCtrl::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    heldKeyAWDS.insert(keyCode);

    // Nếu người chơi nhấn ESC → pause game
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
        heldKeyAWDS.erase(keyCode);
        GameScene::getInstance()->GoToPauseScene(nullptr);
    }
}

void movementCtrl::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    heldKeyAWDS.erase(keyCode);
}

void movementCtrl::update(float dt) {
    updateMovement(dt);
}

void movementCtrl::updateMovement(float dt) {
    float step = 2.0f;
    auto gV = globalVal::getInstance();
    auto tileSize = gV->getTileSize();
    auto sizeMap = gV->getSizeMap();
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    float maxCoord = tileSize * sizeMap;
    float minCoord = 0;

    float playerX = gV->getPlayerPosX();
    float playerY = gV->getPlayerPosY();

    Vec2 newPos = Vec2(playerX, playerY);

    // Tính hướng di chuyển
    if (heldKeyAWDS.count(cocos2d::EventKeyboard::KeyCode::KEY_W) && playerY + step <= maxCoord) {
        newPos.y += step;
    }
    if (heldKeyAWDS.count(cocos2d::EventKeyboard::KeyCode::KEY_S) && playerY - step >= minCoord) {
        newPos.y -= step;
    }
    if (heldKeyAWDS.count(cocos2d::EventKeyboard::KeyCode::KEY_A) && playerX - step >= minCoord + 50) {
        newPos.x -= step;
    }
    if (heldKeyAWDS.count(cocos2d::EventKeyboard::KeyCode::KEY_D) && playerX + step < (sizeMap - 1) * tileSize) {
        newPos.x += step;
    }

    // Cập nhật lại playerPos trong global
    gV->setPlayerPos(Vec2( newPos.x, newPos.y));

    // Tính camera zone
    float tempY = visibleSize.height / 2;
    float tempX = visibleSize.width / 2;

    // Nếu người chơi còn trong vùng trung tâm → camera follow → sprite đứng im
    // Nếu ra khỏi vùng → sprite di chuyển, camera đứng
    Vec2 spritePos = _bodySprite->getPosition();

    if (newPos.y < tileSize * tempY / tileSize || newPos.y > tileSize * (sizeMap - tempY / tileSize)) {
        spritePos.y += (newPos.y - playerY); // Dịch sprite nếu camera không follow nữa
    }

    if (newPos.x < tileSize * tempX / tileSize || newPos.x > tileSize * (sizeMap - tempX / tileSize)) {
        spritePos.x += (newPos.x - playerX); // Dịch sprite nếu camera không follow nữa
    }

    _bodySprite->setPosition(spritePos);

    CCLOG("Player Pos: (%f, %f)", newPos.x, newPos.y);
    CCLOG("Body Sprite Pos: (%f, %f)", spritePos.x, spritePos.y);
}

void movementCtrl::setBodySprite(cocos2d::Sprite* sprite) {
    _bodySprite = sprite;
}
