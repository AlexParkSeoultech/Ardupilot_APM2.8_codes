#ifndef AC_PID_h
#define AC_PID_h
#include <Arduino.h>
class AC_PID {
public:
	AC_PID(  const float &initial_p = 0.0,  const float &initial_i = 0.0,  // constructor
	    const float &initial_d = 0.0, const int16_t &initial_imax = 0.0) :
		_kp  (initial_p), _ki  (initial_i), _kd  (initial_d),	_imax(abs(initial_imax)) 	{	}
	int32_t get_pid(int32_t error, float dt);
	int32_t get_pi(int32_t error, float dt);
	int32_t get_p(int32_t error);
	int32_t get_i(int32_t error, float dt);
	int32_t get_d(int32_t error, float dt);
	void	reset_I();
	void 	load_gains();
	void 	save_gains();
	void operator() (const float p, const float i,const float d, const int16_t imaxval)	{
	  _kp = p; _ki = i; _kd = d; _imax = abs(imaxval);
	}  /// Overload the function call operator 
	float	kP() const				{ return _kp; }
  void  kP(const float v)   { _kp=v; }
	float	kI() const 				{ return _ki; }
  void  kI(const float v)   { _ki=v; }
	float	kD() const 				{ return _kd; }
  void  kD(const float v)   { _kd=v; }
	int16_t	imax() const			{ return _imax; }
	void	imax(const int16_t v)	{ _imax=abs(v); }
	float	get_integrator() const	{ return _integrator; }
	void	set_integrator(float i)	{ _integrator = i; }
private:
	float			_kp, _ki, _kd, _imax;
	float				_integrator;		///< integrator value
	int32_t			_last_input;		///< last input for derivative
	float				_last_derivative; 	///< last derivative for low-pass filter
	float				_output;
//	float				_derivative;
	static const float _filter =15.9155e-3; // "1 / ( 2 * PI * f_cut )";// LPF for derivative
};
#endif
