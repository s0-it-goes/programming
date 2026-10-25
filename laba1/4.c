#include <stdio.h>
#include <math.h>

int main()
{
	int h = 600;
	float Vsat = 7.56;
	float f0 = 2.18 * pow(10, 9);
	int Re = 6371;
	double pi = 3.141592653;
	double a = 0.0;
	float c = 3.0 * pow(10,8);

	printf("Enter elevation angle alpha (0..90 degrees): ");
	scanf("%lf", &a);

	if( a < 0 || a > 90 ) {
		printf("ERROR: angle must be between 0 and 90 degrees\n");
		return 0;
	}

	double d = sqrt((pow(Re,2) * pow(sin(a * pi/180),2)) + (2 * Re * h) + pow(h,2) ) - Re * sin(a * pi/180);
	double Vr = Vsat * ( (Re * cos(a * pi/180)) / (Re * sin(a * pi/180) + d));
	double b = Vr / c;
	double dT =  b * pow(10,9) * 1000;
	double Fd =  (f0 * sqrt((1 + b)/(1 - b)) - f0);

	printf("Distance: %.2lf km\n", d);
	printf("Radial velocity (vr): %.2lf m/s\n", Vr * 1000);
	printf("Time drift (dT): %.4lf ns/s\n", dT);
	printf("Doppler shift (fd): %.4lf kHz\n", Fd);

	char status;

	if ( (Fd > 42.0 || dT > 18) && d > 1000) {
		status = 1; // critical error
	}
	else if ( Fd > 25.0 && dT > 10 ) {
		status = 2; // high dynamic mode
	}
	else if ( Fd > 3.0 || fabs(dT) > 1.0 ) {
		status = 3; // normal acceleration
	}

	switch(status) {
		case 1:
			printf("PROFILE: CRITICAL ERROR\n");
			break;
		case 2:
			printf("PROFILE: HIGHT DYNAMIC MODE\n");
			break;
		case 3:
			printf("PROFILE: NORMAL ACCELERATION\n");
			break;
		default:
			printf("PROFILE: ZENITH MODE\n");
			break;
	}

	return 0;
}
