#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

using namespace olc;

class App : public PixelGameEngine
{
public:
	App()
	{
		sAppName = "olc::Game Jam 2020";
	}

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float deltaTime) override
	{


		FillRectDecal({ 0, 0 }, { (float)ScreenWidth(), (float)ScreenHeight() }, Pixel(0xFF393939));

		#pragma region Draw Grass
		GradientFillRectDecal({ 0.0F, (float)(ScreenHeight() - 50) }, { (float)ScreenWidth(), 25.0F }, Pixel(0xFF00FF00), Pixel(0xFF13458B), Pixel(0xFF13458B), Pixel(0xFF00FF00));
		FillRectDecal({ 0.0F, (float)(ScreenHeight() - 25) }, { (float)ScreenWidth(), 25.0F }, Pixel(0xFF13458B));
		#pragma endregion

		return true;
	}
};

int main()
{
	App app;
	if (app.Construct(1000, 800, 1, 1))
		app.Start();
}