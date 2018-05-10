#pragma once
#include "glm.hpp"
#include <queue>
#include <chrono>


/*//ExcelFormat
#include "mge\Excel\ExcelFormat.h"
using namespace ExcelFormat;*/

using namespace std;

#include "mge\ExcelLibrary\Xlsx\Workbook.h"
using namespace SimpleXlsx;

class MGEDemo;
class AbstractGame;

class TestManager
{
public:

	TestManager(AbstractGame* game);
	~TestManager();
	void RunTest();

	static string TestManager::currentTest;
	static int run_i;
	static int fps;
	static int objects;
	static int statics;
	static int obbs_percentage;
	static int levels;
	static int updates;
	static long long int collisionTests;
	static long long int collisions;
	static long long int per_loop_collisions;

	static long long int fitTests;
	static long long int overlapTests;

	static int fps_avg;
	static long long int collisions_avg;


	static void start();
	static float time();

	CWorksheet * Sheet;
	CWorkbook * Book;
	std::queue<long long int> data;


private:
	AbstractGame* _game;
	int _numberObjects[10]{ 10,25,50, 100, 250, 500, 1000, 2500, 5000, 10000 };
	float _staticPercentage[5]{ 0.0f,0.25f, 0.50f,0.75f,1.0f };
	float _obbsPercentage[3]{ 0.0f,0.50f,1.0f };
	void StoreData();
	void DataAddEndTestBorder();
	void SetDataFile();
	static std::chrono::steady_clock::time_point _start;

	//void RunNormalOctreeTest();
	void RunTestWithStaticImplementation();
	void ResetDataCounters();
	void TestColliders();

};

