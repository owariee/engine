#pragma once

#include <Windows.h>
#include <string>

class Window
{
private:
	HWND hWnd;
	std::string className;
	std::string title;

	static LRESULT CALLBACK RedirectPointer(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK RedirectMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	Window(int x, int y, int width, int height, const char className[], const char title[]);
	~Window();

	void setTitle(const char title[]);
	const char* getTitle();
	const char* getClassName();
	HWND* getHandle();
};
