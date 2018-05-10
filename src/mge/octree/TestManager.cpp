#pragma once
#include <iostream>
#include "TestManager.hpp"
#include "mge/MGEDemo.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/octree/Collider.hpp"

/*//ExcelFormat
#include "mge\Excel\ExcelFormat.h"
using namespace ExcelFormat;*/

using namespace std;

#define NUMBER_OF_CICLES 100
#define NUMBER_OF_TESTS 1
#define MAXIMUM_OBJECTS_INDEX 10
#define MAXIMUM_PERCENTAGE_INDEX 5 //normal value 5
#define MAXIMUM_OBB_PERCENTAGE_INDEX 3
#define MAXIMUM_LEVEL 4 // normal value 5


string TestManager::currentTest = "";
int TestManager::run_i = 0;
int TestManager::fps = 0;
int TestManager::objects = 0;
int TestManager::statics = 0;
int TestManager::obbs_percentage = 0;
int TestManager::levels = 0;
int TestManager::updates = 0;
long long int TestManager::collisionTests = 0;
long long int TestManager::collisions = 0;
long long int TestManager::per_loop_collisions = 0;
long long int TestManager::collisions_avg = 0;

std::chrono::steady_clock::time_point TestManager::_start;


long long int TestManager::fitTests = 0;
long long int TestManager::overlapTests = 0;

int TestManager::fps_avg = 0;



TestManager::TestManager(AbstractGame* game) : _game(game)
{
}

TestManager::~TestManager()
{
}


void TestManager::RunTest()
{
	/*RunNormalOctreeTest();
	DataAddEndTestBorder();
	SetDataFile();*/

	RunTestWithStaticImplementation();
	DataAddEndTestBorder();
	SetDataFile();

	//TestColliders();
}

/*void TestManager::RunNormalOctreeTest()
{
	currentTest = "Non-static objects implementation";
	for (int run_index = 0;run_index < NUMBER_OF_TESTS;run_index++) //number of run_index
	{
		run_i = run_index;
		for (int objects_index = 0;objects_index < MAXIMUM_OBJECTS_INDEX;objects_index++) //nuber of objects
		{
			int objectsToCreate = _numberObjects[objects_index];
			objects = objectsToCreate;
			for (int percentage_index = 0;percentage_index < MAXIMUM_PERCENTAGE_INDEX;percentage_index++)
			{
				float percentage = _staticPercentage[percentage_index];
				statics = percentage * 100;
				for (int obb_index = 0;percentage_index < MAXIMUM_OBB_PERCENTAGE_INDEX;percentage_index++)
				{
					float n = _staticPercentage[percentage_index];
					obbs_percentage = n * 100;

					for (int number_levels = 2;number_levels < MAXIMUM_LEVEL;number_levels++)
					{
						levels = number_levels;
						_game->SetOctree(number_levels, 500.0f);
						_game->PopulateGame(objectsToCreate, percentage, obbs_percentage, true);
						start();
						for (int cicle_index = 0;cicle_index < NUMBER_OF_CICLES;cicle_index++)
						{
							_game->Loop();
							fps_avg += fps;
							collisions_avg += collisions;
							updates = cicle_index;
						}
						StoreData();
						ResetDataCounters();
						_game->Reset();
					}

				}

			}
		}
	}
}*/

