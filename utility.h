#pragma once
#include "SDL.h"
#include "Vector2.h"

const static double TARGET_FRAME_SECONDS = 0.00167; // Desired time per simulated tick
const static int WINDOW_WIDTH = 800;
const static int WINDOW_HEIGHT = 640;


static class Utility
{
public:
	static void SetRectValues(SDL_Rect &rect, int w, int h, int x, int y)
	{
		rect.w = w;
		rect.h = h;
		rect.x = x;
		rect.y = y;
	}

	static SDL_Rect CreateRect (int w, int h, int x, int y)
	{
		SDL_Rect rect;
		rect.w = w;
		rect.h = h;
		rect.x = x;
		rect.y = y;
		return rect;
	}

	static SDL_Rect GetCenteredRect(SDL_Rect& oldRect)
	{
		int moveX = oldRect.w / 2;
		int moveY = oldRect.h / 2;

		SDL_Rect newRect;
		newRect.x = oldRect.x - moveX;
		newRect.y = oldRect.y - moveY;
		newRect.h = oldRect.h;
		newRect.w = oldRect.w;

		return newRect;
	}

	static bool IsInBounds(Vector2 pos, int boundsWidth, int boundsHeight, int buffer)
	{
		if (pos.x > 0-buffer && pos.x < boundsWidth + buffer && pos.y > 0 - buffer && pos.y < boundsHeight + buffer)
			return true;

		return false;
	}
};

