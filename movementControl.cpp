#include "globalVal.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "movementControl.h"
#include "loadMap.h";
bool movementCtrl::init() {
    if (!Node::init())
        return false;

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(movementCtrl::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(movementCtrl::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->scheduleUpdate(); // Schedule update method to be called every frame

    return true;
}
movementCtrl* movementCtrl::getInstance()
{
    static movementCtrl instance; // Sử dụng static để đảm bảo chỉ có một instance duy nhất
    return &instance;
}
void movementCtrl::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    heldKeyAWDS.insert(keyCode);
    // player want to pause the game
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {   // only load key one time press 
        heldKeyAWDS.erase(keyCode);
        GameScene::getInstance()->GoToPauseScene(nullptr);
        return;
    }
}
void movementCtrl::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    heldKeyAWDS.erase(keyCode);
}
void movementCtrl::update(float dt)
{
    updateMovement(dt); // Update player movement based on held keys
}
void movementCtrl::updateMovement(float dt)// hold keys W, A, S, D to move player
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
    float step = 5.0f; // step size for movement
    auto gV = globalVal::getInstance();
	auto tileSize = gV->getTileSize();
	auto sizeMap = gV->getSizeMap();
	auto gS = GameScene::getInstance();
	auto bodySprite = gS->getChildByName("bodySprite");// tao bien bodySprite de truy cap den sprite cua player
    int temp1 = visibleSize.height / 100;

	/*auto posX = bodySprite->getPositionX();
    auto posY = bodySprite->getPositionY();*/
    
    if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_W)) // move forward
    {
        if (gV->getPlayerPosY() + step <= tileSize * (sizeMap - temp1)  ) {
            gV->setPlayerPosY(gV->getPlayerPosY() + step);
        }
        /*else if(gv->getPlayerPosY() + step <= tileSize * (sizeMap)) {
            gv->setPlayerPosY(); 
		}*/
    }
    if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_S)) // move backward
    {
        if (gV->getPlayerPosY() - step >= tileSize * temp1 ) { // min 0
            gV->setPlayerPosY(gV->getPlayerPosY() - step);
		}
    }
    if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_A)) // move left
    {
        if (gV->getPlayerPosX() - step >= tileSize * temp1) {// min 0
            gV->setPlayerPosX(gV->getPlayerPosX() - step);
        }
    }
    if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_D)) // move right
    {
        if (gV->getPlayerPosX() + step <= tileSize * (sizeMap -temp1)) {
            gV->setPlayerPosX(gV->getPlayerPosX() + step);
        }
    }
}
// End of movementControl.cpp 
