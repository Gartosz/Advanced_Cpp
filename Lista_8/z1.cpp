#include <mutex>
#include <vector>
#include <memory>

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