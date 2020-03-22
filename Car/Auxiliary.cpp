#include "Auxiliary.h"

//РЕАЛИЗАЦИЯ ВСПОМОГАТЕЛЬНЫХ ФУНКЦИЙ
// Прорисовка белой линии
void W_line()
{
	//std::cout << std::endl << "\r";
	for (int zz = 1; zz <= 80; zz++)
	{
		setlocale(LC_ALL, "C");
		std::cout << "-"; //char(220);
		setlocale(LC_ALL, "");
	}
	std::cout << std::endl;
}
// Завершающая надпись
void End()
{
	system("cls");
	std::cout << "\t\t\t\t";
	for (int zz = 1; zz <= 25; zz++)
	{
		setlocale(LC_ALL, "C");
		std::cout << char(220);
	}
	std::cout << "\n\t\t\t";
	for (int zz = 1; zz <= 8; zz++)
	{
		setlocale(LC_ALL, "C");
		std::cout << char(220);
	}
	std::cout << char(219);
	setlocale(LC_ALL, "");
	std::cout << "  CПАСИБО ЗА ВНИМАНИЕ  ";
	setlocale(LC_ALL, "C");
	std::cout << char(219);
	for (int zz = 1; zz <= 8; zz++)
	{
		setlocale(LC_ALL, "C");
		std::cout << char(220);
	}
	std::cout << "\n\t\t\t\t";
	std::cout << char(219);
	for (int zz = 1; zz <= 23; zz++)
	{
		setlocale(LC_ALL, "C");
		std::cout << char(220);
	}
	std::cout << char(219);
}

//Размер шрифта
void Font(int a)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = a;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;	
	wcscpy_s(cfi.FaceName/*, LF_FACESIZE*/, L"Console"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);


}
// Мигание текста


void Blink()
{
	std::cout << std::endl;
	for (int zz = 1; zz <= 10; zz++)
	{

		system("color 0C");
		Sleep(1000);
		system("color 0E");
		Sleep(1000);
		system("color 0A");
		Sleep(1000);
	}
	std::cout << std::endl;
}