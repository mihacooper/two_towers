#include "app.h"
#include "select_scene/choice_scene.h"
#include "game_scene/game_scene.h"
#include "config.h"

USING_NS_CC;

App::App() {

}

App::~App()
{
}

void App::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool App::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Two Towers");
        glview->setFrameSize(ScreenResolution.width, ScreenResolution.height);
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(ScreenResolution.width, ScreenResolution.height, ResolutionPolicy::SHOW_ALL);
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
    auto scene = ChoiceScene::createScene();
    director->runWithScene(scene);
    return true;
}

void App::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void App::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
