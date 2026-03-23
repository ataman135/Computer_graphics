#include "Render.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <random>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>



//void paintQuadrangle(double A1[3], double A2[3], double A3[3], double A4[3], int color_seed=1) {
//	std::mt19937 gen(color_seed);
//	std::uniform_real_distribution <double > r(0, 1);
//	glBegin(GL_QUADS);
//		glColor3d(r(gen), r(gen), r(gen));
//		glVertex3dv(A1);
//		glVertex3dv(A2);
//		glVertex3dv(A3);
//		glVertex3dv(A4);
//	glEnd();
//}
//
//void paintTriangle(double A1[3], double A2[3], double A3[3], int color_seed = 1) {
//	std::mt19937 gen(color_seed);
//	std::uniform_real_distribution <double > r(0, 1);
//	glBegin(GL_TRIANGLES);
//		glColor3d(r(gen), r(gen), r(gen));
//		glVertex3dv(A1);
//		glVertex3dv(A2);
//		glVertex3dv(A3);
//	glEnd();
//}

//void paintWall(double A1[3], double A2[3], double height, int color_seed=1) {
//	double A3[] = { A2[0], A2[1], height };
//	double A4[] = { A1[0], A1[1], height };
//	
//	paintQuadrangle(A1, A2, A3, A4, color_seed);
//}
//
//void paintSegment(double StartPoint[3], double CalculateCenter[3], double angle, double height, double PaintCenter[3] = nullptr, int color_seed = 1) {
//	if (PaintCenter == nullptr) {
//		PaintCenter = CalculateCenter;
//	}
//	
//	double part_angle = angle / 60.0;
//	
//	double s = sin(part_angle);
//	double c = cos(part_angle);
//
//	double B1[]{ StartPoint[0], StartPoint[1], StartPoint[2] };
//	double B2[]{ 0, 0, 0 };
//
//	for (int i = 0; i < 60; i++) {
//		B2[0] = CalculateCenter[0] + c * (B1[0] - CalculateCenter[0]) - s * (B1[1] - CalculateCenter[1]);
//		B2[1] = CalculateCenter[1] + s * (B1[0] - CalculateCenter[0]) + c * (B1[1] - CalculateCenter[1]);
//		B2[2] = B1[2];
//
//		paintTriangle(PaintCenter, B1, B2, color_seed+1);
//		paintWall(B1, B2, height, color_seed + 2);
//
//		B1[2] += height;
//		B2[2] += height;
//		PaintCenter[2] += height;
//		if (CalculateCenter != PaintCenter) CalculateCenter[2] += height;
//
//		paintTriangle(PaintCenter, B1, B2, color_seed + 3);
//
//		B1[0] = B2[0];
//		B1[1] = B2[1];
//		B1[2] -= height;
//		PaintCenter[2] -= height;
//		if (CalculateCenter != PaintCenter) CalculateCenter[2] -= height;
//	}
//}
//
//void paintHalfCylinder(double A1[3], double A2[3], double height, int slices = 60, int color_seed=1) {
//	double O[]{ (A1[0] + A2[0]) / 2, (A1[1] + A2[1]) / 2, A1[2]};
//	double B1[]{ A1[0], A1[1], A1[2]};
//
//	paintSegment(B1, O, -M_PI, height, nullptr, color_seed);
//	
//}
//
//void paintShape(double height=5) {
//	double A[]{ 0, 0, 0 };
//	double B[]{ -4, 3, 0 };
//	double C[]{ 0, 5, 0 };
//	double D[]{ 2, 1, 0 };
//	double E[]{ 6, 2, 0 };
//	double F[]{ 2, -1, 0 };
//	double G[]{ 5, -8, 0 };
//	double H[]{ -1, -5, 0 };
//
//	paintHalfCylinder(B, C, height);
//
//	double* Points[] = {A, B, C, D, E, F, G, H};
//
//	paintQuadrangle(A, B, C, D, 1);
//	paintQuadrangle(A, D, E, F, 2);
//	paintTriangle(G, A, F, 56);
//
//	paintWall(A, B, height, 4);
//	paintWall(C, D, height, 5);
//	paintWall(D, E, height, 6);
//	paintWall(E, F, height, 7);
//	paintWall(G, F, height, 19);
//	paintWall(A, H, height, 8);
//	
//
//	for (int i = 0; i < 8; i++) {
//		Points[i][2] = height;
//	}
//
//	paintQuadrangle(A, B, C, D, 12);
//	paintQuadrangle(A, D, E, F, 22);
//	paintTriangle(G, A, F, 58);
//
//	double O[]{ -0.5, -11.5, 0 }; // Честно, харкод, но ничего не поделать
//	double s = -15.0 / 17.0;
//	A[2] = 0;
//	double B1[]{ H[0], H[1], 0 };
//	double angle = asin(s);
//
//	paintSegment(B1, O, angle, height, A, 77);
//}

