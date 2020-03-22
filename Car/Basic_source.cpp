// custom countdown using while
#include <iostream>
#include "Auxiliary.h"
#include<thread>
#include<conio.h>
#include<windows.h>


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

		double give_fuel(double amount, unsigned int speed)
		{
			if (1 < speed && speed < 60) amount = 0.002;
			if (61 < speed && speed < 100) amount = 0.014;
			if (101 < speed && speed < 140) amount = 0.002;
			if (141 < speed && speed < 200) amount = 0.0025;
			if (201 < speed && speed < 250) amount = 0.003;
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
		double consumption; // –асход
		double consumption_per_second; // –асход в секунду
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

		std::thread main_thread; //поток управление потоками
		std::thread acceliration_thread; // ускорение
		std::thread free_wheeling_thread; // машина в движении


	} control;

	
	bool driver_inside = false;

	bool gas_pedal;
	bool break_pedal;
	unsigned int speed;
	unsigned int max_speed;

	

public:
	const Engine& get_engine() const {return this->engine; }
	const Tank& get_tank() const {return this->tank; }
	const unsigned int& get_speed() const { return speed; }
	void fill(double fuel) { tank.fill(fuel); }

	void get_in()
	{
		driver_inside = true;
		control.panel_thread = std::thread(&Car::panel, this);
	}
	void get_out()
	{	
		driver_inside = false;
		if (control.panel_thread.joinable()) control.panel_thread.join();	
		system("cls");
	}

	void panel() 
	{
		while (driver_inside)
		{
			system("cls");
			std::cout << "Engine is "; /* << (engine.Started() ? "started" : "stoped") << ".\n";*/
			
			if  (engine.Started())
			{
				Text_color(10);
				std::cout << "started.\n";
				Text_color(7);
			}
			else
			{
				Text_color(12);
				std::cout <<  "stoped.\n";
				Text_color(7);

			}
			std::cout << "Fuel level: " << tank.get_fuel() << std::endl;
			std::cout << "Speed:      " << speed << " km/h" << std::endl;

			if (tank.get_fuel() < 5)
			{				
			 	Text_color(12);
				std::cout << "LOW FUEL!" << std::endl;
				Text_color(7);
			}
				
			std::this_thread::sleep_for(1s);
			if (tank.get_fuel() == 0) stop();
				//if (control.engine_idle_thread.joinable()) control.engine_idle_thread.join();
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
		if (control.engine_idle_thread.joinable()) control.engine_idle_thread.join();
	}

	void engine_idle()
	{
		while (engine.Started() && tank.give_fuel(engine.get_consumption_per_second(),get_speed()))
		{
			std::this_thread::sleep_for(1s);			
		}
		/*if (tank.get_fuel() == 0)*/ engine.stop();
		
	}


	void info() const
	{
		engine.info();
		W_line();
		tank.info();
		W_line();
	}

	Car(double engine, unsigned int tank, unsigned max_speed = 250) :engine(engine), tank(tank)
	{
		driver_inside = false;
		gas_pedal = false;
		break_pedal = false;
		speed = 0;
		this->max_speed = max_speed<= 350 ? max_speed : max_speed;
		std::cout << "You car is ready to go:-)\n";

		control.main_thread = std::thread(&Car::ControlCar, this);
	}

	~Car()
	{
		if (control.main_thread.joinable()) control.main_thread.join();
		std::cout << "Don't leave me alone.\n";
	}

	void ControlCar()
	{
		try
		{
			char key;
			do
			{
				key = _getch();
				switch (key)
				{
				case 13:
					if (driver_inside)this->get_out();
					else this->get_in();
					break;
				case 'i':case 'I': //Ignitton

					if (!this->get_engine().Started())this->start();
					else this->stop();
					break;
				case 'f':
					double amount;
					std::cout << "How match?: ";
					std::cin >> amount;
					this->fill(amount);
					break;
				case 'w':case 'W':
					std::this_thread::sleep_for(0.6s);
					if (engine.Started())
						if (speed < max_speed)
						{
							speed += 10;							
						}
						else speed = max_speed;
					
					break;
				case 's':case 'S':
					if (speed > 20) speed -= 20;
					else speed = 0;
					break;
				case 27:
					this->stop();
					this->get_out();
					break;
				}
				std::this_thread::sleep_for(0.1s);
				if (!control.free_wheeling_thread.joinable() && speed >0) control.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
				else if (control.free_wheeling_thread.joinable()&& speed == 0) control.free_wheeling_thread.join();
			} while (key != 27);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	
	void free_wheeling()
	{
		while (speed > 0)
		{
			speed--;
			std::this_thread::sleep_for(1s);
		}
	}
};



int main()
{
	setlocale(LC_ALL, "Russian");

	Car car(8,40);	
	std::cout << "Press Enter to get in";
	
}
