#pragma once
#include "CGameObject.h"
class CStage01Map : public CGameObject
{

private:
	CImage* m_Map;
	CImage* m_MiddleMap;

public:
	CStage01Map();
	virtual ~CStage01Map();

private:
	void Init()		override;
	void Render()	override;
	void Update()	override;
	void Release()	override;
};