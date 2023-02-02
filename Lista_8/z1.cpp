namespace cpplab
{
    class FuelTank
    {
        unsigned int fuel_level = 0;
        FuelTank(unsigned int fuel_base)
        {
            fuel_level = fuel_base;
        }

        unsigned int refuel(unsigned int requested_fuel)
        {
            if (requested_fuel > fuel_level)
                return 0;
            fuel_level -= requested_fuel;
            return requested_fuel;
        }
    };

    class Engine
    {

    };
}

int main()
{
    return 0;
}