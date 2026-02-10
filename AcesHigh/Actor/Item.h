#pragma once

#include "Actor/Object.h"
#include "Enumeration/ItemType.h"

class C_ITEM : public C_OBJECT
{

public:
	C_ITEM(const char* fileName, C_VECTOR2& position, E_COLOR color, int sortingOrder,
		int horizontalSpeed, int verticalSpeed, E_ITEMTYPE itemType, bool isBounce);
	~C_ITEM();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnHit(const C_ACTOR* otherActor) override;
	virtual void OnDestroy() override;

	const E_ITEMTYPE GetItemType () const;


private:

	E_ITEMTYPE m_itemType{};


};
