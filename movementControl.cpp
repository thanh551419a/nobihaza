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
    
    int temp1 = visibleSize.height / 100;// temp 1 la 1 nua man hinh

    /*auto posX = bodySprite->getPositionX();
    auto posY = bodySprite->getPositionY();*/
    // khi nhan vat di chuyen , tinh toan truoc cac huong cua nhan vat 
   // sau do moi cap nhat vi tri cua nhan vat
    /*
        diThang = -1: di thang len
        sangNgang = -1: di sang phai
        gV->setPlayerPos(posX + diThang * step, posY + diNgang * step);
    */
	//CCLOG("Player Position: (%f, %d)", gV->getPlayerPosX() + step, );
    if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_W) && gV->getPlayerPosY() + step <= tileSize * sizeMap) { // nhan vat không vượt quá kích thước bản đồ) // move forward
        //CCLOG("djt me may");
        //CCLOG("Player Position before: (%f, %f)", gV->getPlayerPosX(), gV->getPlayerPosY());
        gV->setPlayerPosY(gV->getPlayerPosY() + step);// cap nhat lai vi tri cua nhan vat trong globalVal
        //CCLOG("Player Position after: (%f, %f)", gV->getPlayerPosX(), gV->getPlayerPosY());
        //CCLOG("%d", tileSize * (sizeMap - temp1));
        if (gV->getPlayerPosY() > tileSize * (sizeMap - temp1)) { // di vao phan nhan vat di chuyen map dung im
            _bodySprite->setPositionY(_bodySprite->getPositionY() + step);
        }
        if (_bodySprite->getPositionY() < tileSize * temp1) { // neu vi tri nhan vat di vao vung nhan vat di chuyen map dung im
            _bodySprite->setPositionY(_bodySprite->getPositionY() + step);
        }
    }

    if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_S) && gV->getPlayerPosY() - step >= 0) // move backward
    {
        gV->setPlayerPosY(gV->getPlayerPosY() - step);
        if (gV->getPlayerPosY() < tileSize * temp1) { // neu vi tri nhan vat di vao vung nhan vat di chuyen map dung im
            _bodySprite->setPositionY(_bodySprite->getPositionY() - step);
        }
        if (_bodySprite->getPositionY() > tileSize * temp1) { // di vao phan nhan vat di chuyen map dung im
            _bodySprite->setPositionY(_bodySprite->getPositionY() - step);
        }
    }

    if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_A) && gV->getPlayerPosX() - step >= 0) // move left
    {
		gV->setPlayerPosX(gV->getPlayerPosX() - step);
        if (gV->getPlayerPosX() < tileSize * temp1) { // neu vi tri nhan vat di vao vung nhan vat di chuyen map dung im
            _bodySprite->setPositionX(_bodySprite->getPositionX() - step);
        }
        if (_bodySprite->getPositionX() > tileSize * (sizeMap - temp1)) { // di vao phan nhan vat di chuyen map dung im
            _bodySprite->setPositionX(_bodySprite->getPositionX() - step);
		}
    }

    if (heldKeyAWDS.count(EventKeyboard::KeyCode::KEY_D) && gV->getPlayerPosX() + step < sizeMap * tileSize) // move right
    {
		gV->setPlayerPosX(gV->getPlayerPosX() + step);
        if (gV->getPlayerPosX() > tileSize * (sizeMap - temp1)) { // neu vi tri nhan vat di vao vung nhan vat di chuyen map dung im
            _bodySprite->setPositionX(_bodySprite->getPositionX() + step);
        }
        if (_bodySprite->getPositionX() < tileSize * temp1) { // di vao phan nhan vat di chuyen map dung im
            _bodySprite->setPositionX(_bodySprite->getPositionX() + step);
        }
    }
	CCLOG("Player Position: (%f, %f)", gV->getPlayerPosX(), gV->getPlayerPosY());
	CCLOG("Body Sprite Position: (%f, %f)", _bodySprite->getPositionX(), _bodySprite->getPositionY());
}
// End of movementControl.cpp 
void movementCtrl::setBodySprite(cocos2d::Sprite* sprite) {
	_bodySprite = sprite; // lay bodySprite tu GameScene
}