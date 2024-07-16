#ifndef ASCII_DISPLAY_H
#define ASCII_DISPLAY_H

#include <string>

#if defined(_WIN32)
#include <windows.h>

class Window
{
public:
    const std::string brightness = " .,-~:;=!*#$@";
    int width, height;

    Window(int x, int y){
        width = x;
        height = y;
        screen = new char[width*height];
        SetConsoleActiveScreenBuffer(hConsole);
        cls();
        ref();
    }

    void draw(int x, int y, int b){
        screen[y*width + x] = brightness[b];
    }

    void drawc(int x, int y, char c){
        screen[y*width + x] = c;
    }

    void ref(){
        WriteConsoleOutputCharacterA(hConsole, screen, width * height, { 0,0 }, &dwBytesWritten);
    }

    void cls(){
        for (int i = 0; i < width*height; i++) {
            screen[i] = ' ';
        }
    }
private:
    char *screen;
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    DWORD dwBytesWritten = 0;
};
#elif defined(__APPLE__) || defined(__linux__)

#include <ncurses.h>

class Window {
public:
    const std::string brightness = " .,-~:;=!*#$@";
    int width, height;

    Window(int x, int y)
    {
        initscr();
        cbreak();
        curs_set(0);
        refresh();
        width = x;
        height = y;
    }

    ~Window()
    {
        endwin();
    }

    void draw(int x, int y, int b)
    {
        if (0 <= x && 0 <= y && 0 <= b && x < width && y < height && b < 13)
        {
            mvaddch(y, x, brightness[b]);
        }
    }

    void drawc(int x, int y, char c)
    {
        if (0 <= x && 0 <= y && x < width && y < height)
        {
            mvaddch(y, x, c);
        }
    }

    void ref()
    {
        refresh();
    }

    void cls()
    {
        erase();
    }
};

#endif

#endif
