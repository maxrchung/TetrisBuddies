#include <iostream>

class Screen
{
public:
	void testa();
};

void Screen::testa()
{
	std::cout << "asdf" << std::endl;
}

class LoginScreen : public Screen
{
public:
	LoginScreen();
	void testa();
};

LoginScreen::LoginScreen()
{
	std::cout << "b" << std::endl;
}

void LoginScreen::testa()
{
	std::cout << "testb" << std::endl;
}

int main()
{
	Screen* screen = new LoginScreen;
	LoginScreen loginScreen;
	Screen& screen2 = LoginScreen();

	loginScreen.testa();
	

	while(true) {}
	return 0;
}