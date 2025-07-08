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
    Vec2 temp = Vec2(13*50 , 10*50);
	globalVal::getInstance()->setPlayerPos(temp); // Initialize player position
    Point origin = Director::getInstance()->getVisibleOrigin();

	// goi movementCtrl::getInstance() ?? l?y instance c?a movementCtrl
    auto ctrl = movementCtrl::getInstance();
    if (!ctrl->getParent()) {
        ctrl->init(); // g?i init 1 l?n n?u ch?a có parent
        this->addChild(ctrl); // r?t quan tr?ng: ph?i add vào cây scene
    }


    // build map on screen
    auto map = LoadMap::createFromFile("PHOTO/Map.txt");
    this->addChild(map);


    // build body mc
    bodySprite = Sprite::create("PHOTO/player/player-base-01.png");
    bodySprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2);
    bodySprite->setScale(0.1); // set kich co nhan vat - thu nho con 10%
	bodySprite->setName("bodySprite"); // Set name for easy access later
    bodySprite->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(bodySprite);
	auto bodySize = bodySprite->getContentSize();

    //build left arm 
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
    pauseButton->setAnchorPoint(Vec2(0, 0)); // đặt gốc ở góc trái dưới
    pauseButton->setPosition(10 + 175,10); // lúc này là sát góc trái dưới
	auto menu = Menu::create(pauseButton, NULL);
    pauseButton->setScale(0.1);
	menu->setPosition(Vec2::ZERO); // Set menu position to (0,0)
	this->addChild(menu);

 //pauseButton->setVisible(true);
    //pauseButton->setAnchorPoint(Vec2(0, 0));
    //pauseButton->setPosition(10, 10);
    //pauseButton->setScale(0.1);
    //pauseButton->setName("PauseButton");

    //// debug: bật khung giới hạn
    //pauseButton->setCascadeOpacityEnabled(true);
    //pauseButton->setOpacity(200); // semi-transparent để dễ thấy
   

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
GameScene* GameScene::getInstance()
{
	static GameScene instance;
	return &instance;
}
void GameScene::update(float dt)
{
	movementCtrl::getInstance()->updateMovement(dt); // Update player movement based on held keys
	CCLOG("Player Position: (%f, %f)", globalVal::getInstance()->getPlayerPosX(), globalVal::getInstance()->getPlayerPosY());
}