#include "EffectManager.h"
#include "Effect/Effect.h"

Nahoo::C_EFFECTMANAGER::C_EFFECTMANAGER()
{
	m_effectPool.resize(16);

	for (int i = 0; i < 16; ++i)
	{
		m_effectPool[i] = new C_EFFECT();
	}

}

Nahoo::C_EFFECTMANAGER::~C_EFFECTMANAGER()
{
	for (C_EFFECT* effect : m_effectPool)
	{
		delete effect;
		effect = nullptr;
	}
}

void Nahoo::C_EFFECTMANAGER::SpawnEffect(int effectType, const C_VECTOR2& position, float frameDuration, E_COLOR color, int sortingOrder)
{
	std::vector<std::string> fileNames{};

	if (effectType == 0)
	{
		SetFileNameBulletDestroy(fileNames);
	}
	else if (effectType == 1)
	{
		SetFileNamePlaneDestroy(fileNames);
	}
	else if (effectType == 2)
	{
		SetFileNamePowerItem(fileNames);
	}
	else
	{
		SetFileNameSpecialAttackItem(fileNames);
	}
	
	
	for (C_EFFECT* effect : m_effectPool)
	{
		if (effect->IsActive() == false)
		{
			effect->InitializeEffect(fileNames, position, frameDuration, color, sortingOrder);
			return;
		}
	}

	// 모두 다 isActive가 true인 경우
	C_EFFECT* newEffect = new C_EFFECT();
	newEffect->InitializeEffect(fileNames, position, frameDuration, color, sortingOrder);
	
	m_effectPool.push_back(newEffect);

}

void Nahoo::C_EFFECTMANAGER::Tick(float deltaTime)
{
	for (C_EFFECT* effect : m_effectPool)
	{
		if (effect->IsActive() == true)
		{
			effect->Tick(deltaTime);
		}
	}
}

void Nahoo::C_EFFECTMANAGER::Draw()
{
	for (C_EFFECT* effect : m_effectPool)
	{
		if (effect->IsActive() == true)
		{
			effect->Draw();
		}
	}
}


void Nahoo::C_EFFECTMANAGER::SetFileNameBulletDestroy(std::vector<std::string>& outFileNames)
{
	outFileNames =
	{
		{"destroyEffect1.txt"},
		{"destroyEffect2.txt"},
		{"destroyEffect3.txt"},
		{"destroyEffect2.txt"},
		{"destroyEffect1.txt"}
	};
}

void Nahoo::C_EFFECTMANAGER::SetFileNamePlaneDestroy(std::vector<std::string>& outFileNames)
{
	outFileNames =
	{
		{"destroyEffect2.txt"},
		{"destroyEffect3.txt"},
		{"destroyEffect4.txt"},
		{"destroyEffect5.txt"},
		{"destroyEffect6.txt"},
		{"destroyEffect7.txt"},
		{"destroyEffect8.txt"}
	};
}

void Nahoo::C_EFFECTMANAGER::SetFileNamePowerItem(std::vector<std::string>& outFileNames)
{
	outFileNames =
	{
		{"powerUpEffect.txt"}
		
	};
}

void Nahoo::C_EFFECTMANAGER::SetFileNameSpecialAttackItem(std::vector<std::string>& outFileNames)
{
	outFileNames =
	{
		{"specialAttackEffect.txt"}
	};
}
