#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"
#include "Enumeration/MoveDirection.h"

class C_SPAWNER : public Nahoo::C_ACTOR
{
public:
	C_SPAWNER();
	~C_SPAWNER();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnDestroy() override;

	void SpawnBackGround();
	void SpawnEnemy();
	void SpawnAlly();

private:
	void EnemyPattern1();
	void EnemyPattern2();

	void MakeBigEnemy(Nahoo::C_VECTOR2& spawnPosition, E_MOVEDIRECTION bulletDirection, E_MOVEDIRECTION moveDirection, bool sideBulletSpeedFlag, bool isBounce);
	void MakeSmallEnemy(Nahoo::C_VECTOR2& spawnPosition, E_MOVEDIRECTION bulletDirection, E_MOVEDIRECTION moveDirection, bool sideBulletSpeedFlag, bool isBounce);

private:
	UTIL::C_TIMER m_backgroundTimer{ 3.0f };
	UTIL::C_TIMER m_enemySpawnTimer{ 5.0f };

	const char* m_backGroundFileNames[3]{};

};