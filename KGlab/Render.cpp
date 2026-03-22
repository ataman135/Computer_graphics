#include "Render.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <random>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>


void paintQuadrangle(double A1[3], double A2[3], double A3[3], double A4[3], int color_seed=1) {
	std::mt19937 gen(color_seed);
	std::uniform_real_distribution <double > r(0, 1);
	glBegin(GL_QUADS);
		glColor3d(r(gen), r(gen), r(gen));

		glVertex3dv(A1);
		glVertex3dv(A2);
		glVertex3dv(A3);
		glVertex3dv(A4);
	glEnd();

}

void paintWall(double A1[3], double A2[3], int height, int color_seed=1) {
	std::mt19937 gen(color_seed);
	std::uniform_real_distribution <double > r(0, 1);
	double A3[] = { A2[0], A2[1], height };
	double A4[] = { A1[0], A1[1], height };
	
	glBegin(GL_QUADS);
		glColor3d(r(gen), r(gen), r(gen));

		glVertex3dv(A1);
		glVertex3dv(A2);
		glVertex3dv(A3);
		glVertex3dv(A4);
	glEnd();
}

void paintHalfCylinder(double A1[3], double A2[3], int height, int slices = 60) {
	std::mt19937 gen(7);
	std::uniform_real_distribution <double > r(0, 1);
	double O[]{ (A1[0] + A2[0]) / 2, (A1[1] + A2[1]) / 2, A1[2]};

	double angle= -M_PI / 60.0;

	double radius = sqrt(pow(O[0] - A1[0], 2) + pow(O[1] - A1[1], 2));
	double s = sin(angle);
	double c = cos(angle);

	double B1[]{ A1[0], A1[1], A1[2]};
	double B2[]{ 0, 0, A1[2]};


	
		for (int i = 0; i < 60; i++) {
				glColor3d(r(gen), r(gen), r(gen));

				B2[0] = O[0] + c * (B1[0] - O[0]) - s * (B1[1] - O[1]);
				B2[1] = O[1] + s * (B1[0] - O[0]) + c * (B1[1] - O[1]);
				B2[2] = B1[2];
				glBegin(GL_TRIANGLES);
					glVertex3dv(B1);
					glVertex3dv(O);
					glVertex3dv(B2);
				glEnd();

				paintWall(B1, B2, height, i);

				B1[2] = height;
				B2[2] = height;
				O[2] = height;

				glBegin(GL_TRIANGLES);
					glVertex3dv(B1);
					glVertex3dv(O);
					glVertex3dv(B2);
				glEnd();

			B1[0]= B2[0];
			B1[1] = B2[1];
			B1[2] = 0;
			O[2] = 0;
		}
	
}


void paintShape(int height=5) {
	double A[]{ 0, 0, 0 };
	double B[]{ -4, 3, 0 };
	double C[]{ 0, 5, 0 };
	double D[]{ 2, 1, 0 };
	double E[]{ 6, 2, 0 };
	double F[]{ 2, -1, 0 };
	double G[]{ 5, -8, 0 };
	double H[]{ -1, -5, 0 };

	double O[]{ (B[0] + C[0]) / 2, (B[1] + C[1]) / 2, 0 };
	paintHalfCylinder(B, C, height);

	double* Points[] = {A, B, C, D, E, F, G, H};

	paintQuadrangle(A, B, C, D, 1);
	paintQuadrangle(A, D, E, F, 2);
	paintQuadrangle(A, F, G, H, 3);

	
	for (int i = 0; i < 7; i++) {
		paintWall(Points[i], Points[i + 1], height, i);
	}
	paintWall(Points[0], Points[7], height, 1);

	for (int i = 0; i < 8; i++) {
		Points[i][2] = height;
	}

	paintQuadrangle(A, B, C, D, 12);
	paintQuadrangle(A, D, E, F, 22);
	paintQuadrangle(A, F, G, H, 32);

	
}


void Render(double delta_time)
{
	paintShape();
}