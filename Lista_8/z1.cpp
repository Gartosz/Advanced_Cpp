#include <mutex>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>

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
            std::cout << "Engine used " << consumed_fuel << " of fuel.\n";
            engine_thread.join();
        }

        void connect_fuel_tank(std::shared_ptr<FuelTank> fuel_tank)
        {
            fuel_tanks.emplace_back(fuel_tank);
        }

        void start()
        {
            engine_thread = std::thread(&run, this);
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
    std::shared_ptr<cpplab::FuelTank> tank = std::make_shared<cpplab::FuelTank>(10);
    cpplab::Engine engine(800, 4);
    engine.connect_fuel_tank(tank);
    engine.start();

    return 0;
}