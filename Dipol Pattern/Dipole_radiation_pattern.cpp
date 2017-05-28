#include "Dipole_radiation_pattern.h"

#define pack(buffer) tmp.x = x; tmp.y = y; tmp.z = z; buffer.push_back(tmp);
#define convert(value) x = value * sin(theta) * cos(phi); y = value * sin(theta) * sin(phi); z = value * cos(theta);
#define more(value_0, value_1) if(value_0 < value_1) value_0 = value_1;

Dipole_radiation::Dipole_radiation()
{
	length = 1;
	amperage = 1;
	wavelength = 1;
	pi = 3.14159265358979323846;
	frequency = 1;
	time = 1;
	p0 = 120 * pi;
	rad = 1;
	er = 0;
	et = 0;
	hp = 0;
}
Dipole_radiation::~Dipole_radiation()
{

}


void Dipole_radiation::Set_Parameters(double input_length, double input_amperage, double input_wavelength, double input_frequency, double input_time, double input_rad)
{
	length = input_length;
	amperage = input_amperage;
	wavelength = input_wavelength;
	frequency = input_frequency;
	time = input_time;
	rad = input_rad;
}



void Dipole_radiation::Get_Electric_Field_Rad_Near(double &x, double &y, double &z, double theta, double phi)
{
	convert((((2 * H * p0 * (cos(theta) / sin(theta))) / (B * rad)) * sin(frequency * time)) / er)
}

void Dipole_radiation::Get_Electric_Field_Theta_Near(double &x, double &y, double &z, double theta, double phi)
{
	convert((((H * p0) / (B * rad)) * sin(frequency * time)) / et)
}

void Dipole_radiation::Get_Magnetic_Field_Phi_Near(double &x, double &y, double &z, double theta, double phi)
{
	convert((H * cos(frequency * time)) / hp)
}

void Dipole_radiation::Get_Electric_Field_Theta_Distant(double &x, double &y, double &z, double theta, double phi)
{
	convert((-E * sin(frequency * time - B * rad)) / et)
}

void Dipole_radiation::Get_Magnetic_Field_Phi_Distant(double &x, double &y, double &z, double theta, double phi)
{
	convert((H * sin(frequency * time - B * rad)) / hp)
}

void Dipole_radiation::Find_Near_Zone_Max_Values(bool zone)
{
	er = -DBL_MIN;
	et = -DBL_MIN;
	hp = -DBL_MIN;

	double tmpvalue_0;
	double tmpvalue_1;
	double tmpvalue_2;

	for (double theta = 0; theta <= pi; theta += 0.01)
	{
		if (zone)
		{
			E = (amperage * length * B * p0 * sin(theta)) / (4 * pi * rad);
			H = (amperage * length * B * sin(theta)) / (4 * pi * rad);
			tmpvalue_1 = abs(-E * sin(frequency * time - B * rad));
			tmpvalue_2 = H * sin(frequency * time - B * rad);
		}
		else
		{
			H = (amperage * length * sin(theta)) / (4 * pi * pow(rad, 2));
			tmpvalue_0 = ((2 * H * p0 * (cos(theta) / sin(theta))) / (B * rad)) * sin(frequency * time);
			tmpvalue_1 = ((H * p0) / (B * rad)) * sin(frequency * time);
			tmpvalue_2 = (H * cos(frequency * time));
			more(er, tmpvalue_0)
		}
		more(et,tmpvalue_1)
		more(hp,tmpvalue_2)
	}
	int i = 0;
	i++;
}

