#include "game.h"
void game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("bg/bg.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE"<<"\n";

	}
	if (!this->Menutex.loadFromFile("bg/menu.png"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";

	}
	if (!this->Scoretex.loadFromFile("bg/Scorebg.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->Scorebg.setTexture(this->Scoretex);
	this->Menubg.setTexture(this->Menutex);
	this->worldBackground.setTexture(this->worldBackgroundTex);
	Backgrounds.push_back(BG(&worldBackgroundTex, -30.f));
}
void game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1440,1080),"butterfly",sf::Style::Close|sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}
void game::initbullets()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("spirte/bullet01.png");
}

void game::initGui()
{
	if (!this->font.loadFromFile("scoreandfont/Roboto-Black.ttf"))
	cout << "ERROR::GAME::Failed to load font" << "\n";
	
	this->pointText.setPosition(1040.f,20.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("game over");
	this->gameOverText.setPosition(
	this->window->getSize().x/2.f-this->gameOverText.getGlobalBounds().width/2.f,
	this->window->getSize().y/2.f-this->gameOverText.getGlobalBounds().height / 2.f);


	this->playerHpbar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpbar.setFillColor(sf::Color::Red);
	this->playerHpbar.setPosition(sf::Vector2f(100.f, 20.f));

	this->playerHpbarBack = this->playerHpbar;
	this->playerHpbarBack.setFillColor(sf::Color(25, 25, 25, 200));
}
void game::initSystem()
{
	this->points = 0;
	sound.loadFromFile("sound/sound.wav");
	Sound.setBuffer(sound);
	Sound.setVolume(50);
	bgsoundbuffer.loadFromFile("sound/Bgsound.wav");
	bgsound.setBuffer(bgsoundbuffer);
	bgsound.setVolume(50);
	bgsound.setLoop(true);
}
void game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(20.f,500.f);
	this->enemy = new Enemy(20.f, 20.f);
	this->enemyship = new Enemyship(20.f, 20.f);
}
void game::initEnemies()
{
	this->textureenemy["ENEMY"] = new sf::Texture();
	this->textureenemy["ENEMY"]->loadFromFile("spirte/object01.png");
	if (points >= 0&&points<10000) {
		this->spawnTimerMax = 20.f;
	}
	else if (points >= 10000&&points<100000) {
		this->spawnTimerMax = 10.f;
	}
	else if (points >= 100000&&points<1000000) {
		this->spawnTimerMax = 5.f;
	}
	else
	{
		this->spawnTimerMax = 1.f;
	}
	this->spawnTimer = this->spawnTimerMax;
	this->count = 0.f;

}

void game::initEnemieship()
{
	this->textureenemyship["ENEMYSHIP"] = new sf::Texture();
	this->textureenemyship["ENEMYSHIP"]->loadFromFile("spirte/enemy01.png");
	if (points >= 0 && points < 10000) {
		this->spawnTimerMaxenemyship = 100.f;
	}
	else if (points >= 10000 && points < 100000) {
		this->spawnTimerMaxenemyship = 80.f;
	}
	else if (points >= 100000 && points < 1000000) {
		this->spawnTimerMaxenemyship = 60.f;
	}
	else
	{
		this->spawnTimerMaxenemyship = 50.f;;
	}
	this->spawnTimerenemyship = this->spawnTimerMaxenemyship;
	this->countenemyship = 0.f;
}

void game::initItem()
{
	this->textureitem["ITEM"] = new sf::Texture();
	this->textureitem["ITEM"]->loadFromFile("spirte/item.png");
	this->textureheal["HEAL"] = new sf::Texture();
	this->textureheal["HEAL"]->loadFromFile("spirte/heal.png");
	
}
void game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();

	}
}
void game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);
	if (getItem == 0) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
		{
			this->bullets.push_back(new Bullet(this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f,
				this->player->getPos().y + this->player->getBounds().width / 5.f
				, 1.f
				, 0.f
				, 2.f
			)
			);
		}
	}
	if (getItem==1)
	{
		if (countit == 20)
		{
			countit = 0;
			getItem = 0;
			creatItem = 0;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->player->canAttack())
		{
			this->bullets.push_back(new Bullet(this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f,
				this->player->getPos().y + this->player->getBounds().width / 5.f
				, 2.f
				, 0.f
				, 2.f
			)
			);
			this->bullets.push_back(new Bullet(this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f,
				this->player->getPos().y + this->player->getBounds().width / 5.f
				, 1.414f
				, -1.414f
				, 2.f
			)
			);
			this->bullets.push_back(new Bullet(this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f,
				this->player->getPos().y + this->player->getBounds().width / 5.f
				, 1.414f
				, 1.414f
				, 2.f
			)
			);
			countit++;
		}
	}
}


