#include <typeinfo>
#include "ElectricField.cuh"

ElectricField::ElectricField(double xmin, double xmax, double ymin, double ymax, int gridsX, int gridsY):
_xmax(xmax),
_xmin(xmin),
_ymax(ymax),
_ymin(ymin)
{
	std::vector<std::vector<double> > _grid(gridsX, std::vector<double> (gridsY, 0.));
	srand ( time(NULL) );
	for(int i=0; i<gridsX; i++)
	{
		for(int j=0; j<gridsY; j++)
		{

			_grid.at(i).at(j) = 1.5 + gridsX * rand() % 3 + gridsY;
		}
	}
	
	
	std::cout << _grid.size() <<std::endl;
}

double ElectricField::getEvalue(std::vector<double> point)
{
	std::cout << typeid(point).name() << std::endl;
	double x = point.at(0);
	double y = point.at(1);
	if (isIn(x, y))
	{
	std::cout << _grid.size() <<std::endl;
		int i = (int) _grid.size()/(_xmax-_xmin) * (x - _xmin);
	std::cout << "test1" <<std::endl;
		int j = (int) _grid.at(0).size()/(_ymax-_ymin) * (y - _ymin);
	std::cout << "test2" <<std::endl;
		return _grid.at(i).at(j);
	}
	else
	{
	//std::cout << "test" <<std::endl;
		return 0;
	}
}

__host__ void ElectricField::getEvalue(std::vector<double> *points, double *value)
{
	double x = points->at(0);
	double y = points->at(1);
	if (isIn(x, y))
	{
		int i = (int) _grid.size()/(_xmax-_xmin) * (x - _xmin);
		int j = (int) _grid[0].size()/(_ymax-_ymin) * (y - _ymin);
		*value =  _grid[i][j];
	}
	else
	{
		*value = 0;
	}
}
/*
 __device__ void ElectricField::getEvalue(double *points, double *value)
{
	double x = points[0];
	double y = points[1];
	if (isIn(x, y))
	{
		int i = (int) _grid.size()/(_xmax-_xmin) * (x - _xmin);
		int j = (int) _grid[0].size()/(_ymax-_ymin) * (y - _ymin);
		*value =  _grid[i][j];
	}
	else
	{
		*value = 0;
	}
}
*/

__host__ __device__ bool ElectricField::isIn(double x, double y)
{
	if (x > _xmax || x < _xmin || y < _ymin || y > _ymax)
	{
		return false;
	}
	else
	{
		return true;
	}
}

