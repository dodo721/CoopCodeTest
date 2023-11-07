/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	EyeMeshData.cpp
//
//	Hidden Area Mesh data for one HMD eye.
//
//	The data is a list of 96 vertices, defining 32 triangles.
//	The positions are normalised - range from 0.0 to 1.0
//	Each 3 consecutive vertices define on triangle.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math.h>

struct Vertex2D
{
	Vertex2D(float InX, float InY)
	{
		X = InX;
		Y = InY;
	}
	Vertex2D() {
		X = 0;
		Y = 0;
	}

	bool operator==(const Vertex2D& rhs) const {
		return X == rhs.X && Y == rhs.Y;
	};

	Vertex2D operator+(const Vertex2D& rhs) {
		return {X + rhs.X, Y + rhs.Y};
	}

	Vertex2D operator-(const Vertex2D& rhs) {
		return {X - rhs.X, Y - rhs.Y};
	}

	Vertex2D operator*(const float& rhs) {
		return {X * rhs, Y * rhs};
	}

	/*float length () {
		return sqrt((X * X) + (Y * Y));
	}

	bool operator< (Vertex2D &rhs) {
		return length() < rhs.length();
	}*/

	float		X;
	float		Y;
};

const Vertex2D		LeftEyeHiddenAreaPositions[] =
{
	Vertex2D(0.6420568228f, 1.0f),
	Vertex2D(1.0f, 1.0f),
	Vertex2D(0.7550624013f, 0.9892609119f),

	Vertex2D(0.7550624013f, 0.9892609119f),
	Vertex2D(1.0f, 1.0f),
	Vertex2D(0.8259530067f, 0.9766981006f),
	
	Vertex2D(1.0f, 0.6303145289f),
	Vertex2D(0.9933852553f, 0.6894935966f),
	Vertex2D(1.0f, 1.0f),
	
	Vertex2D(0.9780833721f, 0.7837033868f),
	Vertex2D(1.0f, 1.0f),
	Vertex2D(0.9933852553f, 0.6894935966f),
	
	Vertex2D(0.8259530067f, 0.9766981006f),
	Vertex2D(1.0f, 1.0f),
	Vertex2D(0.8814527988f, 0.9645425081f),
	
	Vertex2D(0.9561929107f, 0.8690519333f),
	Vertex2D(1.0f, 1.0f),
	Vertex2D(0.9780833721f, 0.7837033868f),
	
	Vertex2D(0.8814527988f, 0.9645425081f),
	Vertex2D(1.0f, 1.0f),
	Vertex2D(0.9246563315f, 0.9536676407f),
	
	Vertex2D(0.9246563315f, 0.9536676407f),
	Vertex2D(1.0f, 1.0f),
	Vertex2D(0.9561929107f, 0.8690519333f),
	
	Vertex2D(1.0f, 0.4252603054f),
	Vertex2D(1.0f, 0.0f),
	Vertex2D(0.9865142703f, 0.3167535067f),
	
	Vertex2D(0.6295351982f, 0.0f),
	Vertex2D(0.6981808543f, 0.005146139301f),
	Vertex2D(1.0f, 0.0f),
	
	Vertex2D(0.7825559974f, 0.01721908338f),
	Vertex2D(1.0f, 0.0f),
	Vertex2D(0.6981808543f, 0.005146139301f),
	
	Vertex2D(0.9865142703f, 0.3167535067f),
	Vertex2D(1.0f, 0.0f),
	Vertex2D(0.9636768699f, 0.216376245f),
	
	Vertex2D(0.8487468362f, 0.03234770149f),
	Vertex2D(1.0f, 0.0f),
	Vertex2D(0.7825559974f, 0.01721908338f),
	
	Vertex2D(0.9636768699f, 0.216376245f),
	Vertex2D(1.0f, 0.0f),
	Vertex2D(0.9353111982f, 0.131273821f),
	
	Vertex2D(0.8951631188f, 0.04515158013f),
	Vertex2D(1.0f, 0.0f),
	Vertex2D(0.8487468362f, 0.03234770149f),
	
	Vertex2D(0.9353111982f, 0.131273821f),
	Vertex2D(1.0f, 0.0f),
	Vertex2D(0.8951631188f, 0.04515158013f),
	
	Vertex2D(0.0f, 0.0f),
	Vertex2D(0.4338365495f, 0.0f),
	Vertex2D(0.330127269f, 0.01285663527f),
	
	Vertex2D(0.0f, 0.4224827588f),
	Vertex2D(0.01270084083f, 0.3334831297f),
	Vertex2D(0.0f, 0.0f),
	
	Vertex2D(0.330127269f, 0.01285663527f),
	Vertex2D(0.0f, 0.0f),
	Vertex2D(0.2493925691f, 0.0313315168f),
	
	Vertex2D(0.03772026673f, 0.2338332087f),
	Vertex2D(0.0f, 0.0f),
	Vertex2D(0.01270084083f, 0.3334831297f),
	
	Vertex2D(0.2493925691f, 0.0313315168f),
	Vertex2D(0.0f, 0.0f),
	Vertex2D(0.1802922487f, 0.05096876994f),
	
	Vertex2D(0.07248612493f, 0.1436391324f),
	Vertex2D(0.0f, 0.0f),
	Vertex2D(0.03772026673f, 0.2338332087f),
	
	Vertex2D(0.1802922487f, 0.05096876994f),
	Vertex2D(0.0f, 0.0f),
	Vertex2D(0.1079794019f, 0.07832186669f),
	
	Vertex2D(0.1079794019f, 0.07832186669f),
	Vertex2D(0.0f, 0.0f),
	Vertex2D(0.07248612493f, 0.1436391324f),
	
	Vertex2D(0.4444268048f, 1.0f),
	Vertex2D(0.3694992661f, 0.9932333231f),
	Vertex2D(0.0f, 1.0f),
	
	Vertex2D(0.0f, 0.6263416409f),
	Vertex2D(0.0f, 1.0f),
	Vertex2D(0.017040601f, 0.7411668301f),
	
	Vertex2D(0.268977195f, 0.9784004092f),
	Vertex2D(0.3694992661f, 0.9932333231f),
	Vertex2D(0.0f, 1.0f),
	
	Vertex2D(0.017040601f, 0.7411668301f),
	Vertex2D(0.03240321949f, 0.8031471968f),
	Vertex2D(0.0f, 1.0f),
	
	Vertex2D(0.1714757681f, 0.9543109536f),
	Vertex2D(0.268977195f, 0.9784004092f),
	Vertex2D(0.0f, 1.0f),
	
	Vertex2D(0.03240321949f, 0.8031471968f),
	Vertex2D(0.05181787908f, 0.8630086184f),
	Vertex2D(0.0f, 1.0f),
	
	Vertex2D(0.07756151259f, 0.9210018516f),
	Vertex2D(0.1714757681f, 0.9543109536f),
	Vertex2D(0.0f, 1.0f),
	
	Vertex2D(0.05181787908f, 0.8630086184f),
	Vertex2D(0.07756151259f, 0.9210018516f),
	Vertex2D(0.0f, 1.0f),
};

const int LeftEyeHiddenAreaPositionsLength = 96;
