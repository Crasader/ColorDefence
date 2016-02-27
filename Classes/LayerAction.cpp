#include "LayerAction.h"
#include "CannonPrebuilt.h"
#include "MapPointsManager.h"
#include "NumericalManager.h"
#include "ResourceManager.h"
#include "GameStateManager.h"
#include "BulletManager.h"
#include "CannonManager.h"


#include "ParticleEmitterManager.h"



USING_NS_CC;

const int cannon_z_order=45;



// on "init" you need to initialize your instance
bool LayerAction::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	GameStateManager::getInstance()->currentActioningState = true;

	//��ʼ 10�λ���
	chancesLeft =10;

	//��1����ʼ
	currentWave = 1;

	_enemieReleased= false;

	//��������ɽ��족���¼�
	auto listenerStartBuilding = EventListenerCustom ::create("FINISH_BUILDING",CC_CALLBACK_1(LayerAction::finishBuilding, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerStartBuilding,this);

	//�������������족���¼�
	auto listenerUpgrade = EventListenerCustom ::create("UPGRADE",[&](EventCustom* event){
	
		CannonPrebuilt* cpb =  static_cast<CannonPrebuilt*>(event->getUserData());

		for (Cannon* c: CannonManager::getInstance()->cannons)
		{
			if (c->getPosition()== cpb->getPosition())
			{
				c->setColorInfo(cpb->colorInfo);
				
				if (GameStateManager::getInstance()->currentActioningState)
				{
					c->scheduleUpdate();
					c->resume();

				}

			}
		}

	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerUpgrade,this);



	//�����������������¼�
	auto listenerSuperPower = EventListenerCustom ::create("SUPER_POWER",[&](EventCustom* event){

		if (!GameStateManager::getInstance()->currentActioningState )
		{
			return;
		}

		ResourceManager* rm = ResourceManager::getInstance();
		int min = rm->restResource[0];
		for (int i = 1; i<3 ; i++)
		{
			if (rm->restResource[i]<min)
			{
				min = rm->restResource[i];
			}
		}
		//log("min == %d",min);
		int power = 0;
		for (int i = 0; i<3 ; i++)
		{
			power += rm->restResource[i]-min;
			rm->restResource[i] = min;
		}
		//log("power == %d",power);
		if (power == 0)
		{
			return;
		}

		SoundManager::getInstance()->playSoundEffect("sound/superPower.wav");

		for (Enemy* e : enemyManager->enemiesInSequence)
		{

			
			ParticleSystem* superPower = ParticleSystemQuad::create("effects/Particle_SuperPower.plist");

			superPower->setEmissionRate(power>8?64:power*power);
			superPower->setTotalParticles(power>8?64:power*power);
			addChild(superPower);
			superPower->setPosition(e->getPosition());
			pem->particleEmitters.pushBack(superPower);

			e->onSuperPowerDamage(power*power*1.2);

		}

		if (power> 10)
		{
			for (Enemy* e : enemyManager->enemiesInSequence)
			{

				//e->shake();
				_eventDispatcher->dispatchCustomEvent("SUPER_SHAKE",&power);
			}
		}

	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerSuperPower,this);






	//�������ͷŵ��ˡ����¼�
	auto listenerReady = EventListenerCustom ::create("RELEASE_ENEMIES",CC_CALLBACK_1(LayerAction::startActioning, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerReady,this);


	//cannons = Vector<Cannon*>();

	enemyManager = EnemyManager::getInstance();

	pem = ParticleEmitterManager::getInstance();

	levelManager = LevelManager::getInstance();

	_enemyPath = std::vector<Point>();
	for (int i= 0; i <levelManager->getEnemyPath().size()  ; i++)
	{
		_enemyPath.push_back(MapPointsManager::getPointByIndex(levelManager->getEnemyPath().at(i))); 
	}

	_iterator = 0;

	//��������ͣ�����������¼�
	auto listenerPause = EventListenerCustom ::create("PAUSE_ACTIONING",[&](Event* event){
		setGameActioning(false);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerPause,this);
	auto listenerResume = EventListenerCustom ::create("RESUME_ACTIONING",[&](Event* event){
		setGameActioning(true);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerResume,this);







	


	return true;
}

void LayerAction::finishBuilding(cocos2d::EventCustom* event)
{
	CannonPrebuilt* cpb =  static_cast<CannonPrebuilt*>(event->getUserData());
	

	Cannon* cannon = nullptr;
	cannon = CannonManager::getInstance()->getCannonByType(cpb->getCannonType());

	addChild(cannon,cannon_z_order);
	cannon->setPosition(cpb->getPosition());
	CannonManager::getInstance()->cannons.pushBack(cannon);
	cannon->setColorInfo(cpb->colorInfo);
	cannon->setDamageContributerID();

}

void LayerAction::update( float delta )
{


	
	
	//�ֵĳ���  iterator �����¹� ����sequence
	if (enemyManager->enemiesLeft.size()>0)
	{

		_iterator++;

		if (_iterator>= enemyManager->enemiesLeft.back()->timeInterval)
		{
			_iterator = 0;

			releaseOneEnemy();

		}
	}



	//�ֵ��ƶ�  sequence�еĹ� ����path�ƶ�
	for (Enemy* e:enemyManager->enemiesInSequence)
	{

		if (e->isMoving())
		{
			if (e->getPosition().getDistance(_enemyPath.at(e->currentDestination))<e->moveSpeed)
			{
				e->setPosition(_enemyPath.at(e->currentDestination));
				if (e->currentDestination< _enemyPath.size() -1)
				{

					e->setMoveDirection(_enemyPath.at(e->currentDestination + 1) - _enemyPath.at(e->currentDestination));
					e->currentDestination++;

				}
				else //enemy�����յ�
				{

					e->willArrive();
					if (e->isAlive())
					{
						enemyManager->enemiesArrive.pushBack(e);
					}
					

				}


			}
			else
			{
				e->setPosition(e->getPosition()+ e->moveSpeed * e->getMoveDirection());
			}

		}



	}


	//�����յ�Ĺ�
	for (Enemy* e:enemyManager->enemiesArrive)
	{
		if ((enemyManager->enemiesInSequence.contains(e))&&(e->isAlive()))
		{
			enemyManager->enemiesInSequence.eraseObject(e);
			chancesLeft -= e->chancesCost();

			

			if (chancesLeft<0)
			{
				chancesLeft=0;
			}
			_eventDispatcher->dispatchCustomEvent("CHANCES_LOSE",&chancesLeft);
		}


	}




	for (Enemy* e : enemyManager->enemiesInSequence)
	{
		//e->computeBuff();
		e->solveBuff();
	}



	//�ֵ����� sequence�еĹ� ����ֵ����0 ����dead
	for (Enemy* e:enemyManager->enemiesInSequence)
	{
		if (!e->isAlive())
		{
			enemyManager->enemiesDead.pushBack(e);
			//e->setVisible(false);
			e->onDeath();

			
		}
	}
	for (Enemy* e:enemyManager->enemiesDead)
	{
		if (enemyManager->enemiesInSequence.contains(e))
		{
			enemyManager->enemiesInSequence.eraseObject(e);

		}
	}
	


	//����ϵͳ �����ӵ�����ϵͳ������
	for (ParticleSystem* ps:pem->particleEmitters)
	{
		if ((ps->getParticleCount()==0)&&(ps->getEmissionRate()==0))
		{
			ps->unscheduleUpdate();
			ps->removeFromParent();
			pem->emittersToRemove.pushBack(ps);
		}
	}
	for (ParticleSystem* ps:pem->emittersToRemove)
	{
		if ((pem->particleEmitters.contains(ps))&&(ps->getParticleCount()==0))
		{
			pem->particleEmitters.eraseObject(ps);

		}
	}
	pem->emittersToRemove.clear();




	//��Ϸ�����ж�
	if (chancesLeft<=0)
	{
		_eventDispatcher->dispatchCustomEvent("GAME_OVER_LOSE");
		//log("lose");
		unscheduleUpdate();
	}
	else if ((enemyManager->enemiesLeft.size()== 0)&&(enemyManager->enemiesInSequence.size()==0))
	{
		unsigned grading = chancesLeft==10?3:(chancesLeft>=5?2:1);
		levelManager->newLevelRecord(grading);
		_eventDispatcher->dispatchCustomEvent("GAME_OVER_WIN",&grading);
		//log("win");
		unscheduleUpdate();
	}


}

void LayerAction::startActioning( cocos2d::EventCustom* event )
{
	_enemieReleased = true;
	scheduleUpdate();
}

void LayerAction::releaseOneEnemy()
{


	if (enemyManager->enemiesLeft.back()->isRealEnemy)
	{

		enemyManager->enemiesInSequence.pushBack(enemyManager->enemiesLeft.back());
		this->addChild(enemyManager->enemiesInSequence.back(),0);
		enemyManager->enemiesInSequence.back()->setPosition(_enemyPath.front()) ;
		enemyManager->enemiesInSequence.back()->currentDestination = 1;

		enemyManager->enemiesInSequence.back()->setMoveDirection(_enemyPath.at(1) - _enemyPath.at(0));
	}
	else
	{
		currentWave++;
		_eventDispatcher->dispatchCustomEvent("NEXT_WAVE",&currentWave);
	}

	enemyManager->enemiesLeft.popBack();


}

void LayerAction::setGameActioning( bool actioning )
{

	Vector<Bullet*> bullets = BulletManager::getInstance()->bullets;
	CannonManager* cm = CannonManager::getInstance();
	ParticleEmitterManager* pem = ParticleEmitterManager::getInstance();
	

	if (actioning)
	{
		
		if (_enemieReleased)
		{
			scheduleUpdate();
		}
		
		for (Cannon* c : cm->cannons)
		{
			c->scheduleUpdate();
			c->resume();

		}
		for (Enemy* e : enemyManager->enemiesInSequence)
		{
			e->resume();

		}
		for (Enemy* e : enemyManager->enemiesDead)
		{
			e->resume();

		}
		for (Bullet* b : bullets)
		{
			b->resume();
		}
		for (ParticleSystem* p : pem->particleEmitters)
		{
			p->resume();
		}


	}
	else
	{
		unscheduleUpdate();
		for (Cannon* c : cm->cannons)
		{
			c->pause();
			c->unscheduleUpdate();
			
		}
		for (Enemy* e : enemyManager->enemiesInSequence)
		{
			e->pause();

		}
		for (Enemy* e : enemyManager->enemiesDead)
		{
			e->pause();

		}
		for (Bullet* b : bullets)
		{
			b->pause();
		}
		for (ParticleSystem* p : pem->particleEmitters)
		{
			p->pause();
		}
	}
}



