#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include"Player.h"
#include<map>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<windows.h>
#include"Bullet.h"
#include"Bulletship.h"
#include"Enemy.h"
#include"Enemyship.h"
#include"item.h"
#include"BG.h"
#include"Heal.h"
#include"Button.h"
#include<SFML/Audio.hpp>
using namespace std;


class game
{
private:
	sf::RenderWindow* window;
	
	std::map<std::string, sf::Texture *> textures;
	std::vector<Bullet*> bullets;


	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;

	sf::Sprite worldBackground;
	sf::Texture worldBackgroundTex;
	sf::Sprite Menubg;
	sf::Texture Menutex;
	sf::Sprite Scorebg;
	sf::Texture Scoretex;

	Player* player;

	sf::RectangleShape playerHpbar;
	sf::RectangleShape playerHpbarBack;

	std::map<std::string, sf::Texture*> textureenemy;
	std::vector<Enemy*> enemies;

	Enemy* enemy;

	std::map<std::string, sf::Texture*> textureenemyship;
	std::vector<Enemyship*> enemieships;
	Enemyship* enemyship;

	std::map<std::string, sf::Texture*> textureitem;
	std::vector<item*> items;

	std::map<std::string, sf::Texture*> textureheal;
	std::vector<Heal*>heals;

	sf::Clock clock;
	std::vector<BG> Backgrounds;

	sf::Text myName;
	sf::Text Playername;
	sf::Text PlayernameText;

	sf::String Playerinput;
	sf::String Sendnametoscore;

	sf::String playerNamescore[6];
	sf::Text Textscore;
	sf::Text Playernametext_2[6];
	sf::Text Playerscore[6];

	sf::Text tryagain;

	sf::SoundBuffer sound;
	sf::Sound Sound;

	sf::SoundBuffer bgsoundbuffer;
	sf::Sound bgsound;

	int K = 0;

	unsigned points;

	float spawnTimer;
	float spawnTimerMax;
	float count;

	float spawnTimerenemyship;
	float spawnTimerMaxenemyship;
	float countenemyship;

	int getItem = 0;
	int creatItem = 0;
	int countit=0;

	int getHeal = 0;
	int creatHeal = 0;
	int countHeal=0;
	
	float deltaTime = 0.0f;
	bool gameover = false;
	
	int Menu=0;
	int Score[7];
	int Rank=5;

	void initWorld();
	void initWindow();
	void initbullets();
	void initGui();
	void initSystem();
	void initPlayer();
	void initEnemies();
	void initEnemieship();
	void initItem();
public:
	game();
	virtual ~game();

	inline const bool gameOverCheck() { return gameover; }
	inline const long getScore() { return points; }

	void run();
	void updatePollEvents();
	void updateInput();
	void updateGui();
	void updateBullets();
	void updateItem();
	void updateEnemies();
	void updateEnemieships();
	void updateCombat();
	void updateReciveitem();
	void update();
	void updateWorld();
	void updateCollision();
	void updatestate();
	void render();
	void reset();
	void updategameover();
	
};


