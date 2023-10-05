#include "../../../Headers/ConsoleMenu/ConsoleMenu.h"

Menu::FunctionCase::FunctionCase(const string title, KEY key, function<void()> ExeFunc)
{
	this->title = title;
	this->code = char(key);
	this->ExeFunc = ExeFunc;
}

Menu* Menu::FunctionCase::Do() { ExeFunc(); return nullptr; }

Menu::SubMenuCase::SubMenuCase(const string title, KEY key, Menu* SubMenu)
{
	this->title = title;
	this->code = char(key);
	this->SubMenu = SubMenu;
}

Menu* Menu::SubMenuCase::Do() { return SubMenu; }

Menu::Menu() {
	for (int i = 0; i < 256; ++i)
		this->menu[i] = nullptr;
}

void Menu::push_case(string title, KEY key, function<void()> ExeFunc) {
	if (menu[char(key)]) throw DuplicateKey("Duplicate Key!!!", char(key));
	menu[char(key)] = new FunctionCase(title, key, ExeFunc);
}

void Menu::push_case(string title, KEY key, Menu* SubMenu) {
	if (menu[char(key)]) throw DuplicateKey("Duplicate Key!!!", char(key));
	menu[char(key)] = new SubMenuCase(title, key, SubMenu);
}

void Menu::start(Menu* menu) {
	while (true) {
		system("cls");
		std::cout << "Esc) BACK/EXIT" << std::endl;
		for (int i = 0; i < 256; ++i)
			if (menu->menu[i] && i != 48)
				std::cout << menu->menu[i]->title << std::endl;
		if (menu->menu[48])
			std::cout << menu->menu[48]->title << std::endl;
		char choice = _getch();
		std::cout << std::endl;
		if (choice == char(KEY::Esc))
			break;
		if (!menu->menu[choice]) {
			std::cout << "Unknown key!!! Press something for continue...";
			_getch();
		}
		else {
			auto SubMenu = menu->menu[choice]->Do();
			if (SubMenu) start(SubMenu);
		}
	}
}
