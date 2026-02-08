#pragma once

#include "Actor/Plane.h"

using namespace Nahoo;

class C_PLANEALLY : public C_PLANE
{
	C_PLANEALLY(const char* fileName, C_VECTOR2& position);

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnHit(const C_ACTOR* otherActor) override;



};
