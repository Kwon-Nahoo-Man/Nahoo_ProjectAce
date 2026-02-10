#pragma once

#include "Actor/Actor.h"
#include "Math/Vector2.h"
#include "Math/Color.h"

class C_STATUS : public Nahoo::C_ACTOR
{
public:
	C_STATUS(const char* fileName, Nahoo::C_VECTOR2& position, Nahoo::E_COLOR color);
	~C_STATUS();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
		
	void SetPaint(bool isPaint);


private:
	bool m_isPaint{ true };


};
