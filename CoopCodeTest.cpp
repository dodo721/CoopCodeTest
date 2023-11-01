/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Cooperative Innovations Code Test
//
//	Copyright 2018 Cooperative Innovations Ltd.
//
//	This test was developed with Visual Studio 2017. It works fine with Visual Studio 2015 as well.
//	The free Community version will work fine.
//	( https://visualstudio.microsoft.com/vs/community/ )
//
//	If you use a compiler other than Visual Studio 2017, make sure we know in case of compilation issues.
//
//	Each test takes the form of a function which you have to implement. 
//	If any of your functions fail the tests, you'll receive a print detailing the line and the program will assert.
//	If you are stuck on a test, comment out the test from main and add some comments explaining how you were trying to solve it.
//	
//	The test functions are:
//		AlignAddressForward
//		RemoveIfOrderPreserving
//		RemoveIf
//		AreIntervalsIntersecting
//		AreBoxesIntersecting
//
//	Aside from inside those functions or main() if you need to disable, do not make any other changes. 
//	
//	Spend at most an hour on the test. 
//	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

//	Helper macro, checks if a condition passed - printing the line and asserting if it fails.
#define TEST_CONDITION(cond) { if(!(cond)) { printf("Test failed! Line: %d\n", __LINE__); assert(false); } }

//	Function pointer type used for predicate
typedef bool(*PredicateFunctionPointer)(int Element);

