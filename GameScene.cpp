#include "GameScene.h"
#include "GamePause.h"
#include "GameOver.h"
#include "loadMap.h"
#include "globalVal.h"
#include "movementControl.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    //'scene' is an autolease object
    auto scene = Scene::create();

    //'layer' is an autorelease object
    auto layer = GameScene::create();

    //add layer as a child to scene
    scene->addChild(layer);

    //return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 temp = Vec2(13 * 50, 13 * 50);
    globalVal::getInstance()->setPlayerPos(temp); // Initialize player position
    Point origin = Director::getInstance()->getVisibleOrigin();

    // goi movementCtrl::getInstance() để lấy instance của movementCtrl
    auto ctrl = movementCtrl::getInstance();
    if (!ctrl->getParent()) {
        ctrl->init();
        this->addChild(ctrl); // rất quan trọng: phải add vào cây scene
    }

    // build map on screen
    auto map = LoadMap::createFromFile("PHOTO/Map.txt");
    this->addChild(map);

    // thêm phần layer 2 bên
    auto layer1 = Sprite::create("PHOTO/Map/adding.png");
    auto layer2 = Sprite::create("PHOTO/Map/adding.png");
    int temp1 = layer1->getContentSize().height - visibleSize.height;
    auto tempSize = layer1->getContentSize().width;

    layer1->setAnchorPoint(Vec2(0, 0));
    layer2->setAnchorPoint(Vec2(0, 0));
    layer1->setPosition((visibleSize.width - 3 * visibleSize.height) / 2 - temp1, 0);
    CCLOG("Layer1 position: %f %f", layer1->getPositionX(), layer1->getPositionY());
    layer2->setPosition((visibleSize.width + visibleSize.height) / 2 + temp1, 0);
    CCLOG("visibleSize: %f %f", visibleSize.width, visibleSize.height);
    this->addChild(layer1, 9999);
    this->addChild(layer2, 9999);

    // build body mc
    bodySprite = Sprite::create("PHOTO/player/player-base-01.png");
    bodySprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2);
    bodySprite->setScale(0.1);
    bodySprite->setName("bodySprite");
    bodySprite->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(bodySprite);
    auto bodySize = bodySprite->getContentSize();

    // Gửi bodySprite vào movementCtrl để sử dụng
    ctrl->setBodySprite(bodySprite);

    // build left arm 
    leftArmSprite = Sprite::create("PHOTO/player/player-hands-02.png");
    auto leftArmSize = leftArmSprite->getContentSize();
    leftArmSprite->setPosition(
        bodySize.width / 2 - leftArmSize.width / 2 - 50,
        bodySize.height / 2 + leftArmSize.height / 2 + 50
    );
    leftArmSprite->setAnchorPoint(Vec2(0.5, 0.5));
    bodySprite->addChild(leftArmSprite);

    // build right arm
    rightArmSprite = Sprite::create("PHOTO/player/player-hands-02.png");
    auto rightArmSize = rightArmSprite->getContentSize();
    rightArmSprite->setPosition(
        bodySize.width / 2 + rightArmSize.width / 2 + 50,
        bodySize.height / 2 + rightArmSize.height / 2 + 50);
    bodySprite->addChild(rightArmSprite);

    // build pause button
    auto pauseButton = MenuItemImage::create(
        "PHOTO/Menu/Pause_Button.png",
        "PHOTO/Menu/Pause_Button.png",
        CC_CALLBACK_1(GameScene::GoToPauseScene, this));
    pauseButton->setAnchorPoint(Vec2(0, 0));
    pauseButton->setPosition(10 + 175, 10);
    pauseButton->setScale(0.1);
    auto menu = Menu::create(pauseButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    CCLOG("%f %f", origin.x, origin.y);

    this->scheduleUpdate(); // Schedule the update method to be called every frame

    return true;
}

void GameScene::GoToPauseScene(cocos2d::Ref* pSender)
{
    auto scene = GamePause::createScene();
    Director::getInstance()->pushScene(scene);
}

void GameScene::GoToGameOverScene(cocos2d::Ref* pSender)
{
    auto scene = GameOver::createScene();
    Director::getInstance()->replaceScene(scene);
}

// ✅ XOÁ static getInstance() vì không đúng logic scene hiện tại
// Nếu bạn vẫn cần quản lý global GameScene, hãy dùng biến toàn cục hoặc Director::getRunningScene()

void GameScene::update(float dt)
{
    movementCtrl::getInstance()->updateMovement(dt);
    CCLOG("Player Position: (%f, %f)", globalVal::getInstance()->getPlayerPosX(), globalVal::getInstance()->getPlayerPosY());
}

cocos2d::Sprite* GameScene::getBodySprite() const
{
    return bodySprite;
}
