#include "Spawner.h"
#include "Actor/Object.h"
#include "Util/Util.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Actor/Plane.h"

C_SPAWNER::C_SPAWNER()
{

}

C_SPAWNER::~C_SPAWNER()
{
	OnDestroy();
}

void C_SPAWNER::BeginPlay()
{
	Nahoo::C_ACTOR::BeginPlay();

	m_backGroundFileNames[0] = "cloud.txt";
	m_backGroundFileNames[1] = "cloud2.txt";
	m_backGroundFileNames[2] = "cloud3.txt";

	m_backgroundTimer.SetTargetTime(5.0f);
	m_enemySpawnTimer.SetTargetTime(2.0f);

	// 미리 배경 스폰
	C_OBJECT* back{};

	int indexRandom = UTIL::RandomInteger(0, 2);
	int xRandom = UTIL::RandomInteger(0, Nahoo::C_ENGINE::GetInstance().GetWidth());
	int yRandom = UTIL::RandomInteger(0, Nahoo::C_ENGINE::GetInstance().GetHeight());
	C_VECTOR2 position = C_VECTOR2(xRandom, yRandom);
	int speedRandom = UTIL::RandomInteger(10, 35);
	
	back = new C_OBJECT(m_backGroundFileNames[indexRandom], position, false, E_COLOR::BackgroundWhite | E_COLOR::White, 0, speedRandom);
	back->GiveMoveOrder(E_MOVEDIRECTION::Down);
	m_owner->AddNewActor(back);

}

void C_SPAWNER::Tick(float deltaTime)
{
	Nahoo::C_ACTOR::Tick(deltaTime);

	m_backgroundTimer.Tick(deltaTime);
	m_enemySpawnTimer.Tick(deltaTime);

	if (m_backgroundTimer.IsTimeOut() == true)
	{
		SpawnBackGround();
	}
	if (m_enemySpawnTimer.IsTimeOut() == true)
	{
		SpawnEnemy();
	}

}

void C_SPAWNER::OnDestroy()
{

}

void C_SPAWNER::SpawnBackGround()
{
	C_OBJECT* back{};

	int indexRandom = UTIL::RandomInteger(0, 2);
	int xRandom = UTIL::RandomInteger(-5, Nahoo::C_ENGINE::GetInstance().GetWidth() - 10);
	C_VECTOR2 position = C_VECTOR2(xRandom, -40);
	int speedRandom = UTIL::RandomInteger(10, 40);

	back = new C_OBJECT(m_backGroundFileNames[indexRandom], position, false, E_COLOR::BackgroundWhite | E_COLOR::White, 0, speedRandom);
	back->GiveMoveOrder(E_MOVEDIRECTION::Down);
	m_owner->AddNewActor(back);

	m_backgroundTimer.Reset();
	float targetTimeRandom = UTIL::RandomFloat(3, 8);
	m_backgroundTimer.SetTargetTime(targetTimeRandom);
}

void C_SPAWNER::SpawnEnemy()
{
	int patternRandom = UTIL::RandomInteger(1, 2);
	if (patternRandom == 1)
	{
		EnemyPattern1();
	}
	else
	{
		EnemyPattern2();
	}

	m_enemySpawnTimer.Reset();
	float targetTimeRandom = UTIL::RandomFloat(5, 10);
	m_enemySpawnTimer.SetTargetTime(targetTimeRandom);
}

void C_SPAWNER::SpawnAlly()
{

}

void C_SPAWNER::EnemyPattern1()
{
	bool directionChoose = (UTIL::RandomFloat(0, 1)) <= 0.5; // 0.5까지는 왼쪽 나머지 오른쪽
	E_MOVEDIRECTION direction{};
	C_VECTOR2 spawnPosition{};

	if (directionChoose == true)
	{
		direction = E_MOVEDIRECTION::Left;
		spawnPosition.m_x = Nahoo::C_ENGINE::GetInstance().GetWidth() - 5;
	}
	else
	{
		direction = E_MOVEDIRECTION::Right;
		spawnPosition.m_x = -5;
	}
	bool IsBigEnemy = (UTIL::RandomFloat(0, 1)) > 0.7; // true이면 큰 적군 생성

	int enemyRandomNumber = UTIL::RandomInteger(1, 3);
	for (int i = 1; i < +enemyRandomNumber; i++)
	{
		spawnPosition.m_y = UTIL::RandomInteger(40 * (i - 1), 40 * i);
		if (IsBigEnemy == true)
		{
			MakeBigEnemy(spawnPosition, E_MOVEDIRECTION::Down | direction, direction, true, false);
		}
		else
		{
			MakeSmallEnemy(spawnPosition, E_MOVEDIRECTION::Down | direction, direction, true, false);
		}


	}

}

