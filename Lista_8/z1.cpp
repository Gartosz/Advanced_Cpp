#include <mutex>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>

namespace cpplab
{
    class FuelTank
    {
        public:
        FuelTank(unsigned int fuel_base) : fuel_level(fuel_base) {}

        unsigned int refuel(unsigned int requested_fuel)
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (requested_fuel > fuel_level)
                return 0;
            fuel_level -= requested_fuel;
            return requested_fuel;
        }
        private:
        unsigned int fuel_level = 0;
        std::mutex mutex;
    };

    class Engine
    {
        public:
        Engine(size_t interval_ms_, unsigned int fuel_consumption_) : 
               interval_ms(std::chrono::milliseconds(interval_ms_)), fuel_consumption(fuel_consumption_) {}

        ~Engine()
        {
            std::cout << "Engine on thread " << engine_thread.get_id() << " used " << consumed_fuel << " of fuel.\n";
            engine_thread.join();
        }

        void connect_fuel_tank(std::shared_ptr<FuelTank> fuel_tank)
        {
            fuel_tanks.emplace_back(fuel_tank);
        }

        void start()
        {
            std::cout << "Engine started.\n";
            engine_thread = std::thread(&cpplab::Engine::run, this);
        }

        private:
        std::vector<std::shared_ptr<FuelTank>> fuel_tanks;
        std::chrono::milliseconds interval_ms = std::chrono::milliseconds(0);
        unsigned int fuel_consumption = 0;
        std::thread engine_thread;
        unsigned int consumed_fuel = 0;
        void run()
        {
            do
            {
                std::this_thread::sleep_for(interval_ms);
                for (auto fuel_tank = fuel_tanks.begin(); fuel_tank < fuel_tanks.end(); ++fuel_tank)
                {
                    if ((*fuel_tank)->refuel(fuel_consumption))
                    {
                        consumed_fuel += fuel_consumption;
                        fuel_tank = fuel_tanks.end();
                    }
                    else
                        fuel_tanks.erase(fuel_tank);
                }
            } while (!fuel_tanks.empty());
        }
    };
}

int main()
{
    std::vector<std::shared_ptr<cpplab::Engine>> engines;
    engines.emplace_back(std::make_shared<cpplab::Engine>(2000, 5));
    engines.emplace_back(std::make_shared<cpplab::Engine>(1000, 1));
    engines.emplace_back(std::make_shared<cpplab::Engine>(3000, 2));
    std::srand(time(NULL));
    std::vector<std::shared_ptr<cpplab::FuelTank>> tanks;
    for (int i = 0; i < 10; ++i)
    {
        tanks.emplace_back(std::make_shared<cpplab::FuelTank>(std::rand() % 10 + 10));
    }

    for (auto &engine : engines)
    {
        for (auto &tank : tanks)
            engine->connect_fuel_tank(tank);
        engine->start();
    }

    return 0;
}