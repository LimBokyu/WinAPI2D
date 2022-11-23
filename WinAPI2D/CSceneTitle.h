#pragma once
#include "CScene.h"

class CTitle;

class CSceneTitle : public CScene
{
public:
	CSceneTitle();
	virtual ~CSceneTitle();

private:
	CTitle* title;

	bool m_bTrigger;
	bool m_bSound;
	float m_fTimer = 0;


private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;

	void PlaySoundEffect();
};
