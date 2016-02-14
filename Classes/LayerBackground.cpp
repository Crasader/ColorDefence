#include "LayerBackground.h"
#include "MapPointsManager.h"


const float Y_topBarBound = 1230.0f;
const float Y_mainPanelBound = 150.0f;

const int whiteBar_tag = 221;  //注意 占用了221 222 223
const int bottom_bar_tag = 88;

USING_NS_CC;


// on "init" you need to initialize your instance
bool LayerBackground::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* bottom = Sprite::create("background/bottom.png");
	addChild(bottom);
	bottom->setTag(bottom_bar_tag);
	bottom->setPosition(visibleSize.width/2,Y_mainPanelBound/2);


	colorBlocks = Vector<Sprite*>();

	_nodeGrid = NodeGrid::create();
	//_nodeGrid->setPosition(180,0);
	addChild(_nodeGrid);

	for (int i = 0; i< 12 ; i++ )
	{
		for (int j = 0; j< 8 ; j++)
		{


			Sprite* block = Sprite::create("BLANK.png");
			block->setTextureRect(Rect(0,0,((j==0)||(j==7))?180:90,((i==0)||(i==11))?180:90));
			//block->setTextureRect(Rect(0,0,90,90));
			_nodeGrid->addChild(block);
			block->setColor(ccc3(0,0,0));
			block->setPosition(MapPointsManager::getPointByIndex(i*8 + j));
			colorBlocks.pushBack(block);

			
			if (j == 0)
			{
				//第一列
				block->setAnchorPoint(block->getAnchorPoint()+Vec2(0.25,0));
			}
			else if (j == 7)
			{
				//最后一列
				block->setAnchorPoint(block->getAnchorPoint()+Vec2(-0.25,0));

			}
			
			if (i == 0)
			{
				//第一行
				block->setAnchorPoint(block->getAnchorPoint()+Vec2(0,0.25));

			}
			else if (i == 11)
			{
				//最后一行
				block->setAnchorPoint(block->getAnchorPoint()+Vec2(0,-0.25));

			}
			
				
		}


	}


	for (int i = 0;i<3;i++)
	{
		center0fRGB[i] = Node::create();
		addChild(center0fRGB[i]);
		center0fRGB[i]->setPosition(origin.x + visibleSize.width/2 , Y_mainPanelBound + (Y_topBarBound - Y_mainPanelBound)/4 * (i+1));
	}




	em = EnemyManager::getInstance();
	enemiesInBg = Vector<Enemy*>();
	_timer = 0;
	bigLetters =  Vector<BigLetter*>();
	scheduleUpdate();
	


	//监听“游戏结束”的事件
	auto listenerGameOverWin = EventListenerCustom ::create("GAME_OVER_WIN",[&](EventCustom* event){
		gameOverAnimation(true);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerGameOverWin,this);

	auto listenerGameOverLose = EventListenerCustom ::create("GAME_OVER_LOSE",[&](EventCustom* event){
		gameOverAnimation(false);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerGameOverLose,this);




	//监听“释放敌人”的事件
	auto listenerReady = EventListenerCustom ::create("RELEASE_ENEMIES",[&](EventCustom* event){

		auto act1 = FadeOut::create(0.29);
		auto act2 = DelayTime::create(0.02);
		auto act3 = FadeIn::create(0.29);
		(Sprite*)(this->getChildByTag(bottom_bar_tag))->runAction(Sequence::create(act1,act2,act3,nullptr));
	
	
	
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerReady,this);


	//监听 超能力震荡 事件
	//auto listenerSuperPower = EventListenerCustom ::create("SUPER_POWER",[&](EventCustom* event){
	auto listenerSuperPower = EventListenerCustom ::create("SUPER_SHAKE",[&](EventCustom* event){

		
		_nodeGrid->stopAllActions();
		auto act1 = Liquid::create(0.001, Size(8, 12), 0, 0);
		auto act2 = Liquid::create(0.06, Size(8, 12), 1, 15);
		auto act3 = Liquid::create(0.1, Size(8, 12), 1, 10);
		auto act4 = Liquid::create(0.2, Size(8, 12), 1, 7);
		auto act5 = Liquid::create(0.4, Size(8, 12), 1, 5);
		auto act6 = Liquid::create(0.001, Size(8, 12), 0, 0);
		_nodeGrid->runAction(Sequence::create(act1,act2,act3,act4,act5,act6,NULL));
		

// 		auto act1 = WavesTiles3D::create(3, Size(36, 64), 5, 40);
// 		_nodeGrid->runAction(act1);


	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerSuperPower,this);




	return true;
}

void LayerBackground::update( float delta )
{
	

	if (em->enemiesArrive.size()>0)
	{
		Enemy* e = em->enemiesArrive.back();
		em->enemiesArrive.popBack();

		e->retain();
		e->removeFromParent();
		addChild(e,20);
		e->release();

		enemiesInBg.pushBack(e);
		e->setFloating();
	}


	
	for (Enemy* e:enemiesInBg)
	{
		if (e->getNumberOfRunningActions() == 0)
		{

			Size visibleSize = Director::getInstance()->getVisibleSize();
			Vec2 origin = Director::getInstance()->getVisibleOrigin();

			Point pDest = Point(
				origin.x + visibleSize.width * CCRANDOM_0_1() ,
				Y_mainPanelBound + (Y_topBarBound - Y_mainPanelBound) * CCRANDOM_0_1()
				);

			Vec2 dir = pDest - e->getPosition();

			e->setMoveDirection(dir);

		
			e->runAction(MoveTo::create(7.5 + 7 * CCRANDOM_0_1(),pDest));
		}
	}
	
	
	for (int i = 0;i<3;i++)
	{
		if (center0fRGB[i]->getNumberOfRunningActions() == 0)
		{

			Size visibleSize = Director::getInstance()->getVisibleSize();
			Vec2 origin = Director::getInstance()->getVisibleOrigin();

			Point pDest = Point(
				origin.x + visibleSize.width * CCRANDOM_0_1() ,
				Y_mainPanelBound + (Y_topBarBound - Y_mainPanelBound) * CCRANDOM_0_1()
				);

			center0fRGB[i]->runAction(MoveTo::create(2.5 + 2.5 * CCRANDOM_0_1(),pDest));
		}
	}




	for (Sprite* sp: colorBlocks)
	{
		sp->setColor(Color3B(
			105 - sp->getPosition().getDistance(center0fRGB[0]->getPosition())/1300 * 105,
			155 - sp->getPosition().getDistance(center0fRGB[1]->getPosition())/1300 * 155,
			205 - sp->getPosition().getDistance(center0fRGB[2]->getPosition())/1300 * 205
			));
	}


	_timer ++;
	if (_timer>8)
	{
		_timer = 0;

		for (int t = 0 ; t<3 ; t++)
		{
			if (getChildByTag( t + whiteBar_tag)!= nullptr)
			{
				getChildByTag(t + whiteBar_tag)->setPositionY(getChildByTag(t + whiteBar_tag)->getPositionY()-90);
				if (getChildByTag(t + whiteBar_tag)->getPositionY() < MapPointsManager::getPointByIndex(0).y)
				{
					getChildByTag(t + whiteBar_tag)->setPositionY( MapPointsManager::getPointByIndex(95).y);
				}
			}
		}


		if (!bigLetters.empty())
		{
			for (BigLetter* bl:bigLetters)
			{
				bl->setPositionX(bl->getPositionX()-90);
				if (bl->getPositionX()<-2000)
				{
					bl->setPositionX(bl->getPositionX()+16*6*90);
				}
			}
		}


	}



	

}

void LayerBackground::gameOverAnimation( bool win )
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	if (win)
	{

		BigLetter::_letter _bl[16]= {
			BigLetter::C,
			BigLetter::O,
			BigLetter::N,
			BigLetter::G,
			BigLetter::R,
			BigLetter::A,
			BigLetter::T,
			BigLetter::U,
			BigLetter::L,
			BigLetter::A,
			BigLetter::T,
			BigLetter::I,
			BigLetter::O,
			BigLetter::N,
			BigLetter::S,
			BigLetter::SYMBOL,
		};

		for (int i = 0 ; i<16 ; i++)
		{
			BigLetter* bl = BigLetter::create();
			bl->setLetter(_bl[i]);
			addChild(bl,1);
			bl->setPosition(origin + Vec2(i*90*6,90*2) );
			bigLetters.pushBack(bl);
		}

	}
	else
	{


		for (int t = 0 ; t<3; t++)
		{
			auto whiteBar = Sprite::create("BLANK.png");
			whiteBar->setTextureRect(Rect(origin.x,origin.y,visibleSize.width,90));
			whiteBar->setPosition(visibleSize.width/2 , MapPointsManager::getPointByIndex(64+t*8).y);
			whiteBar->setOpacity(180 - t*55 );
			addChild(whiteBar,1,whiteBar_tag + t);
		}


		auto grayLayer = Sprite::create("BLANK.png");
		grayLayer->setTextureRect(Rect(origin.x,origin.y,visibleSize.width,visibleSize.height));
		grayLayer -> setColor(Color3B(50,50,50));
		grayLayer->setOpacity(127);
		grayLayer->setPosition(visibleSize/2);
		addChild(grayLayer,2);

	}
}






