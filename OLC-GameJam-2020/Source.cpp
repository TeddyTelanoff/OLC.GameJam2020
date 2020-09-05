#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <vector>

using namespace olc;

#define map(val, im, iM, om, oM) iM + (oM - im) * (val - im) / (om - im)

#define WIDTH 1000
#define HEIGHT 800
#define BS 50
const vf2d bs = { BS, BS };
float deltaTime;

struct Player
{
	PixelGameEngine* app;

	vf2d pos;
	float speed;

	std::vector<float> clicks;

	void Update()
	{
		if ((app->GetKey(A).bPressed || app->GetKey(A).bHeld) || (app->GetKey(LEFT).bPressed || app->GetKey(LEFT).bHeld))
			pos.x -= deltaTime * BS * speed;
		if ((app->GetKey(D).bPressed || app->GetKey(D).bHeld) || (app->GetKey(RIGHT).bPressed || app->GetKey(RIGHT).bHeld))
			pos.x += deltaTime * BS * speed;
		if ((app->GetKey(W).bPressed || app->GetKey(W).bHeld) || (app->GetKey(UP).bPressed || app->GetKey(UP).bHeld))
			pos.y -= deltaTime * BS * speed;
		if ((app->GetKey(S).bPressed || app->GetKey(S).bHeld) || (app->GetKey(DOWN).bPressed || app->GetKey(DOWN).bHeld))
			pos.y += deltaTime * BS * speed;

		if (app->GetMouse(0).bPressed)
		{
			clicks.push_back((float)app->GetMouseX());
			clicks.push_back((float)app->GetMouseY());
			clicks.push_back(1.0F);
		}
	}

	void Draw()
	{
		for (size_t i = 0; i < clicks.size() / 3; i++)
		{
			app->FillRectDecal({ clicks[(i * 3) + 0], clicks[(i * 3) + 1] }, bs / 2, ((int) map(clicks[i * 3 + 2], 0.0f, 1.0f, 0x01000000, 0xFF000000)) | 0x00FF00);
			clicks[i * 3 + 2] -= deltaTime;

			if (clicks[i * 3 + 2] <= 0)
			{
				clicks.erase(clicks.begin() + i * 3);
				clicks.erase(clicks.begin() + i * 3);
				clicks.erase(clicks.begin() + i * 3);
				i--;
			}
		}

		app->FillRectDecal(pos, bs, GREEN);
	}
};

struct App : public PixelGameEngine
{
	Player player;

	bool OnUserCreate() override
	{
		sAppName = "olc::Game Jam 2020";

		player = { this, { WIDTH / 2, HEIGHT / 2 }, 15 };

		return true;
	}

	bool OnUserUpdate(float dt) override
	{
		if (GetKey(ESCAPE).bReleased)
			return false;

		deltaTime = dt;

		player.Update();

		FillRectDecal({ 0, 0 }, { WIDTH, HEIGHT }, 0xFF393939);

		player.Draw();

		return true;
	}
};

int main()
{
	App app;
	if (app.Construct(WIDTH, HEIGHT, 1, 1))
		app.Start();
}