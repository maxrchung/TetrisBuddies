#include "ProfileScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"
#include "ClientManager.h"

ProfileScreen::ProfileScreen()
	:
    backSection(new Section(0.0f,
                            12.5f,
                            420.0f,
                            595.0f,
                            GraphicsManager::getInstance()->buttonColor,
                            true)),

	section(new Section(0.0f,
	                     12.5f,
						 400.0f,
						 575.0f)),

    title(new TextBox("PROFILE",
	                   0.0f,
					   -200.0f,
					   300.0f,
					   Alignments::CENTER,
                       true)),
                       
	status(new TextBox("View your profile stats here. Press back to return to the home menu.",
	                    0.0f,
						-125.0f,
						300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

	usernameTag(new TextBox("Username:",
						    -100.0f,
                            -50.0f,
                            150.0f,
						    Alignments::LEFT)),

	nameTag(new TextBox("maxisagod",
						50.0f,
						-50.0f,
						250.0f,
						Alignments::LEFT)),

	highscoreTag(new TextBox("High score:",
						 -100.0f,
						 0.0f,
						 250.0f,
						 Alignments::LEFT)),

	hsTag(new TextBox("0",
						 50.0f,
						 0.0f,
						 250.0f,
						 Alignments::LEFT)),

	gamesplayedTag(new TextBox("Games played: ",
						 -100.0f,
						 50.0f,
						 250.0f,
						 Alignments::LEFT)),

	gpTag(new TextBox("0",
						 50.0f,
						 50.0f,
						 250.0f,
						 Alignments::LEFT)),

	gameswonTag(new TextBox("Games Won: ",
						 -100.0f,
						 100.0f,
						 250.0f,
						 Alignments::LEFT)),

	gwTag(new TextBox("0",
						 50.0f,
						 100.0f,
						 250.0f,
						 Alignments::LEFT)),

	winpercentageTag(new TextBox("Win percentage: ",
						 -100.0f,
						 150.0f,
						 250.0f,
						 Alignments::LEFT)),

	wpTag(new TextBox("0",
						 50.0f,
						 150.0f,
						 250.0f,
						 Alignments::LEFT)),

	home(new Button(Screens::HOME,
                    "Back",
                    0.0f,
                    225.0f,
                    150.0f,
                    50.0f))
{
    UIElements.push_back(backSection);
    UIElements.push_back(section);
    UIElements.push_back(title);
    UIElements.push_back(status);
	UIElements.push_back(usernameTag);
	UIElements.push_back(highscoreTag);
	UIElements.push_back(gameswonTag);
	UIElements.push_back(gamesplayedTag);
	UIElements.push_back(winpercentageTag);
	UIElements.push_back(nameTag);
	UIElements.push_back(hsTag);
	UIElements.push_back(gwTag);
	UIElements.push_back(gpTag);
	UIElements.push_back(wpTag);
    UIElements.push_back(home);

    selectables = { home };
}
void ProfileScreen::reload()
{
    std::string username = ClientManager::getInstance().player.username;
    std::cout << "this is my username:  " << username << std::endl;
    nameTag->message.setString(ClientManager::getInstance().player.username);
    hsTag->message.setString(std::to_string(ClientManager::getInstance().player.highScore));
    gpTag->message.setString(std::to_string(ClientManager::getInstance().player.gamesPlayed));
    gwTag->message.setString(std::to_string(ClientManager::getInstance().player.gamesWon));
    wpTag->message.setString(std::to_string(ClientManager::getInstance().player.getWinRate()).substr(0, 5));
	std::cout <<  ClientManager::getInstance().player.winPercentage << std::endl;
}


void ProfileScreen::update()
{
    Screen::update();

    if (home->isActivated ||
        (InputManager::getInstance()->enter && home->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(home->toScreen);
    }
}

void ProfileScreen::draw()
{
    Screen::draw();
}