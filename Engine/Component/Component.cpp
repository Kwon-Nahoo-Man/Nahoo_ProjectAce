#include "Component.h"

void Nahoo::COMP_COMPONENT::BeginPlay()
{
	if (m_hasBeganPlay == true)
	{
		return;
	}
	m_hasBeganPlay = true;

}

void Nahoo::COMP_COMPONENT::SetOwner(C_ACTOR* owner)
{
	m_owner = owner;
}

void Nahoo::COMP_COMPONENT::Tick(float deltaTime)
{

}

void Nahoo::COMP_COMPONENT::Destroy()
{

}

void Nahoo::COMP_COMPONENT::OnDestroy()
{

}

