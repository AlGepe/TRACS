#include <SMSDetector.h>

using namespace dolfin;

SMSDetector::SMSDetector(double pitch, double width, double depth, int nns, char bulk_type, char implant_type, int n_cells_x = 100, int n_cells_y = 100 ) :
    _pitch(pitch),
    _width(width),
    _depth(depth),
    _nns(nns),
    _bulk_type(bulk_type),
    _implant_type(implant_type),
    _x_min(0.0),
    _x_max(_pitch * (2*_nns+1)),
    _y_min(0),
    _y_max(_depth),
    _n_cells_x(n_cells_x),
    _n_cells_y(n_cells_y),
    _mesh(_x_min,_y_min,_x_max,_depth, _n_cells_x, _n_cells_y),
    _periodic_boundary(_x_min, _x_max, _depth),
    _central_strip(_pitch, _width, _nns),
    _neighbour_strips(_pitch, _width, _nns),
    _backplane(_x_min, _x_max, _depth),
    _V_p(_mesh, _periodic_boundary),
    _a_p(_V_p, _V_p),
    _L_p(_V_p),
    _V_g(_mesh),
    _a_g(_V_g, _V_g),
    _L_g(_V_g),
    _w_u(_V_p),
    _d_u(_V_p),
    _w_f_grad(_V_g),
    _d_f_grad(_V_g)
{
}

void SMSDetector::set_voltages(double v_bias, double v_depletion)
{
  _v_strips = (_implant_type == 'n') ? v_bias : 0.0;
  _v_backplane = (_implant_type == 'p') ? v_bias : 0.0;
  _f_poisson = ((_bulk_type== 'p') ? +1.0 : -1.0)*(-2.0*v_depletion)/(_depth*_depth);
}

void SMSDetector::solve_w_u()
{

  // Solving Laplace equation f = 0
  Constant f(0);
  _L_p.f = f;

  // Set BC values
  Constant central_strip_V(1.0);
  Constant neighbour_strip_V(0.0);
  Constant backplane_V(0.0);
  // Set BC variables
  DirichletBC central_strip_BC(_V_p, central_strip_V, _central_strip);
  DirichletBC neighbour_strip_BC(_V_p, neighbour_strip_V, _neighbour_strips);
  DirichletBC backplane_BC(_V_p, backplane_V, _backplane);
  // Collect them
  std::vector<const DirichletBC*> bcs;
  bcs.push_back(&central_strip_BC);
  bcs.push_back(&neighbour_strip_BC);
  bcs.push_back(&backplane_BC);

  solve(_a_p == _L_p , _w_u, bcs);
}

Function * SMSDetector::get_w_u()
{
  return &_w_u;
}


void SMSDetector::solve_d_u()
{
  // Solving Poisson equation for the d_u
  Constant f(_f_poisson);
  _L_p.f = f;

  // Set BC values
  Constant central_strip_V(_v_strips);
  Constant neighbour_strip_V(_v_strips);
  Constant backplane_V(_v_backplane);
  // Set BC variables
  DirichletBC central_strip_BC(_V_p, central_strip_V, _central_strip);
  DirichletBC neighbour_strip_BC(_V_p, neighbour_strip_V, _neighbour_strips);
  DirichletBC backplane_BC(_V_p, backplane_V, _backplane);
  // Collect them
  std::vector<const DirichletBC*> bcs;
  bcs.push_back(&central_strip_BC);
  bcs.push_back(&neighbour_strip_BC);
  bcs.push_back(&backplane_BC);

  solve(_a_p == _L_p , _d_u, bcs);
}

Function * SMSDetector::get_d_u()
{
  return &_d_u;
}

void SMSDetector::solve_w_f_grad()
{

  _L_g.u = _w_u;
  solve(_a_g == _L_g, _w_f_grad);
  // Change sign E = - grad(u)
  _w_f_grad = _w_f_grad * (-1.0);
}

Function * SMSDetector::get_w_f_grad()
{
  return &_w_f_grad;
}


void SMSDetector::solve_d_f_grad()
{
  _L_g.u = _d_u;
  solve(_a_g == _L_g, _d_f_grad);
  // Change sign E = - grad(u)
  _d_f_grad = _d_f_grad * (-1.0);

}

Function * SMSDetector::get_d_f_grad()
{
  return &_d_f_grad;
}

bool SMSDetector::is_out(std::vector<double> x)
{
  bool out = true;
  if ( (x[0] > _x_min) && (x[0] < _x_max) && (x[1] > _y_min) && (x[1] < _y_max))
  {
    out = false;
  }
  return out;
}


SMSDetector::~SMSDetector()
{

}