void game::updateGui()
{
	std::stringstream ss;
	ss <<"Points: " << this->points;
	this->pointText.setString(ss.str());

	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpbar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpbar.getSize().y));

}
void game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		if (bullet->getBounds().left + bullet->getBounds().width>=this->window->getSize().x)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			break;
		}
		++counter;
	}

}

void game::updateItem()
{
	if (creatItem == 1)
	{
		this->items.push_back(new item(this->textureitem["ITEM"],
			rand()%1440/1.f,
			rand()%1080/ 1.f
			, -1.f
			, 0.f
			, 1.f
		)
		);
		creatItem = 0;
	}
	if (creatHeal == 1&&this->player->getHp() < 91)
	{
		this->heals.push_back(new Heal (this->textureheal["HEAL"],
			rand() % 1440 / 1.f,
			rand() % 1080 / 1.f
			, -1.f
			, 0.f
			, 1.f
		)
		);
		creatHeal = 0;
	}
	unsigned counterit = 0;
	 for (auto* item : this->items)
	 {
		 item->update();
		 if (item->getBounds().left  < 0.f)
		 {
			 delete this->items.at(counterit);
			 this->items.erase(this->items.begin() + counterit);
			 break;
		 }
		 ++counterit;
	 }
	 unsigned counterheal = 0;
	 for (auto* heal : this->heals)
	 {
		 heal->update();
		 if (heal->getBounds().left < 0.f)
		 {
			 delete this->heals.at(counterheal);
			 this->heals.erase(this->heals.begin() + counterheal);
			 break;
		 }
		 ++counterheal;
	 }
}
void game::updateEnemies()
{
	this->spawnTimer += 0.25f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand()%this->window->getSize().x+900.f, rand() % this->window->getSize().y - 20.f));
		this->spawnTimer = 0.f;
	}


	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();
	
		if (enemy->getBounds().left <0.f)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			break;
		}
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getPoints()*3);
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			Sound.play();
			break;
		}

		++counter;
	}

}
void game::updateEnemieships()
{
	this->spawnTimerenemyship += 0.25f;
	if (this->spawnTimerenemyship >= this->spawnTimerMaxenemyship)
	{
		this->enemieships.push_back(new Enemyship(rand() % this->window->getSize().x + 900.f, rand() % this->window->getSize().y - 20.f));
		this->spawnTimerenemyship = 0.f;
	}


	unsigned counter = 0;
	for (auto* enemyship : this->enemieships)
	{
		enemyship->update();

		if (enemyship->getBounds().left < 0.f)
		{
			delete this->enemieships.at(counter);
			this->enemieships.erase(this->enemieships.begin() + counter);
			break;
		}
		else if (enemyship->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemieships.at(counter)->getPoints() * 3);
			delete this->enemieships.at(counter);
			this->enemieships.erase(this->enemieships.begin() + counter);
			Sound.play();
			break;
		}

		++counter;
	}

}