void TestManager::RunTestWithStaticImplementation()
{
	currentTest = "Static objects-NO OBBs";
	for (int run_index = 0;run_index < 10;run_index++) //number of run_index
	{
		run_i = run_index;
		for (int objects_index = 0;objects_index < 10;objects_index++) //nuber of objects
		{
			int objectsToCreate = _numberObjects[objects_index];
			objects = objectsToCreate;
			for (int percentage_index = 0;percentage_index < 5;percentage_index++)
			{
				float percentage = _staticPercentage[percentage_index];
				statics = percentage * 100;

				//for (int obb_index = 0;obb_index < 3;obb_index++)
				{
					//float n = _obbsPercentage[percentage_index];
					//obbs_percentage = n * 100;
					obbs_percentage = 0;
					for (int number_levels = 0;number_levels < 4;number_levels++)
					{
						levels = number_levels;
						_game->SetOctree(number_levels, 500.0f);
						_game->PopulateGame(objectsToCreate, percentage, 0.0f, true);

						start();
						for (int cicle_index = 0;cicle_index < 100;cicle_index++)
						{
							_game->Loop();
							fps_avg += fps;
							collisions_avg += collisions;
							updates = cicle_index;
						}
						StoreData();
						ResetDataCounters();
						_game->Reset();
					}
				}
			}
		}
	}
}
void TestManager::ResetDataCounters()
{
	fps_avg = 0;
	collisions_avg = 0;
	fitTests = 0;
	collisions = 0;
	collisionTests = 0;
}
void TestManager::TestColliders()
{
	float times[3];
	for (int i = 0;i < 3;i++)
	{
		GameObject go1("gameObject1");
		go1.translate(glm::vec3
		{
			((float)rand() / (float)RAND_MAX) * 50.0f * 2.0f * 0.9f - 50.0f * 0.9f,
			((float)rand() / (float)RAND_MAX) * 50.0f * 2.0f * 0.9f - 50.0f * 0.9f,
			((float)rand() / (float)RAND_MAX) * 50.0f * 2.0f * 0.9f - 50.0f * 0.9f,
		});

		if (i == 0 || i==1)
			go1.createCollider(); //AABB
		else
			go1.createCollider(true); //OBB


		GameObject go2("gameObject2");
		go2.translate(glm::vec3
		{
			((float)rand() / (float)RAND_MAX) * 50.0f * 2.0f * 0.9f - 50.0f * 0.9f,
			((float)rand() / (float)RAND_MAX) * 50.0f * 2.0f * 0.9f - 50.0f * 0.9f,
			((float)rand() / (float)RAND_MAX) * 50.0f * 2.0f * 0.9f - 50.0f * 0.9f,
		});

		if (i == 0)
			go2.createCollider(); //AABB
		else
			go2.createCollider(true); //OBB

		start();
		for (int k = 0;k < 1000000;k++)
		{
			go1._boundingBox->collidesWith(go2._boundingBox);
		}
		times[i] = time();
	}

	cout << "-------------------" << endl;
	cout << "The time required for 1M of checks is:" << endl << endl;
	cout << '\t' << times[0] << "ms for AABB-ABBB." << endl;
	cout << '\t' << times[1] << "ms for AABB-OBB." << endl;
	cout << '\t' << times[2] << "ms for OBB-OBB." << endl << endl;
	cout << "Press ENTER to close the program" << endl;
	cout << "-------------------" << endl;
	std::cin.ignore();
}
void TestManager::StoreData()
{
	float t = time();
	data.push(TestManager::run_i);
	data.push(TestManager::fps_avg / NUMBER_OF_CICLES);
	data.push(TestManager::objects);
	data.push(TestManager::statics);
	data.push(TestManager::levels);
	data.push(TestManager::collisionTests);
	data.push(TestManager::collisions);
	data.push(TestManager::fitTests);
	data.push(TestManager::collisions_avg / NUMBER_OF_CICLES);
	data.push(t);
}
void TestManager::DataAddEndTestBorder()
{
	for (int i = 0;i < 10;i++)
		data.push(-1);
}
void TestManager::SetDataFile()
{
	CWorkbook book("Incognito " + currentTest);
	Book = &book;

	std::vector<ColumnWidth> ColWidth;
	ColWidth.push_back(ColumnWidth(0, 3, 20));
	Sheet = &book.AddSheet("Raw Data " + currentTest, ColWidth);

	Style style;
	style.horizAlign = ALIGN_H_CENTER;
	style.font.attributes = FONT_BOLD;
	size_t CenterStyleIndex = book.AddStyle(style);

	Sheet->BeginRow();
	Sheet->AddCell("Data of test", CenterStyleIndex);
	Sheet->MergeCells(CellCoord(1, 0), CellCoord(1, 3));
	Sheet->EndRow();

	Sheet->BeginRow();
	Sheet->AddCell("Run");
	Sheet->AddCell("FPS");
	Sheet->AddCell("Objects");
	Sheet->AddCell("Statics");
	Sheet->AddCell("Levels");
	Sheet->AddCell("Collision Tests");
	Sheet->AddCell("Collisions");
	Sheet->AddCell("Fit Tests");
	Sheet->AddCell("Per Loop Collisions");
	Sheet->AddCell("Time");
	Sheet->EndRow();

	while (data.empty() == false)
	{
		Sheet->BeginRow();
		for (int i = 0;i < 10;i++)
		{
			Sheet->AddCell(std::to_string(data.front())); //to string because not add cell of long long int and I need the biggest number in C++ 
			data.pop();
		}
		Sheet->EndRow();
	}

	if (book.Save("Simple" + currentTest + ".xlsx")) std::cout << "The book has been saved successfully" << std::endl;
	else std::cout << "The book saving has been failed" << std::endl;
}
void TestManager::start() {
	_start = std::chrono::steady_clock::now();
}
float TestManager::time() {
	//std::chrono::duration<double> diff = std::chrono::steady_clock::now() - _start;
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _start);
	return elapsed.count();
}


