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
	dash->Initialize(windowDimensions, "Assets/Cutscenes/Move.png");
	dash->AddAText("Shift To Dodge", textManager, sf::Vector2f(windowDimensions.x * 0.35f, windowDimensions.y * 0.4f));
	tutorial.push_back(dash);

	Cutscene* skeletonSpawn = new Cutscene();
	skeletonSpawn->Initialize(windowDimensions, "Assets/Cutscenes/Move.png");
	skeletonSpawn->AddAText("Skeleton Spawn", textManager, sf::Vector2f(windowDimensions.x * 0.35f, windowDimensions.y * 0.4f));
	skeletonSpawn->AddAText("On Enemy Kill", textManager, sf::Vector2f(windowDimensions.x * 0.35f, windowDimensions.y * 0.55f));
	tutorial.push_back(skeletonSpawn);

	Cutscene* skeletonAttack = new Cutscene();
	skeletonAttack->Initialize(windowDimensions, "Assets/Cutscenes/Move.png");
	skeletonAttack->AddAText("Skeletons Follow", textManager, sf::Vector2f(windowDimensions.x * 0.3f, windowDimensions.y * 0.3f));
	skeletonAttack->AddAText("Your Attacks", textManager, sf::Vector2f(windowDimensions.x * 0.32f, windowDimensions.y * 0.45f));
	skeletonAttack->AddAText("When They Are", textManager, sf::Vector2f(windowDimensions.x * 0.34f, windowDimensions.y * 0.6f));
	skeletonAttack->AddAText("in Range", textManager, sf::Vector2f(windowDimensions.x * 0.36f, windowDimensions.y * 0.75f));
	tutorial.push_back(skeletonAttack);

	Cutscene* skeletonDash = new Cutscene();
	skeletonDash->Initialize(windowDimensions, "Assets/Cutscenes/Move.png");
	skeletonDash->AddAText("Right Click To", textManager, sf::Vector2f(windowDimensions.x * 0.35f, windowDimensions.y * 0.4f));
	skeletonDash->AddAText("Skeleton Dash", textManager, sf::Vector2f(windowDimensions.x * 0.35f, windowDimensions.y * 0.55f));
	tutorial.push_back(skeletonDash);
}

int CutsceneManager::update(float deltaTime, sf::Vector2i& windowDimensions)
{
	if (tutorial.at(cutsceneIndex)->Update(deltaTime, windowDimensions) == 1)
	{
		if (++cutsceneIndex >= tutorial.size())
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