void game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_delete = false;
		for (size_t k = 0; k < this->bullets.size()&& enemy_delete==false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints() *100;
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
				enemy_delete = true;
				if (rand() % 10 == 0 && creatItem != 2)
				{
					creatItem = 1;
				}
				if (rand() % 20 == 0 )
				{
					creatHeal = 1;
				}
				Sound.play();

				break;
			}
		}

	}
	for (int i = 0; i < this->enemieships.size(); ++i)
	{
		bool enemyship_delete = false;
		for (size_t k = 0; k < this->bullets.size() && enemyship_delete == false; k++)
		{
			if (this->enemieships[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemieships[i]->getPoints() * 100;
				delete this->enemieships[i];
				this->enemieships.erase(this->enemieships.begin() + i);
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
				enemyship_delete = true;
				if (rand() % 10 == 0 && creatItem != 2)
				{
					creatItem = 1;
				}
				if (rand() % 20 == 0)
				{
					creatHeal = 1;
				}
				Sound.play();
				break;
			}
		}

	}
}
void game::updateReciveitem()
{
		for (size_t k = 0; k < this->items.size() ; k++)
		{
			if (this->player->getBounds().intersects(this->items[k]->getBounds()))
			{
				delete this->items[k];
				this->items.erase(this->items.begin() + k);
				getItem = 1;
				creatItem = 2;
				Sound.play();
				break;
			}
		}
		for (size_t k = 0; k < this->heals.size(); k++)
		{
			if (this->player->getBounds().intersects(this->heals[k]->getBounds()))
			{
				delete this->heals[k];
				this->heals.erase(this->heals.begin() + k);
				this->player->loseHp(-10);
				creatHeal = 0;
				Sound.play();
				break;
			}
		}
}
game::game()
{
	this->initWindow();
	this->initPlayer();
	this->initbullets();
	this->initItem();
	this->initEnemieship();
	this->initEnemies();
	this->initSystem();
	this->initGui();
	this->initWorld();
}
game::~game()
{
	delete this->window;
	delete this->player;
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	for (auto* i : this->bullets)
	{
		delete i;
	}
	for (auto* i : this->enemies)
	{
		delete i;
	}
	for (auto* i : this->enemieships)
	{
		delete i;
	}
	for (auto* i : this->items)
	{
		delete i;
	}
	for (auto* i : this->heals)
	{
		delete i;
	}

}
void game::run()
{
	
	while (this->window->isOpen())
	{	


		if (Menu == 0)
		{
			bgsound.play();
			
			this->updatePollEvents();

			this->window->clear();

			myName.setFont(this->font);
			myName.setOrigin(myName.getGlobalBounds().width/2,myName.getGlobalBounds().height/2);
			myName.setCharacterSize(30);
			myName.setFillColor(sf::Color::Green);
			myName.setString("64010017 Kittayot Sangngam");
			myName.setPosition(200.f,100.f);


			this->window->draw(this->Menubg);
			this->window->draw(this->myName);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				Menu = 1;
			}

			this->window->display();
		}
		if (Menu==1) {
			this->updatePollEvents();
			this->update();
			this->render();
		}
		if (Menu==2)
		{
			bgsound.stop();
			Playername.setPosition(this->window->getSize().x / 2.f, 150.f);
			Playername.setOrigin(Playername.getGlobalBounds().width / 2, Playername.getGlobalBounds().height / 2);
			Playername.setFont(this->font);
			Playername.setCharacterSize(100);
			Playername.setFillColor(sf::Color::White);
			Playername.setString("Enter Your Name");


			PlayernameText.setOrigin(PlayernameText.getGlobalBounds().width / 2, PlayernameText.getGlobalBounds().height / 2);
			PlayernameText.setPosition(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
			PlayernameText.setFillColor(sf::Color::White);
			PlayernameText.setFont(font);
			PlayernameText.setCharacterSize(70);

			Button button("Save", { 170, 50 }, 50, sf::Color::White, sf::Color::Black);
			button.setFont(font);
			button.setPosition(sf::Vector2f(this->window->getSize().x / 2.f, 680.f));
			button.setOrigin(sf::Vector2f(170 / 2, 50 / 2));


			sf::Event event;


			while (this->window->pollEvent(event)) {
				switch (event.type) {

				case sf::Event::Closed:
					this->window->close();
				case sf::Event::TextEntered:
					if (event.text.unicode < 128)
						if (event.text.unicode == 8)
							continue;
					if (event.text.unicode == 13)
						PlayernameText.setString(Playerinput);
					else
						Playerinput += static_cast<char>(event.text.unicode);
					PlayernameText.setString(Playerinput);


				case sf::Event::KeyPressed:

					if (event.key.code == 27) {
						this->window->close();
					}
					if (event.key.code == sf::Keyboard::BackSpace && Playerinput.getSize() != 0)
					{
						Playerinput.erase(Playerinput.getSize() - 1, 1);
						PlayernameText.setString(Playerinput);
					}
				case sf::Event::MouseMoved:
					if (button.isMouseOver(*this->window)) {
						button.setBackColor(sf::Color::Green);
					}
					else {
						button.setBackColor(sf::Color::Red);
					}
					break;
				case sf::Event::MouseButtonPressed:
					if (button.isMouseOver(*this->window)) {
						Sendnametoscore = Playerinput;
						Menu = 3;
					}
					break;
				}



			}
			this->window->clear();
			this->window->draw(this->Scorebg);
			button.drawTo(*this->window);
			this->window->draw(Playername);
			this->window->draw(PlayernameText);
			this->window->display();
		}
		if (Menu == 3)
		{
			this->updatePollEvents();
			fstream myFile;
			myFile.open("scoreandfont/hscore.txt", ios::in);
			if (myFile.is_open())
			{
				string line;
				int y = 0;
				for (int i = 0; i < 5; i++)
				{
					getline(myFile, line);
					stringstream ss1, ss2;
					string t1;
					int num2;
					//cout << line  << "\n";
					string word = "";
					for (auto x : line)
					{

						if (x == ' ')
						{

							playerNamescore[i] = word;
							t1 = playerNamescore[i];
							//cout << t1 << " " << "name" <<" "<< i << endl;


							//cout << word << endl;
							word = "";
						}
						else {
							word = word + x;
						}
					}
					ss2 << word;
					ss2 >> num2;
					Score[i] = num2;
					//cout << score[i] << " " << "score"<<" "<< i << endl;
					//cout << word << endl;

				}
				myFile.close();

			}
			for (int i = 4; i >= 0; i--)
			{
				if (points > Score[i])
				{
					Rank = i;
					//cout << Score[i] << " " << Score[i] << " score \n";
					//cout << Rank << " " << i << " rank \n";
				}
			}
			if (K == 0) {
				for (int e = 4; e >= Rank; e--)
				{
					string q;
					int y = e + 1;
					playerNamescore[y] = playerNamescore[e];
					Score[y] = Score[e];


					q = playerNamescore[y];
					cout << q << endl;

				}


				playerNamescore[Rank] = Sendnametoscore;
				Score[Rank] = points;





				myFile.open("scoreandfont/hscore.txt", ios::out);//write
				if (myFile.is_open())
				{
					string t3, t0, t1, t2, t4;

					t0 = playerNamescore[0];
					t1 = playerNamescore[1];
					t2 = playerNamescore[2];
					t3 = playerNamescore[3];
					t4 = playerNamescore[4];
					//cout << t0 << " " << t1 << " " << t2 << " " << t3 << " " << t4 << endl;
					myFile << t0 << " " << Score[0] << "\n";
					myFile << t1 << " " << Score[1] << "\n";
					myFile << t2 << " " << Score[2] << "\n";
					myFile << t3 << " " << Score[3] << "\n";
					myFile << t4 << " " << Score[4] << "\n";

					myFile.close();

				}
				K++;
			}

				Textscore.setPosition(this->window->getSize().x / 2.f, 80.f);
				Textscore.setOrigin(Textscore.getGlobalBounds().width / 2, Textscore.getGlobalBounds().height / 2);
				Textscore.setFont(this->font);
				Textscore.setCharacterSize(30);
				Textscore.setFillColor(sf::Color::White);
				Textscore.setString("Score Board");

				for (int i = 0; i < 5; i++)
				{
					Playernametext_2[i].setOrigin(Textscore.getGlobalBounds().width / 2, Textscore.getGlobalBounds().height / 2);
					Playernametext_2[i].setFont(this->font);
					Playernametext_2[i].setCharacterSize(30);
					Playernametext_2[i].setFillColor(sf::Color::White);
					Playernametext_2[i].setString(playerNamescore[i]);
				}
				Playernametext_2[0].setPosition((this->window->getSize().x / 3.f) + 75, 220.f);
				Playernametext_2[1].setPosition((this->window->getSize().x / 3.f) + 75, 295.f);
				Playernametext_2[2].setPosition((this->window->getSize().x / 3.f) + 75, 370.f);
				Playernametext_2[3].setPosition((this->window->getSize().x / 3.f) + 75, 445.f);
				Playernametext_2[4].setPosition((this->window->getSize().x / 3.f) + 75, 520.f);


				for (int i = 0; i < 5; i++)
				{

					Playerscore[i].setOrigin(Playerscore[i].getGlobalBounds().width / 2, Playerscore[i].getGlobalBounds().height / 2);
					Playerscore[i].setFont(this->font);
					Playerscore[i].setCharacterSize(70);
					Playerscore[i].setFillColor(sf::Color::White);

					//string t10;

					string t10 = to_string(Score[i]);


					Playerscore[i].setString(t10);
				}
				Playerscore[0].setPosition((this->window->getSize().x * 2 / 3.f) + 75, 220.f);
				Playerscore[1].setPosition((this->window->getSize().x * 2 / 3.f) + 75, 295.f);
				Playerscore[2].setPosition((this->window->getSize().x * 2 / 3.f) + 75, 370.f);
				Playerscore[3].setPosition((this->window->getSize().x * 2 / 3.f) + 75, 445.f);
				Playerscore[4].setPosition((this->window->getSize().x * 2 / 3.f) + 75, 520.f);

				tryagain.setPosition(this->window->getSize().x / 2.f, 800.f);
				tryagain.setOrigin(tryagain.getGlobalBounds().width / 2, tryagain.getGlobalBounds().height / 2);
				tryagain.setFont(this->font);
				tryagain.setCharacterSize(20);
				tryagain.setFillColor(sf::Color::White);
				tryagain.setString("Press T totryagain");

				this->window->clear();
				this->window->draw(this->Scorebg);
				this->window->draw(this->Playernametext_2[0]);
				this->window->draw(this->Playernametext_2[1]);
				this->window->draw(this->Playernametext_2[2]);
				this->window->draw(this->Playernametext_2[3]);
				this->window->draw(this->Playernametext_2[4]);

				this->window->draw(this->Playerscore[0]);
				this->window->draw(this->Playerscore[1]);
				this->window->draw(this->Playerscore[2]);
				this->window->draw(this->Playerscore[3]);
				this->window->draw(this->Playerscore[4]);

				this->window->draw(this->Textscore);
				this->window->draw(this->tryagain);

			
				
				this->window->display();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				{
					Menu = 0;
					reset();
					K = 0;
					Rank = 5;
				}
				
		}

	}
}
void game::update()
{
	this->updateInput();
	this->updateItem();
	this->updateReciveitem();
	this->updateGui();
	this->player->update();
	this->updateCollision();
	this->updateBullets();
	this->updateEnemies();
	this->updateEnemieships();
	this->updateCombat();
	this->updateWorld();
	this->updategameover();
}
void game::updateWorld()
{
	deltaTime = clock.restart().asSeconds();
	if (deltaTime > 1.0f / 30.0f)
		deltaTime = 1.0f / 30.0f;
}
void game::updateCollision()
{
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left,this->window->getSize().y-this->player->getBounds().height);
	}



}

