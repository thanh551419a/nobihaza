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
    Vec2 temp = Vec2(13*50 , 13*50);
	globalVal::getInstance()->init1(); // goi ham init reset lai tat ca
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

    // them phan layer 2 ben
	auto layer1 = Sprite::create("PHOTO/Map/adding.png");
	auto layer2 = Sprite::create("PHOTO/Map/adding.png");
	auto tempSize = layer1->getContentSize().width;// 700 
	//layer1->setPosition(  (visibleSize.width - visibleSize.height*3)/2 ,0);
	layer1->setAnchorPoint(Vec2(0, 0)); // Set anchor point to bottom-left corner
	layer2->setAnchorPoint(Vec2(0, 0)); // Set anchor point to bottom-left corner
	int layer1size = layer1->getContentSize().width; // 700
	layer1->setPosition( (visibleSize.width -  visibleSize.height)/2 - layer1size ,0);
//	CCLOG("Layer1 position: %f %f", layer1->getPositionX(), layer1->getPositionY());
	layer2->setPosition( (visibleSize.width + visibleSize.height) / 2 , 0);
	//CCLOG("visibleSize: %f %f", visibleSize.width, visibleSize.height); 
	this->addChild(layer1,9999);
	this->addChild(layer2,9999);
    // build body mc
    bodySprite = Sprite::create("PHOTO/player/player-base-01.png");
    bodySprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2);
    bodySprite->setScale(0.1); // set kich co nhan vat - thu nho con 10%
	bodySprite->setName("bodySprite"); // Set name for easy access later
    bodySprite->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(bodySprite);
	auto bodySize = bodySprite->getContentSize();
	movementCtrl::getInstance()->setBodySprite(bodySprite); // Set the body sprite in movementCtrl
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
   

  //  CCLOG("%f %f", origin.x, origin.y);

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
    // Cập nhật di chuyển
    movementCtrl::getInstance()->updateMovement(dt);

    // Lấy player position
    auto gV = globalVal::getInstance();
    Vec2 playerPos(gV->getPlayerPosX(), gV->getPlayerPosY());

    // Lấy kích thước màn hình và map
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto mapSizeInPixels = Size(globalVal::getInstance()->getSizeMap() * globalVal::getInstance()->getTileSize(),
        globalVal::getInstance()->getSizeMap() * globalVal::getInstance()->getTileSize());

    // Giới hạn vị trí camera không đi ra khỏi bản đồ
    float cameraX = std::max(visibleSize.width / 2, std::min(playerPos.x, mapSizeInPixels.width - visibleSize.width / 2));
    float cameraY = std::max(visibleSize.height / 2, std::min(playerPos.y, mapSizeInPixels.height - visibleSize.height / 2));

    // Đặt vị trí scene sao cho nhân vật ở giữa (nếu còn trong vùng trung tâm)
    this->setPosition(Vec2(visibleSize.width / 2 - cameraX, visibleSize.height / 2 - cameraY));
}