#include "game.hpp"

#include "Scene_Menu.hpp"

const unsigned int Game::W  = 800;
const unsigned int Game::H = 800;
const std::string Game::title = "TB-RPG";

Game::Game() {}
Game::~Game() {}

void Game::run()
{
  init();
  loop();
}

void Game::init()
{
  _window.create(sf::VideoMode(W, H), title);
  _window.setFramerateLimit(60);
  _window.setKeyRepeatEnabled(false);

  _sceneHandler.addScene(std::unique_ptr<Scene>(new Scene_Menu(_sceneHandler, _resources)));

  _sceneHandler.init();

  _clock.restart();
}

void Game::loop()
{
  while (_window.isOpen())
  {
    handleEvents();
    update();
    draw();

    _sceneHandler.applySceneRequests();
    if(_sceneHandler.exitRequest()) _window.close();
  }
}

void Game::update()
{
  sf::Time deltatime;
  deltatime = _clock.restart();

  _sceneHandler.activeScene().update(deltatime);
}

void Game::draw()
{
  _window.clear(sf::Color::Black);

  _sceneHandler.activeScene().draw(_window);

  _window.display();
}

void Game::handleEvents()
{
  sf::Event event;
  while (_window.pollEvent(event))
  {
    switch(event.type)
    {
      case sf::Event::Closed:
        _window.close();
        break;
        
      default:
        break;
    }

    _sceneHandler.activeScene().handleEvents(event);
  }
}