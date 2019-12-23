#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha)
{
	CGame * game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, alpha);
}

void CSprite::DrawFlip(int nx, float x, float y, float offsetX, int alpha)
{
	//to-do-lqs
	spriteHandler = CGame::GetInstance()->GetSpriteHandler();
	float camX = CGame::GetInstance()->GetCamPos_x();
	float camY = CGame::GetInstance()->GetCamPos_y();
	D3DXVECTOR3 p(floor(x - camX), floor(y - camY), 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	D3DXMATRIX oldTransform, middleTransform;
	spriteHandler->GetTransform(&oldTransform);

	D3DXVECTOR2 rotate = D3DXVECTOR2(nx > 0 ? -1 : 1, 1);
	D3DXMatrixTransformation2D(&middleTransform, &D3DXVECTOR2(p.x + offsetX, p.x), 0.0f, &rotate, NULL, 0.0f, NULL);
	//D3DXMatrixTransformation2D(&middleTransform, &D3DXVECTOR2(p.x + offsetX, p.x), 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX newTransform = oldTransform * middleTransform;

	spriteHandler->SetTransform(&newTransform);

	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha,255,255,255));
	spriteHandler->SetTransform(&oldTransform);
}


void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}



void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t=this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
		
	}
	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

void CAnimation::RenderFlip(int nx, float x, float y, float offsetX, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}
	frames[currentFrame]->GetSprite()->DrawFlip(nx, x, y, offsetX, alpha);
}
void CAnimation::RenderWhip(int currentId,int nx, float x, float y, float offsetX, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}
	frames[currentId]->GetSprite()->DrawFlip(nx, x, y, offsetX, alpha);
}


CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}