#include <mutex>
#include <vector>
#include <memory>
#include <chrono>

namespace cpplab
{
    class FuelTank
    {
        public:
        unsigned int fuel_level = 0;
        FuelTank(unsigned int fuel_base)
        {
            fuel_level = fuel_base;
        }

        unsigned int refuel(unsigned int requested_fuel)
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (requested_fuel > fuel_level)
                return 0;
            fuel_level -= requested_fuel;
            return requested_fuel;
        }
        private:
        std::mutex mutex;
    };

    class Engine
    {
        public:
        std::vector<std::shared_ptr<FuelTank>> fuel_tanks;
        std::chrono::milliseconds interval_ms = std::chrono::milliseconds(0);
        unsigned int fuel_consumption = 0;

        Engine(size_t interval_ms_, unsigned int fuel_consumption_)
        {
            interval_ms = std::chrono::milliseconds(interval_ms_);
            fuel_consumption = fuel_consumption_;
        }

        void connect_fuel_tank(std::shared_ptr<FuelTank> fuel_tank)
        {
            fuel_tanks.emplace_back(fuel_tank);
        }
    };
}

int main()
{
    return 0;
}