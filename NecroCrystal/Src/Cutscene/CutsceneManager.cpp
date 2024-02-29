#include "CutsceneManager.h"

CutsceneManager::CutsceneManager() :
	cutsceneIndex(0)
{
}

CutsceneManager::~CutsceneManager()
{
	for (auto& cutscene : tutorial)
	{
		delete cutscene;
	}
}

void CutsceneManager::initialize(sf::Vector2i& windowDimensions, TextManager& textManager)
{
	Cutscene* move = new Cutscene();
	move->Initialize(windowDimensions, "Assets/Cutscenes/Move.png");
	move->AddAText("ZQSD To Move", textManager, sf::Vector2f(windowDimensions.x * 0.35f, windowDimensions.y * 0.4f));
	tutorial.push_back(move);

	Cutscene* basicAttack = new Cutscene();
	basicAttack->Initialize(windowDimensions, "Assets/Cutscenes/BasicAttack.png");
	basicAttack->AddAText("Left Click", textManager, sf::Vector2f(windowDimensions.x * 0.47f, windowDimensions.y * 0.4f));
	basicAttack->AddAText("To Attack", textManager, sf::Vector2f(windowDimensions.x * 0.55f, windowDimensions.y * 0.56f));
	tutorial.push_back(basicAttack);

	Cutscene* pause = new Cutscene();
	pause->Initialize(windowDimensions, "Assets/Cutscenes/Move.png");
	pause->AddAText("P for Pause", textManager, sf::Vector2f(windowDimensions.x * 0.35f, windowDimensions.y * 0.4f));
	tutorial.push_back(pause);

	Cutscene* dash = new Cutscene();
	dash->Initialize(windowDimensions, "Assets/Cutscenes/NecroZone.png");
	dash->AddAText("Shift To Dodge", textManager, sf::Vector2f(windowDimensions.x * 0.42f, windowDimensions.y * 0.3f));
	tutorial.push_back(dash);

	Cutscene* skeletonSpawn = new Cutscene();
	skeletonSpawn->Initialize(windowDimensions, "Assets/Cutscenes/SkeletonSpawn.png");
	skeletonSpawn->AddAText("Skeleton Spawn", textManager, sf::Vector2f(windowDimensions.x * 0.38f, windowDimensions.y * 0.3f));
	skeletonSpawn->AddAText("On Enemy Kill", textManager, sf::Vector2f(windowDimensions.x * 0.38f, windowDimensions.y * 0.45f));
	tutorial.push_back(skeletonSpawn);

	Cutscene* skeletonAttack1 = new Cutscene();
	skeletonAttack1->Initialize(windowDimensions, "Assets/Cutscenes/SkeletonAttack1.png");
	skeletonAttack1->AddAText("If an Enemy is", textManager, sf::Vector2f(windowDimensions.x * 0.45f, windowDimensions.y * 0.25f));
	skeletonAttack1->AddAText("Attacked Close", textManager, sf::Vector2f(windowDimensions.x * 0.47f, windowDimensions.y * 0.40f));
	skeletonAttack1->AddAText("To a Skeleton", textManager, sf::Vector2f(windowDimensions.x * 0.49f, windowDimensions.y * 0.55f));
	tutorial.push_back(skeletonAttack1);

	Cutscene* skeletonAttack2 = new Cutscene();
	skeletonAttack2->Initialize(windowDimensions, "Assets/Cutscenes/SkeletonAttack2.png");
	skeletonAttack2->AddAText("Skeleton Will", textManager, sf::Vector2f(windowDimensions.x * 0.3f, windowDimensions.y * 0.30f));
	skeletonAttack2->AddAText("also Attack it", textManager, sf::Vector2f(windowDimensions.x * 0.32f, windowDimensions.y * 0.45f));
	tutorial.push_back(skeletonAttack2);

	Cutscene* skeletonDash = new Cutscene();
	skeletonDash->Initialize(windowDimensions, "Assets/Cutscenes/SkeletonDash.png");
	skeletonDash->AddAText("Right Click To", textManager, sf::Vector2f(windowDimensions.x * 0.35f, windowDimensions.y * 0.20f));
	skeletonDash->AddAText("Skeleton Dash", textManager, sf::Vector2f(windowDimensions.x * 0.38f, windowDimensions.y * 0.35f));
	tutorial.push_back(skeletonDash);
}

int CutsceneManager::update(float deltaTime, sf::Vector2i& windowDimensions)
{
	int actionTaken = tutorial.at(cutsceneIndex)->Update(deltaTime, windowDimensions);
	if (actionTaken == 1)
	{
		if (++cutsceneIndex >= tutorial.size())
		{
			cutsceneIndex = 0;
			return 1;
		}
	}
	if (actionTaken == 2)
	{
		if (--cutsceneIndex < 0)
		{
			cutsceneIndex = 0;
			return 1;
		}
	}
	return 0;
}

void CutsceneManager::draw(sf::RenderWindow* window)
{
	tutorial.at(cutsceneIndex)->Draw(window);
}