//	Basic 3D box
struct Box3D
{
	float	MinX;
	float	MinY;
	float	MinZ;
	float	MaxX;
	float	MaxY;
	float	MaxZ;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	AlignAddressForward
//
//	Take an address and an alignment size, and return a new address that:
//		1) divided by the alignment, it has no remainder
//		2) it's not less than the input address provided (it's aligned to the next perfect divisor)
//
//	Example: AlignAddressForward(5, 4) -> 8, which is the next address >= 1 that divided by 4 has a remainder of 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

intptr_t AlignAddressForward(intptr_t Address, int Alignment)
{

	int remainder = Address % Alignment;
	if (remainder == 0) return Address;
	return Address + (Alignment - remainder);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	
//	RemoveIfOrderPreserving
//	
//	RemoveIfOrderPreserving modifies the Array in-place so the elements for which the predicate pred returns true do not appear anymore;
//	it returns the length of the modified Array (which will be <= the original ArrayLength)
//	The order of the non-deleted elements does have to be preserved
//
//	Example: 
//	int Array[] = {1,2,3,4,5,6};
//	bool isEven(int Element) { return ( Element & 1 ) == 0; }
//	RemoveIfOrderPreserving(Array, 6, isEven) should return 3, and modify Array so the first three elements are 1,3,5 (in this order!)
//	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int RemoveIfOrderPreserving(int* Array, int ArrayLength, PredicateFunctionPointer Pred)
{

	// Tried to do a more space efficient algorithm to swap everything in place -
	// however could not think of a way to shift all elements down with each true Pred,
	// without boosting time complexity to almost O(n^2).
	// Given lack of time to think of anything else, the additional space seems a reasonable compromise
	/*
	int interval = 0;
	int length = ArrayLength;
	for (int i = 0; i < ArrayLength; i ++) {
		int val = *(Array + i);
		if (Pred(val)) {
			// record how many in a row we hit
			interval ++;
		} else {
			// flush the interval
			for (int j = 0; j < interval; j++) {
				*(Array + i - interval + j) = *(Array + i + j);
			}
			length -= interval;
			interval = 0;
			i -= interval;
		}
	}
	return length;*/

	// temporary array to store elements in
	int *new_array = (int*)malloc(ArrayLength * sizeof(int));
	int new_arr_idx = 0;

	// loop and test each element
	for (int i = 0; i < ArrayLength; i++) {
		int val = *(Array + i);
		if (!Pred(val)) {
			*(new_array + new_arr_idx) = val;
			new_arr_idx++;
		}
	}

	// copy temp array to original and clenaup
	for (int i = 0; i < new_arr_idx; i++) {
		*(Array + i) = *(new_array + i);
	}
	free(new_array);

	return new_arr_idx;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	
//	RemoveIf
//
//	RemoveIf modifies the Array in-place so the elements for which the predicate pred returns true do not appear anymore;
//	it returns the length of the modified Array (should be <= the original ArrayLength)
//	The order of the non-deleted elements does not have to be preserved
//
//	Example: 
//	int Array[] = {1,2,3,4,5,6};
//	bool isEven(int element) { return ( element & 1 ) == 0; }
//	RemoveIf(Array, 6, isEven) should return 3, and modify Array so the first three elements are 1,3,5 (possibly not in this order)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int RemoveIf(int* Array, int ArrayLength, PredicateFunctionPointer Pred)
{

	// Cannot reduce time complexity from O(n) as must iterate over every element -
	// Only way to reduce space is to swap elements in place,
	// but cannot think of how to do so without increasing time.
	// Using same algorithm for time
	return RemoveIfOrderPreserving(Array, ArrayLength, Pred);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	
//	AreIntervalsIntersecting
//
//	Returns true if the two intervals [i1Start, i1End], [i2Start, i2End] overlap
//	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AreIntervalsIntersecting(float i1Start, float i1End, float i2Start, float i2End)
{
	
	return (i1End > i2Start && i1Start < i2End);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	
//	Returns true if the two 3d boxes overlap. Two boxes do not overlap if they are side by side (same logic as AreIntervalsIntersecting)
//	The boxes are defined by two corners, "min" and "max" which have the property that:
//	- in "min" each coordinate is smaller than any other coordinate of any other corner
//	- in "max" each coordinate is larger than any other coordinate of any other corner
//	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Vector3 {
	float x;
	float y;
	float z;
};

bool AreBoxesIntersecting(const Box3D Box1, const Box3D Box2)
{

	Vector3 Min1 = {Box1.MinX, Box1.MinY, Box1.MinZ};
	Vector3 Max1 = {Box1.MaxX, Box1.MaxY, Box1.MaxZ};

	Vector3 Min2 = {Box2.MinX, Box2.MinY, Box2.MinZ};
	Vector3 Max2 = {Box2.MaxX, Box2.MaxY, Box2.MaxZ};
	
	// do axes intersect
	bool xIntersect = AreIntervalsIntersecting(Min1.x, Max1.x, Min2.x, Max2.x);
	bool yIntersect = AreIntervalsIntersecting(Min1.y, Max1.y, Min2.y, Max2.y);
	bool zIntersect = AreIntervalsIntersecting(Min1.z, Max1.z, Min2.z, Max2.z);

	return xIntersect && yIntersect && zIntersect;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	AddressTestValues
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const uint64_t AddressTestValues[] = {
	0x4a86cf1bcadf75de, 0x2fa246329c61f766, 0xf31e7e29e0802d96, 0xf0d194479b0d1e19, 
	0x91ba2480239cde84,	0x6caa71b224f2404e, 0x1f6f4809e236170e, 0x25e8837ecdb9c1b0, 
	0xfe758d0cdec40b20, 0xa6d8ffced84ac2d2, 0x811ca15046fbf2c5, 0x7e19d63fe20c5031, 
	0xc3a0353774662c1e, 0x38f6f78aacb91a7e, 0x4134c414b435c9b2, 0xa7ec20ec2d6ed109, 
	0xfbfbbe3aa77abb85, 0xfee4198f60567667, 0xa7d17e7c787bc64a, 0xfa5833f742632569, 
	0xe3f3280398ae981c, 0x43be329e0558a512, 0x4bf1b04f8d0eed08, 0xf1ace3037feaf293, 
	0xe3273cd529f42146, 0x27b760288a09200d, 0xac1990fd635703f4, 0x3133784c7e0ca543, 
	0xc8eb6f4267b747b6, 0xfafc51b6ed09d08b
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	TEST_AlignAddressToNext
//
//	Test function. Do *not* modify.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TEST_AlignAddressToNext()
{
	int		i;
	int		j;
	int		TestValueIndex = 0;

	for(j = 2; j < 5; j++)
	{
		for(i = 0; i < 10; i++)
		{
			intptr_t	Test = (intptr_t)AddressTestValues[TestValueIndex++];

			intptr_t	Result = AlignAddressForward(Test, j);

			TEST_CONDITION((Result % j) == 0);
			TEST_CONDITION((Result >= Test));
		}
	}
}

bool IsEven(int element)
{
	return	((element & 1) == 0);
}

int		sMoreThanElement = 0;
bool isMoreThan(int element)
{
	return	(element > sMoreThanElement);
}

void TEST_RemoveIfOrderPreserving()
{
	{
		int		Array[] = { 1,2,3,4,5,6 };
		int		NewLength = RemoveIfOrderPreserving(Array, 6, IsEven);

		TEST_CONDITION(NewLength == 3);
		TEST_CONDITION(Array[0] == 1);
		TEST_CONDITION(Array[1] == 3);
		TEST_CONDITION(Array[2] == 5);
	}

	{
		int		Array[] = { 1,2,3,4,5,6 };

		sMoreThanElement = 4;
		int		NewLength = RemoveIfOrderPreserving(Array, 6, isMoreThan);

		TEST_CONDITION(NewLength == 4);
		TEST_CONDITION(Array[0] == 1);
		TEST_CONDITION(Array[1] == 2);
		TEST_CONDITION(Array[2] == 3);
		TEST_CONDITION(Array[3] == 4);

		sMoreThanElement = 2;
		NewLength = RemoveIfOrderPreserving(Array, NewLength, isMoreThan);

		TEST_CONDITION(NewLength == 2);
		TEST_CONDITION(Array[0] == 1);
		TEST_CONDITION(Array[1] == 2);

		sMoreThanElement = -1;
		TEST_CONDITION(RemoveIfOrderPreserving(Array, NewLength, isMoreThan) == 0);
	}
}

void TEST_RemoveIf()
{
	int		i;

	{
		int		Array[] = { 1,2,3,4,5,6 };
		int		NewLength = RemoveIf(Array, 6, IsEven);

		TEST_CONDITION(NewLength == 3);
		for (int i = 0; i < NewLength; i++)
		{
			TEST_CONDITION(!IsEven(Array[i]));
		}
	}

	{
		int		Array[] = { 1,2,3,4,5,6 };

		sMoreThanElement = 4;
		int		NewLength = RemoveIf(Array, 6, isMoreThan);

		TEST_CONDITION(NewLength == 4);
		for(i = 0; i < NewLength; i++)
		{
			TEST_CONDITION(!isMoreThan(Array[i]));
		}

		sMoreThanElement = 2;
		NewLength = RemoveIf(Array, NewLength, isMoreThan);

		TEST_CONDITION(NewLength == 2);
		for(i = 0; i < NewLength; i++)
		{
			TEST_CONDITION(!isMoreThan(Array[i]));
		}

		sMoreThanElement = -1;
		TEST_CONDITION(RemoveIf(Array, NewLength, isMoreThan) == 0);
	}
}

void TEST_AreIntervalsIntersecting()
{
	TEST_CONDITION(AreIntervalsIntersecting(0.0f, 1.0f, 2.0f, 3.0f) == false);
	TEST_CONDITION(AreIntervalsIntersecting(0.0f, 1.0f, 0.5f, 2.0f) == true);	
	TEST_CONDITION(AreIntervalsIntersecting(0.0f, 1.0f, -3.0f, -2.0f) == false);		
	TEST_CONDITION(AreIntervalsIntersecting(0.0f, 1.0f, 0.0f, 1.0f) == true);
	TEST_CONDITION(AreIntervalsIntersecting(0.0f, 1.0f, 0.5f, 1.0f) == true);	
	TEST_CONDITION(AreIntervalsIntersecting(0.0f, 1.0f, -0.5f, 0.5f) == true);
	TEST_CONDITION(AreIntervalsIntersecting(0.0f, 1.0f, 1.0f, 2.0f) == false);
}

void TEST_AreBoxesIntersecting()
{
	{
		Box3D	Box1 = { 0.f, 0.f, 0.f, 1.f, 1.f, 1.f };
		Box3D	Box2 = { 0.f, 0.f, 0.5f, 1.f, 1.f, 1.5f };
		TEST_CONDITION(AreBoxesIntersecting(Box1, Box2) == true);
	}

	{
		Box3D	Box1 = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
		Box3D	Box2 = { 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f };
		TEST_CONDITION(AreBoxesIntersecting(Box1, Box2) == false);
	}

	{
		Box3D	Box1 = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
		Box3D	Box2 = { 1.0f, 1.0f, 0.0f, 2.0f, 2.0f, 1.0f };
		TEST_CONDITION(AreBoxesIntersecting(Box1, Box2) == false);
	}

	{
		Box3D	Box1 = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
		Box3D	Box2 = { 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f };
		TEST_CONDITION(AreBoxesIntersecting(Box1, Box2) == false);
	}

	{
		Box3D	Box1 = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
		Box3D	Box2 = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
		TEST_CONDITION(AreBoxesIntersecting(Box1, Box2) == true);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	main
//
//	Comment out any of the tests if you become stuck on them
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	TEST_AlignAddressToNext();

	TEST_RemoveIfOrderPreserving();

	TEST_RemoveIf();

	TEST_AreIntervalsIntersecting();

	TEST_AreBoxesIntersecting();

	printf("All tests passed. :)\n");
    
    return	0;
}