void C_SPAWNER::EnemyPattern2()
{
	bool IsBigEnemy = (UTIL::RandomFloat(0, 1)) > 0.7;
	C_VECTOR2 spawnPosition{};
	spawnPosition.m_y = -5;

	int enemyRandomNumber = UTIL::RandomInteger(1, 3);
	for (int i = 0; i<enemyRandomNumber; i++)
	{
		spawnPosition.m_x = UTIL::RandomInteger(Nahoo::C_ENGINE::GetInstance().GetWidth() / 3 * i, Nahoo::C_ENGINE::GetInstance().GetWidth() / 3 * (i + 1));
		if (IsBigEnemy == true)
		{
			MakeBigEnemy(spawnPosition, E_MOVEDIRECTION::Down, E_MOVEDIRECTION::Down, true, false);
		}
		else
		{
			MakeSmallEnemy(spawnPosition, E_MOVEDIRECTION::Down, E_MOVEDIRECTION::Down, true, false);
		}
	}
}

void C_SPAWNER::MakeBigEnemy(Nahoo::C_VECTOR2& spawnPosition, E_MOVEDIRECTION bulletDirection, E_MOVEDIRECTION moveDirection, bool sideBulletSpeedFlag, bool isBounce)
{
	C_PLANE* plane{};
	const char* fileName{};
	if ((moveDirection) == E_MOVEDIRECTION::Left)
	{
		fileName = "enemy_big_left.txt";
	}
	else if ((moveDirection) == E_MOVEDIRECTION::Right)
	{
		fileName = "enemy_big_right.txt";
	}
	else
	{
		fileName = "enemy_big.txt";
	}

	int moveSpeed = UTIL::RandomInteger(20, 60);
	float fireRate = UTIL::RandomFloat(1.2f, 1.8f);
	int bulletHorizontalSpeed{};

	if (sideBulletSpeedFlag == true)
	{
		bulletHorizontalSpeed = UTIL::RandomInteger(30, 80);
	}
	else
	{
		bulletHorizontalSpeed = 0;
	}

	plane = new C_PLANE(fileName, spawnPosition, true, E_COLOR::Red | E_COLOR::ForegroundIntensity, moveSpeed, 10, E_COLLISIONTYPE::Enemy, fireRate);
	plane->SetBulletSpec("enemyBullet.txt", E_COLOR::Red | E_COLOR::ForegroundIntensity | E_COLOR::BackgroundRed, bulletHorizontalSpeed, 60, 3, isBounce, bulletDirection);
	plane->GiveMoveOrder(moveDirection);
	m_owner->AddNewActor(plane);


}

void C_SPAWNER::MakeSmallEnemy(Nahoo::C_VECTOR2& spawnPosition, E_MOVEDIRECTION bulletDirection, E_MOVEDIRECTION moveDirection, bool sideBulletSpeedFlag, bool isBounce)
{
	C_PLANE* plane{};
	const char* fileName{};
	if (moveDirection == E_MOVEDIRECTION::Left)
	{
		fileName = "enemy_small_left.txt";
	}
	else if (moveDirection == E_MOVEDIRECTION::Right)
	{
		fileName = "enemy_small_right.txt";
	}
	else
	{
		fileName = "enemy_small.txt";
	}
	int moveSpeed = UTIL::RandomInteger(30, 70);
	float fireRate = UTIL::RandomFloat(0.8f, 1.2f);
	int bulletHorizontalSpeed{};

	if (sideBulletSpeedFlag == true)
	{
		bulletHorizontalSpeed = UTIL::RandomInteger(40, 80);
	}
	else
	{
		bulletHorizontalSpeed = 0;
	}

	plane = new C_PLANE(fileName, spawnPosition, true, E_COLOR::Red, moveSpeed, 5, E_COLLISIONTYPE::Enemy, fireRate);
	plane->SetBulletSpec("enemyPistol.txt", E_COLOR::Red | E_COLOR::BackgroundRed | E_COLOR::BackgroundRed, bulletHorizontalSpeed, 80, 1, isBounce, bulletDirection);
	plane->GiveMoveOrder(moveDirection);
	m_owner->AddNewActor(plane);

}
