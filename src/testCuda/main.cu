#include "ElectricField.cuh"

int main()
{
	ElectricField eField(0., 10., 2., 24., 100., 100.);
	std::cout << eField.getEvalue(3., 10.) << std::endl;
	return 0;
}