std::vector<std::vector<double>> Circle01;
std::vector<std::vector<double>> Circle02;

void paintQuadrangle(const std::vector<std::vector<double>> points, int color_seed=1) {
	std::mt19937 gen(color_seed);
	std::uniform_real_distribution <double > r(0, 1);
	glBegin(GL_QUADS);
		glColor3d(r(gen), r(gen), r(gen));
		glVertex3dv(points[0].data());
		glVertex3dv(points[1].data());
		glVertex3dv(points[2].data());
		glVertex3dv(points[3].data());
	glEnd();
}

void paintTriangle(const std::vector<std::vector<double>> points, int color_seed = 1) {
	std::mt19937 gen(color_seed);
	std::uniform_real_distribution <double > r(0, 1);
	glBegin(GL_TRIANGLES);
	glColor3d(r(gen), r(gen), r(gen));
	glVertex3dv(points[0].data());
	glVertex3dv(points[1].data());
	glVertex3dv(points[2].data());
	glEnd();
}

void paintPartCircle(std::vector<double> PaintCenter, std::vector<std::vector<double>>& CirclePoints, int color_seed = 1) {
	for (int i = 0; i < CirclePoints.size()-1; i++) {
		paintTriangle({ PaintCenter, CirclePoints[i], CirclePoints[i+1] }, color_seed + 1);
	}
}

void calculateCircle(std::vector<double> StartPoint, std::vector<double> CalculateCenter, std::vector<std::vector<double>>& CirclePoints,double angle) {
	double part_angle = angle / 60.0;

	double s = sin(part_angle);
	double c = cos(part_angle);

	std::vector<double> B1 = { StartPoint[0], StartPoint[1], StartPoint[2] };
	std::vector<double> B2 = { 0, 0, 0 };

	CirclePoints.push_back(B1);

	for (int i = 0; i < 60; i++) {
		B2[0] = CalculateCenter[0] + c * (B1[0] - CalculateCenter[0]) - s * (B1[1] - CalculateCenter[1]);
		B2[1] = CalculateCenter[1] + s * (B1[0] - CalculateCenter[0]) + c * (B1[1] - CalculateCenter[1]);
		B2[2] = B1[2];
		B1[0] = B2[0];
		B1[1] = B2[1];
		CirclePoints.push_back(B1);
	}
}

void paintFloor(const std::vector<std::vector<double>> points) {
	paintQuadrangle({ points[0], points[1], points[2], points[3] }, 1);
	paintQuadrangle({ points[0], points[3], points[4], points[5] }, 2);
	paintTriangle({ points[0], points[5], points[6]}, 3);

	std::vector<double> O1 = { (points[1][0] + points[2][0]) / 2, (points[1][1] + points[2][1]) / 2, points[0][2] };

	paintPartCircle(O1, Circle01, 8);
	paintPartCircle(points[0], Circle02, 9);

}

void paintWall(std::vector<std::vector<double>> prev_points, std::vector<std::vector<double>> curr_points, int color_seed=2) {
	std::mt19937 gen(color_seed);
	std::uniform_real_distribution <double > r(0, 1);
	for (int i = 0; i < prev_points.size()-1; i++) {
		if (i == 6) {
			continue;
		}
		
		glBegin(GL_TRIANGLES);
			glColor3d(r(gen), r(gen), r(gen));
			glVertex3dv(prev_points[i].data());
			glVertex3dv(prev_points[i+1].data());
			glVertex3dv(curr_points[i].data());
		glEnd();

		glBegin(GL_TRIANGLES);
			glColor3d(r(gen), r(gen), r(gen));
			glVertex3dv(prev_points[i+1].data());
			glVertex3dv(curr_points[i+1].data());
			glVertex3dv(curr_points[i].data());
		glEnd();
	}
}

