#include "AC_PID.h"
int32_t AC_PID::get_p(int32_t error) {
	return (float)error * _kp;
}
int32_t AC_PID::get_i(int32_t error, float dt) {
	if((_ki != 0) && (dt != 0)){
		_integrator += ((float)error * _ki) * dt;
		if (_integrator < -_imax) {
			_integrator = -_imax;
		} else if (_integrator > _imax) {
			_integrator = _imax;
		}
		return _integrator;
	}
	return 0;
}
int32_t AC_PID::get_d(int32_t input, float dt){
	if ((_kd != 0) && (dt != 0)) {
		float _derivative = (input - _last_input) / dt;
		_derivative = _last_derivative +
		        (dt / ( _filter + dt)) * (_derivative - _last_derivative);
		_last_input 		= input;
		_last_derivative    = _derivative;
		return _kd * _derivative;
	}
	return 0;
}
int32_t AC_PID::get_pi(int32_t error, float dt){
	return get_p(error) + get_i(error, dt);
}
int32_t AC_PID::get_pid(int32_t error, float dt) {
	return get_p(error) + get_i(error, dt) + get_d(error, dt);
}
void AC_PID::reset_I() {
	_integrator = 0;
	_last_input = 0;
	_last_derivative = 0;
}
void AC_PID::load_gains() {
//	_kp.load();
//	_ki.load();
//	_kd.load();
//	_imax.load();
//	_imax = abs(_imax);
}
void AC_PID::save_gains() {
//	_kp.save();
//	_ki.save();
//	_kd.save();
//	_imax.save();
}