void game::updategameover()
{
	
	if(this->player->getHp() > 0)gameover = false;
	else if (this->player->getHp() <= 0) {
		gameover = true; Menu = 2;
	}
}


void game::updatestate()
{
}
void game::render()
{
		this->window->clear();
		if (!gameover)
		{
			for (BG& background : Backgrounds)
				background.Update(deltaTime);

			for (BG& background : Backgrounds)
				background.Draw(*window);

		}
		if (!gameover) {
			this->player->render(*this->window);
			for (auto* bullet : this->bullets)
			{
				bullet->render(this->window);
			}
			for (auto* enemy : this->enemies)
			{
				enemy->render(this->window);
			}
			for (auto* item : this->items)
			{
				item->render(this->window);
			}
			for (auto* enemyship : this->enemieships)
			{
				enemyship->render(this->window);
			}
			for (auto* heal : this->heals)
			{
				heal->render(this->window);
			}

		}


		if (!gameover) {
			this->window->draw(this->pointText);
			this->window->draw(this->playerHpbarBack);
			this->window->draw(this->playerHpbar);
		}
		this->window->display();

}

void game::reset()
{
	this->player->setPosition(20.f, 500.f);
	this->player->loseHp(-100);
	

	this->count = 0.f;

	this->countenemyship = 0.f;
	this->points = 0;
	this->getItem = 0;
	this->creatItem = 0;
	this->countit=0;

	this->getHeal = 0;
	this->creatHeal = 0;
	this->countHeal=0;

	this->deltaTime = 0.0f;
	this->gameover = false;

	enemies.clear();
	enemieships.clear();
	items.clear();
	heals.clear();
	bullets.clear();
}






