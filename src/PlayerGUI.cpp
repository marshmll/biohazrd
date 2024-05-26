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

void PlayerGUI::initHpBar()
{
	this->hpBar = new gui::ProgressBar(20.f, 20.f, 250, 30,
									   sf::Color(20, 20, 20, 200), sf::Color(250, 20, 20, 200),
									   this->font, 14, "");
}

void PlayerGUI::initExpBar()
{
	this->expBar = new gui::ProgressBar(20.f, 70.f, 250, 30,
										sf::Color(20, 20, 20, 200), sf::Color(20, 250, 20, 200),
										this->font, 14, "");
}

/* CONSTRUCTOR AND DESTRUCTOR */

PlayerGUI::PlayerGUI(Player *player)
{
	this->player = player;
	this->initFont();
	this->initHpBar();
	this->initExpBar();
}

PlayerGUI::~PlayerGUI()
{
	delete this->hpBar;
	delete this->expBar;
}

/* FUNCTIONS */

void PlayerGUI::update(const float &dt)
{
	this->updateHpBar();
	this->updateExpBar();
}

void PlayerGUI::render(sf::RenderTarget &target)
{
	this->hpBar->render(target);
	this->expBar->render(target);
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