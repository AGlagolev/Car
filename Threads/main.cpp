#include<iostream>
#include<thread>

using namespace std::literals::chrono_literals;

static bool finish = false;

void What()
{
	while (!finish)
	{
		std::cout << "What a f*uck ";
		std::this_thread::sleep_for(1s);
	}
}
void Is()
	{
		
		while (!finish)
		{
			std::cout << "Is going on?\n";
			std::this_thread::sleep_for(1s);
		}
	}

void main()
{
	std::thread thread_what(What);
	std::thread thread_is(Is);

	std::cin.get(); // Ожидает нажатие клавиши Enter. Нажатие остальных клавиш игнорирует
	finish = true;

	thread_what.join();
	thread_is.join();
}