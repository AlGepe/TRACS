#include "ElectricField.cuh"

ElectricField::ElectricField(double xmin, double xmax, double ymin, double ymax, int gridsX, int gridsY):
_xmin(xmin),
_xmax(xmax),
_ymin(ymin),
_ymax(ymax)
{
	srand ( time(NULL) );
	_grid = std::vector<std::vector<double> >(gridsX, std::vector<double>(gridsY) );
	for(int i=0; i<gridsX; i++)
	{
		for(int j=0; j<gridsY; j++)
		{
			_grid[i][j] = 1.5 + gridsX * rand() % 3 + gridsY;
		}
	}
}

double ElectricField::getEvalue(double x, double y)
{
	if (isIn(x, y))
	{
		int i = (int) _grid.size()/(_xmax-_xmin) * (x - _xmin);
		int j = (int) _grid[0].size()/(_ymax-_ymin) * (y - _ymin);
		return _grid[i][j];
	}
	else
	{
		return 0;
	}
}


bool ElectricField::isIn(double x, double y)
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

