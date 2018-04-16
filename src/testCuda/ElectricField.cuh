#ifndef ELECTRICFIELD_CUH
#define ELECTRICFIELD_CUH
#include <stdio.h>
#include <typeinfo>
#include <iostream>
#include <vector>

class ElectricField
{
	private:
		std::vector< std::vector<double> >_grid;
		double _xmax;
		double _xmin;
		double _ymax;
		double _ymin;
	public:
		ElectricField(double xmin, double xmax, double ymin, double ymax, int gridsX, int gridsY);
		double getEvalue(std::vector<double> point);
		__host__ void getEvalue(std::vector<double> *points, double *value);
		//__device__ void getEvalue(double *points, double *value);
		__host__ __device__ bool isIn(double x, double y);
};
#endif //ELECTRICFIELD_H
