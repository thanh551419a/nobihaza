#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    //'scene' is an autorelease object
    auto scene = Scene::create();

    //'layer' is an autorelease object
    auto layer = MainMenu::create();

    //add layer as a child to scene
    scene->addChild(layer);

    //return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// build wallpaper on screen
    backGroundMenu = Sprite::create("PHOTO/Background/backGroundMenu.jpg");
    backGroundMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    backGroundMenu->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(backGroundMenu);

	// build "Play" button
    auto PlayButton = MenuItemImage::create("PHOTO/Menu/Play_Button.png",
                                     "PHOTO/Menu/Play_Button.png",
                       CC_CALLBACK_1(MainMenu::GoToGameScene,this));
    auto menu = Menu::create(PlayButton, NULL);
    this->addChild(menu);

    // catch key "enter" pressed event
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MainMenu::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}
void MainMenu::GoToGameScene(cocos2d::Ref* pSender)
{
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(scene);
}
void MainMenu::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
    {
        GoToGameScene(nullptr); // Call the function to go to the game scene
    }
}