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
  float width = 170.f;
  float height = 20.f;

  this->hpBarBg.setSize(sf::Vector2f(width, height));
  this->hpBarBg.setFillColor(sf::Color(50, 50, 50, 200));
  this->hpBarBg.setPosition(20.f, 20.f);

  this->hpBarFill.setSize(sf::Vector2f(width, height));
  this->hpBarFill.setFillColor(sf::Color(250, 20, 20, 200));
  this->hpBarFill.setPosition(this->hpBarBg.getPosition());
}

/* CONSTRUCTOR AND DESTRUCTOR */

PlayerGUI::PlayerGUI(Player *player)
{
  this->player = player;
  this->initFont();
  this->initHpBar();
}

PlayerGUI::~PlayerGUI()
{
}

/* FUNCTIONS */

void PlayerGUI::update(const float &dt)
{
}

void PlayerGUI::render(sf::RenderTarget &target)
{
  this->renderHpBar(target);
}

void PlayerGUI::updateHpBar()
{
}

void PlayerGUI::renderHpBar(sf::RenderTarget &target)
{
  target.draw(this->hpBarBg);
  target.draw(this->hpBarFill);
}
