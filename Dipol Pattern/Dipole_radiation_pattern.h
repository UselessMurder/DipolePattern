#pragma once

#include <cmath>
#include "GL.h"




class Dipole_radiation
{
private:
	double length;
	double amperage;
	double wavelength;
	double frequency;
	double time;
	double rad;

	double pi;
	double p0;
	double B;
	double H;
	double E;


	double er;
	double et;
	double hp;

	void Find_Near_Zone_Max_Values(bool zone);

	void Get_Electric_Field_Rad_Near(double &x, double &y, double &z, double theta, double phi);
	void Get_Electric_Field_Theta_Near(double &x, double &y, double &z, double theta, double phi);
	void Get_Magnetic_Field_Phi_Near(double &x, double &y, double &z, double theta, double phi);

	void Get_Electric_Field_Theta_Distant(double &x, double &y, double &z, double theta, double phi);
	void Get_Magnetic_Field_Phi_Distant(double &x, double &y, double &z, double theta, double phi);

public:
	Dipole_radiation();
	~Dipole_radiation();

	void Set_Parameters(double input_length, double input_amperage, double input_wavelength, double input_frequency, double input_time, double input_rad);

	void Dipole_radiation::Get_Radiation_Pattern(bool zone, std::vector<Vertex> &electric_field_line, std::vector<Vertex> &magnetic_field_line);

	double Get_Amplitude_Erad();
	std::pair<Vertex,Vertex> Get_Erad_Vector(bool zone);

	double Get_Amplitude_Etheta();
	std::pair<Vertex,Vertex> Get_Etheta_Vector(bool zone);

	double Get_Amplitude_Hphi();
	std::pair<Vertex,Vertex> Get_Hphi_Vector(bool zone);
};
