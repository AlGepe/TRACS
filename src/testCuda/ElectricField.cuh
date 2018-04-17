#ifndef ELECTRICFIELD_CUH
#define ELECTRICFIELD_CUH
#include <stdio.h>
#include <typeinfo>
#include <iostream>
#include <vector>

class ElectricField
{
	private:
		double _xmax;
		double _xmin;
		double _ymax;
		double _ymin;
		std::vector< std::vector<double> > _grid;

	public:
		ElectricField(double xmin, double xmax, double ymin, double ymax, int gridsX, int gridsY);
		double getEvalue(std::vector<double> point);
		void getEvalue(std::vector<double> *points, double *value);
		//__device__ void getEvalue(double *points, double *value);
		bool isIn(double x, double y);
		std::vector< std::vector<double> > get_grid();
};
#endif //ELECTRICFIELD_H
