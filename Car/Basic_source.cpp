// custom countdown using while
#include <iostream>
#include "Auxiliary.h"
#include<thread>
#include<conio.h>


using namespace std::literals::chrono_literals;




class Car
{
	class Tank
	{
		unsigned int volume; // LITAJ
		double fuel; // Level of fuel

	public:
		// GETS
		unsigned int get_volume() const { return this->volume; }
		double get_fuel() const { return this->fuel; }
		Tank(unsigned int volume) :volume(volume >= 20 && volume <= 100 ? volume : throw std::exception("Error: Bad tank volume")), fuel(0)
		{
			std::cout << "Tank is ready:\t" << this << std::endl;
		}
		// Metods
		void fill(double fuel)
		{
			if (fuel >= 0)
			{
				this->fuel += fuel;
				if (this->fuel >= volume) this->fuel = volume;
			}
		}

		double give_fuel(double amount)
		{
			fuel -= amount;
			if (fuel <= 0)fuel = 0;
			return fuel;
		}
		void info() const
		{
			std::cout << "Tank volume:\t" << volume << " liters. \n";
			std::cout << "Fuel level:\t" << fuel << " liters. \n";
		}

		~Tank()
		{
			std::cout << "Tank crashed:\t" << this << std::endl;
		}

	} tank;

	class Engine
	{
		bool started;
		double consumption; // Расход
		double consumption_per_second; // Расход в секунду
	public:
		bool Started() const { return started; }
		double get_comsumtion() const { return consumption; }
		double get_consumption_per_second() { return consumption_per_second; }
		//SET
		/*void set_comsumption(double consumption)
		{
			this->consumption = consumption >= 3 && consumption <= 30 ? consumption : throw std::exception("Error: Bad comsumption");
		}*/
		void start() { started = true; }
		void stop() { started = false; }

		void info() const
		{
			std::cout << "Engine is " << (started ? "started" : "stoped") << ".\n";
			std::cout << "Consumption is: " << consumption << " L/100km\n";
			std::cout << "consumption_per_second is: " << consumption_per_second << " L/1s.\n";
		}


		Engine(double consumption) :consumption(consumption >= 3 && consumption <= 30 ? consumption : throw std::exception("Error: Bad comsumption")),
			consumption_per_second(consumption / 10000),
			started(false)
		{
			std::cout << "Engine installed:\t" << this << std::endl;
		}
		~Engine()
		{
			std::cout << "Engine crashed:\t" << this << std::endl;
		}
	} engine;

	struct Control
	{
		std::thread panel_thread;
		std::thread engine_idle_thread;
	} control;

	bool driver_inside = false;

public:
	const Engine& get_engine() const {return this->engine; }
	const Tank& get_tank() const {return this->tank; }

	void fill(double fuel) { tank.fill(fuel); }

	void get_in()
	{
		driver_inside = true;
		control.panel_thread = std::thread(&Car::panel, this);
	}
	void get_out()
	{	
		driver_inside = false;
		control.panel_thread.join();	
	}

	void panel() const
	{
		while (driver_inside)
		{
			system("cls");
			std::cout << "Engine is " << (engine.Started() ? "started" : "stoped") << ".\n";
			std::cout << "Fuel level: " << tank.get_fuel() << std::endl;
			std::this_thread::sleep_for(1s);
		}
	}

	void start() 
	{
		if (tank.get_fuel())
		{
			engine.start();
			control.engine_idle_thread = std::thread(&Car::engine_idle, this);
		}
		else std::cout << "No fuel\n";
	}


	void stop()
	{
		engine.stop();
		control.engine_idle_thread.join();
	}
	void engine_idle()
	{
		while (engine.Started() && tank.give_fuel(engine.get_consumption_per_second()))
		{
			std::this_thread::sleep_for(1s);			
		}
	}


	void info() const
	{
		engine.info();
		W_line();
		tank.info();
		W_line();
	}

	Car(double engine, unsigned int tank) :engine(engine), tank(tank)
	{
		std::cout << "You car is ready to go:-)\n";
	}

	~Car()
	{
		std::cout << "Don't leave me alone.\n";
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	Car car(8,40);	
	

	std::cout << "Press Enter to get in";
	std::cin.get();
	car.get_in();

	char key;

	do
	{
		key = _getch();
		switch (key)
		{
		case 13:
			if (!car.get_engine().Started())car.start();
			else car.stop();
			break;
		case 'f':
			double amount;
			std::cout << "How match?: ";
			std::cin >> amount;
			car.fill(amount);
			break;
		case 27:
			car.stop();
			car.get_out();
		}
	} while (key != 27);
}
