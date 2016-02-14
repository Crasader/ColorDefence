#include "AppDelegate.h"
#include "SceneMenu.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::create("ColorDefence");
		director->setOpenGLView(glview);
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//�Ժ����ֻ�����ʾ�ֱ���Ϊ���Ŀ��1280x720
	glview->setFrameSize(720,1280);
	glview->setFrameZoomFactor(0.5);

#endif


	glview->setDesignResolutionSize(720,1280, ResolutionPolicy::SHOW_ALL);

	//ͼ����Դ·��
	//��ȡ��ǰ�豸��Ļ�ߴ�
	Size frameSize = glview->getFrameSize();
	std::vector<std::string> searchPath;
	//�����Ļ�ߴ��>smallResource�زĳߴ��
	//if (frameSize.width > 1080 )
	if (frameSize.width > 108000 )
	{
		//ʹ�ô�ߴ���ز�
		searchPath.push_back("xxxhdpi/");
		director->setContentScaleFactor(2.0);
	}
	else
	{
		//ʹ��С�ߴ���ز�
		searchPath.push_back("xhdpi/");
		director->setContentScaleFactor(1.0);
	}

	// �����ز�·��Ŀ¼
	FileUtils::getInstance()->setSearchPaths(searchPath);


	//��windows������ʱ��0.5������ʾ ��Ԥ����������


	// turn on display FPS
	//director->setDisplayStats(true);
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	auto scene = SceneMenu::createScene();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
