#ifndef MENU_H_
#define MENU_H_

bool loadMenu();

bool loadMenuScreen();

void menuHoverButton(int x, int y);

void hoverOneButton(int x, int y);

void oneButtonClicked(int x, int y);

void hoverTwoButton(int x, int y);

void twoButtonClicked(int x, int y);

void renderMenuButton();

void renderChose1Button();

void renderChose2Button();

#endif