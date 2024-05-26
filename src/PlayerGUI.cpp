#include "stdafx.h"
#include "PlayerGUI.h"

/* INITIALIZERS */

void PlayerGUI::initFont()
{
	if (!this->font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
	{
		throw std::runtime_error("PLAYERGUI::INITFONT::ERR::COULD_NOT_LOAD_FONT");
	}
}

void PlayerGUI::initLevelBar()
{
	this->levelBar = new gui::SolidBar(20.f, 20.f, 30.f, 30.f,
									   sf::Color(20, 20, 250, 200), sf::Color::White,
									   this->font, 14);
}

void PlayerGUI::initHpBar()
{
	this->hpBar = new gui::ProgressBar(20.f, 60.f, 250.f, 30.f,
									   sf::Color(50, 50, 50, 200), sf::Color(250, 20, 20, 200),
									   this->font, sf::Color::White, 14);
}

void PlayerGUI::initExpBar()
{
	this->expBar = new gui::ProgressBar(20.f, 100.f, 200.f, 20.f,
										sf::Color(50, 50, 50, 200), sf::Color(20, 250, 20, 200),
										this->font, sf::Color::White, 14);
}

/* CONSTRUCTOR AND DESTRUCTOR */

PlayerGUI::PlayerGUI(Player *player)
{
	this->player = player;
	this->initFont();
	this->initLevelBar();
	this->initHpBar();
	this->initExpBar();
}

PlayerGUI::~PlayerGUI()
{
	delete this->levelBar;
	delete this->hpBar;
	delete this->expBar;
}

/* FUNCTIONS */

void PlayerGUI::update(const float &dt)
{
	this->updateLevelBar();
	this->updateHpBar();
	this->updateExpBar();
}

void PlayerGUI::render(sf::RenderTarget &target)
{
	this->levelBar->render(target);
	this->hpBar->render(target);
	this->expBar->render(target);
}

void PlayerGUI::updateLevelBar()
{
	this->levelBar->setString(std::to_string(this->player->getAttributeComponent()->level));
}

void PlayerGUI::updateHpBar()
{
	// Calculate the percentage of the health.
	float percent = static_cast<float>(this->player->getAttributeComponent()->hp) /
					static_cast<float>(this->player->getAttributeComponent()->hpMax);

	std::stringstream hpBarText;
	hpBarText << this->player->getAttributeComponent()->hp << " | " << this->player->getAttributeComponent()->hpMax;

	this->hpBar->setString(hpBarText.str());
	this->hpBar->setProgressPercent(percent);
}

void PlayerGUI::updateExpBar()
{
	// Calculate the percentage of the exp.
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) /
					static_cast<float>(this->player->getAttributeComponent()->expNext);

	std::stringstream expBarText;
	expBarText << this->player->getAttributeComponent()->exp << " | " << this->player->getAttributeComponent()->expNext;

	this->expBar->setString(expBarText.str());
	this->expBar->setProgressPercent(percent);
}