#pragma once

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)
#define SCREEN_WIDTH 640 //320 
#define SCREEN_HEIGHT 579 //240

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48

enum Type
{
	GROUND = 2,
	BRICK = 3,
	PIPE = 4,
	KOOPAS = 7,
	MUSHROOM = 10,
	ActivationPoint = 11
};
