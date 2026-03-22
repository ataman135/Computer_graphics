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

void paintTriangle(double A1[3], double A2[3], double A3[3], int color_seed = 1) {
	std::mt19937 gen(color_seed);
	std::uniform_real_distribution <double > r(0, 1);
	glBegin(GL_TRIANGLES);
		glColor3d(r(gen), r(gen), r(gen));
		glVertex3dv(A1);
		glVertex3dv(A2);
		glVertex3dv(A3);
	glEnd();
}

void paintWall(double A1[3], double A2[3], int height, int color_seed=1) {
	std::mt19937 gen(color_seed);
	std::uniform_real_distribution <double > r(0, 1);
	double A3[] = { A2[0], A2[1], height };
	double A4[] = { A1[0], A1[1], height };
	
	paintQuadrangle(A1, A2, A3, A4, color_seed);
}

void paintHalfCylinder(double A1[3], double A2[3], int height, int slices = 60) {
	std::mt19937 gen(7);
	std::uniform_real_distribution <double > r(0, 1);
	glColor3d(r(gen), r(gen), r(gen));
	double O[]{ (A1[0] + A2[0]) / 2, (A1[1] + A2[1]) / 2, A1[2]};

	double angle= -M_PI / 60.0;

	double s = sin(angle);
	double c = cos(angle);

	double B1[]{ A1[0], A1[1], A1[2]};
	double B2[]{ 0, 0, A1[2]};

		for (int i = 0; i < 60; i++) {
				B2[0] = O[0] + c * (B1[0] - O[0]) - s * (B1[1] - O[1]);
				B2[1] = O[1] + s * (B1[0] - O[0]) + c * (B1[1] - O[1]);
				B2[2] = B1[2];
				paintTriangle(O, B1, B2, 13);

				paintWall(B1, B2, height, 12);

				B1[2] = height;
				B2[2] = height;
				O[2] = height;

				paintTriangle(O, B1, B2, 13);

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

	paintHalfCylinder(B, C, height);

	double* Points[] = {A, B, C, D, E, F, G, H};

	paintQuadrangle(A, B, C, D, 1);
	paintQuadrangle(A, D, E, F, 2);
	paintTriangle(G, A, F, 56);

	paintWall(A, B, height, 4);
	paintWall(C, D, height, 5);
	paintWall(D, E, height, 6);
	paintWall(E, F, height, 7);
	paintWall(G, F, height, 19);
	paintWall(A, H, height, 8);
	

	for (int i = 0; i < 8; i++) {
		Points[i][2] = height;
	}

	paintQuadrangle(A, B, C, D, 12);
	paintQuadrangle(A, D, E, F, 22);
	paintTriangle(G, A, F, 58);

	double O[]{ -0.5, -11.5, 0 }; // Честно, харкод, но ничего не поделать
	double B1[]{ H[0], H[1], 0 };
	double B2[]{ 0, 0, B1[2] };
	


	double s = -15.0 / 17.0;
	double angle = asin(s) / 60.0;
	s = sin(angle);
	double c = cos(angle);

	for (int i = 0; i < 60; i++) {
		B2[0] = O[0] + c * (B1[0] - O[0]) - s * (B1[1] - O[1]);
		B2[1] = O[1] + s * (B1[0] - O[0]) + c * (B1[1] - O[1]);
		B2[2] = B1[2];
		A[2] = 0;
		paintTriangle(A, B1, B2, 13);

		paintWall(B1, B2, height, 12);

		B1[2] = height;
		B2[2] = height;
		O[2] = height;
		A[2] = height;

		paintTriangle(A, B1, B2, 13);

		B1[0] = B2[0];
		B1[1] = B2[1];
		B1[2] = 0;
		O[2] = 0;
	}

	
}


void Render(double delta_time)
{
	paintShape();
}