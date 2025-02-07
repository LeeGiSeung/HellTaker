#include "pch.h"
#include "CWall.h"

#include "CCollider.h"

CWall::CWall()
	:m_HitBox(nullptr)
	, WallSize({0.f,0.f})
{
	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox");
	m_HitBox->SetOffset(WallSize);
	AddComponent(m_HitBox);
}

CWall::~CWall()
{
}

void CWall::Render()
{
	//ºÎ¸ð ·»´õ
	//CObj::Render();
}

void CWall::Begin()
{
}

void CWall::Tick()
{
}