void Dipole_radiation::Get_Radiation_Pattern(bool zone, std::vector<Vertex> &electric_field_line, std::vector<Vertex> &magnetic_field_line)
{
	B = (2 * pi) / wavelength;
	this->Find_Near_Zone_Max_Values(zone);

	double x, y, z;
	Vertex tmp;

	for (double phi = 0; phi <= pi * 2; phi += 0.1)
	{
		for (double theta = 0; theta <= pi * 2; theta += 0.1)
		{
			if (zone)
			{
				E = (amperage * length * B * p0 * sin(theta)) / (4 * pi * rad);
				this->Get_Electric_Field_Theta_Distant(x, y, z, theta, phi);
			}
			else
			{
				H = (amperage * length * sin(theta)) / (4 * pi * pow(rad, 2));
				this->Get_Electric_Field_Theta_Near(x, y, z, theta, phi);
			}
				pack(electric_field_line)
		}
	}

	for (double theta = 0; theta <= pi * 2 ; theta += 0.1)
	{
		for (double phi = 0; phi <= pi * 2 ; phi += 0.1)
		{
			if (zone)
			{
				H = (amperage * length * B * sin(theta)) / (4 * pi * rad);
				this->Get_Magnetic_Field_Phi_Distant(x, y, z, theta, phi);
			}
			else
			{
				H = (amperage * length * sin(theta)) / (4 * pi * pow(rad, 2));
				this->Get_Magnetic_Field_Phi_Near(x, y, z, theta, phi);
			}
			pack(magnetic_field_line)
		}
	}
}

double Dipole_radiation::Get_Amplitude_Erad()
{
	return er;
}

std::pair<Vertex, Vertex> Dipole_radiation::Get_Erad_Vector(bool zone)
{
	std::pair<Vertex, Vertex> result;
	Vertex tmp;
	if (zone)
	{
		tmp.x = 0;
		tmp.y = 0;
		tmp.z = 0;
	}
	else
	{
		H = (amperage * length * sin(1.7)) / (4 * pi * pow(rad, 2));
		this->Get_Electric_Field_Rad_Near(tmp.x, tmp.y, tmp.z, 1.7, 1.5);
		result.first = tmp;
		H = (amperage * length * sin(1.5)) / (4 * pi * pow(rad, 2));
		this->Get_Electric_Field_Rad_Near(tmp.x, tmp.y, tmp.z, 1.5, 1.5);
	}
	result.second = tmp;
	return result;
}

double Dipole_radiation::Get_Amplitude_Etheta()
{
	return et;
}

std::pair<Vertex, Vertex> Dipole_radiation::Get_Etheta_Vector(bool zone)
{
	std::pair<Vertex, Vertex> result;
	Vertex tmp;
	if (zone)
	{
		E = (amperage * length * B * p0 * sin(1.5)) / (4 * pi * rad);
		this->Get_Electric_Field_Theta_Distant(tmp.x, tmp.y, tmp.z, 1.5, 0.5);
		result.first = tmp;
		E = (amperage * length * B * p0 * sin(1.7)) / (4 * pi * rad);
		this->Get_Electric_Field_Theta_Distant(tmp.x, tmp.y, tmp.z, 1.7, 0.5);
	}
	else
	{
		H = (amperage * length * sin(1.5)) / (4 * pi * pow(rad, 2));
		this->Get_Electric_Field_Theta_Near(tmp.x, tmp.y, tmp.z, 1.5, 0.5);
		result.first = tmp;
		H = (amperage * length * sin(1.7)) / (4 * pi * pow(rad, 2));
		this->Get_Electric_Field_Theta_Near(tmp.x, tmp.y, tmp.z, 1.7, 0.5);
	}
	result.second = tmp;
	return result;
}

double Dipole_radiation::Get_Amplitude_Hphi()
{
	return hp;
}

std::pair<Vertex, Vertex> Dipole_radiation::Get_Hphi_Vector(bool zone)
{
	std::pair<Vertex, Vertex> result;
	Vertex tmp;
	if (zone)
	{
		H = (amperage * length * B * sin(1.5)) / (4 * pi * rad);
		this->Get_Magnetic_Field_Phi_Distant(tmp.x, tmp.y, tmp.z, 1.5, 0.5);
		result.first = tmp;
		H = (amperage * length * B * sin(1.5)) / (4 * pi * rad);
		this->Get_Magnetic_Field_Phi_Distant(tmp.x, tmp.y, tmp.z, 1.5, 0.7);
	}
	else
	{
		H = (amperage * length * sin(1.5)) / (4 * pi * pow(rad, 2));
		this->Get_Magnetic_Field_Phi_Near(tmp.x, tmp.y, tmp.z, 1.5, 0.5);
		result.first = tmp;
		H = (amperage * length * sin(1.5)) / (4 * pi * pow(rad, 2));
		this->Get_Magnetic_Field_Phi_Near(tmp.x, tmp.y, tmp.z, 1.5, 0.7);
	}
	result.second = tmp;
	return result;
}