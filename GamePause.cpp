#include "MainMenuScene.h"
#include "GameScene.h"
#include "GamePause.h"
USING_NS_CC;

Scene* GamePause::createScene()
{
    //'scene' is an autorelease object
    auto scene = Scene::create();

    //'layer' is an autorelease object
    auto layer = GamePause::create();

    //add layer as a child to scene
    scene->addChild(layer);

    //return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePause::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // build map on screen
    backGroundScene = Sprite::create("PHOTO/Background/backGround.jpg");
    backGroundScene->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    backGroundScene->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(backGroundScene);
	// add menu items
	auto menuItemResume = MenuItemImage::create(// item for resume
        "PHOTO/Menu/Resume_Button.png",
        "PHOTO/Menu/Resume_Button.png",
		CC_CALLBACK_1(GamePause::Resume, this));

	auto menuItemRetry = MenuItemImage::create(// item for retry
        "PHOTO/Menu/Retry_Button.png",
        "PHOTO/Menu/Retry_Button.png",
		CC_CALLBACK_1(GamePause::Retry, this));

    auto menuItemMainMenu = MenuItemImage::create(//item for main menu
        "PHOTO/Menu/Main_Menu_Button.png",
		"PHOTO/Menu/Main_Menu_Button.png",
        CC_CALLBACK_1(GamePause::GoToMainMenuScene, this));
	
	auto menu = Menu::create(menuItemResume, menuItemMainMenu, menuItemRetry, nullptr);
    menu->setPosition(Vec2::ZERO); // set position of menu to zero
    this->addChild(menu);
    
	// set position for menu items
    menuItemResume->setPosition(Vec2(visibleSize.width / 2, visibleSize.height  * 2 / 3));
	menuItemRetry->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 ));
	menuItemMainMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));

	//set boundering for menu items
	boundering = Sprite::create("PHOTO/Menu/boundering.png");
	boundering->setPosition(menuItemResume->getPosition());
	this->addChild(boundering);

	//save positions of menu items
	menuItem.push_back(menuItemResume->getPosition());
	menuItem.push_back(menuItemRetry->getPosition());
	menuItem.push_back(menuItemMainMenu->getPosition());

	// catch key pressed event
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GamePause::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    return true;
}
void GamePause::Resume(cocos2d::Ref* pSender)
{
    Director::getInstance()->popScene();
}
void GamePause::Retry(cocos2d::Ref* pSender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}
void GamePause::GoToMainMenuScene(cocos2d::Ref* pSender)
{
    auto scene = MainMenu::createScene();
    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}

void GamePause::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    int n = menuItem.size(); // number of menu items
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) // if up arrow is pressed
    {
        // set selected item to last item
        selectedItem = (selectedItem - 1 + n) % n;
    }

    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) // if right arrow is pressed
    {
        // set selected item to first item
        selectedItem = (selectedItem + 1) % n;   
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
    {
        if (selectedItem == 0)
            Resume(nullptr);
        else if (selectedItem == 1)
            Retry(nullptr);
        else if (selectedItem == 2)
            GoToMainMenuScene(nullptr);
    }
    // set position of boundering to selected item
    boundering->setPosition(menuItem[selectedItem]);
}