void prism(double h, double u) {
	std::vector<std::vector<double>> points = {
		{0, 0, 0}, {-4, 3, 0}, {0, 5, 0}, {2, 1, 0},
		{6, 2, 0}, {2, -1, 0}, {5, -8, 0}, {-1, -5, 0}
	};

	std::vector<double> O1 = { (points[1][0] + points[2][0]) / 2, (points[1][1] + points[2][1]) / 2, points[0][2] };
	std::vector<double> O2 = { -0.5, -11.5, points[0][2] };
	double s = -15.0 / 17.0;
	double angle2 = asin(s);

	std::vector<std::vector<double>> Circle1;
	calculateCircle(points[1], O1, Circle1, -M_PI);
	paintPartCircle(O1, Circle1, 8);

	std::vector<std::vector<double>> Circle2;
	calculateCircle(points[7], O2, Circle2, angle2);

	Circle01 = std::move(Circle1);
	Circle02 = std::move(Circle2);

	paintFloor(points);
	double c_x = 0;
	double c_y = 0;
	int precision = 140.0;

	double part_h = h / (double)precision;
	double part_u = u / (double)precision;

	std::vector<std::vector<double>> prev_points;
	std::vector<std::vector<double>> prev_pointsC1;
	std::vector<std::vector<double>> prev_pointsC2;

	for (int i = 0; i < points.size(); i++) {
		prev_points.push_back({points[i][0], points[i][1], 0});
	}

	paintFloor(prev_points);

	for (int i = 0; i < Circle01.size(); i++) {
		prev_pointsC1.push_back({ Circle01[i][0], Circle01[i][1], 0 });
	}
	for (int i = 0; i < Circle02.size(); i++) {
		prev_pointsC2.push_back({ Circle02[i][0], Circle02[i][1], 0 });
	}

	for (int i = 0; i < precision; i++) {
		double curr_h = part_h * i;
		double curr_u = part_u * i;
		double rad = curr_u * M_PI / 180.0;

		std::vector<std::vector<double>> curr_points;
		std::vector<std::vector<double>> curr_pointsC1;
		std::vector<std::vector<double>> curr_pointsC2;

		for (const auto& p : points) {
			double dx = p[0] - c_x;
			double dy = p[1] - c_y;
			double x = c_x + dx * cos(rad) - dy * sin(rad);
			double y = c_y + dx * sin(rad) + dy * cos(rad);
			curr_points.push_back({ x, y, curr_h });
		}

		for (const auto& p : Circle01) {
			double dx = p[0] - c_x;
			double dy = p[1] - c_y;
			double x = c_x + dx * cos(rad) - dy * sin(rad);
			double y = c_y + dx * sin(rad) + dy * cos(rad);
			curr_pointsC1.push_back({ x, y, curr_h });
		}

		for (const auto& p : Circle02) {
			double dx = p[0] - c_x;
			double dy = p[1] - c_y;
			double x = c_x + dx * cos(rad) - dy * sin(rad);
			double y = c_y + dx * sin(rad) + dy * cos(rad);
			curr_pointsC2.push_back({ x, y, curr_h });
		}

		paintWall(prev_points, curr_points, 11);
		paintWall({ prev_points[0], prev_points[7] }, { curr_points[0], curr_points[7]}, 11);
		paintWall(prev_pointsC1, curr_pointsC1, 12);
		paintWall(prev_pointsC2, curr_pointsC2, 13);

		prev_points = std::move(curr_points);
		prev_pointsC1 = std::move(curr_pointsC1);
		prev_pointsC2 = std::move(curr_pointsC2);
	}
	Circle01 = std::move(prev_pointsC1);
	Circle02 = std::move(prev_pointsC2);

	paintFloor(prev_points);
}

double u = 0;

void Render(double delta_time)
{
	//glTranslated(5,0,0);
	//glRotated(120, 0, 1, 0);

	double speed = 120;
	glRotated(u += speed * delta_time, 0, 0, 1);
	prism(5, 180);
}