#include "AppDelegate.h"
#include "select_scene/choice_scene.h"
#include "game_scene/game_scene.h"
#include "config.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Two Towers");
        glview->setFrameSize(ScreenResolution.width, ScreenResolution.height);
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(ScreenResolution.width, ScreenResolution.height, kResolutionShowAll);
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
    auto scene = ChoiceScene::createScene();
    director->runWithScene(scene);
    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
