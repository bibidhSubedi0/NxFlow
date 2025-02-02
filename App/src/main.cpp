#include "../../CoreLibrary/include/public/Training.h"
#include <fstream>
#include <vector>
#include<memory>

using namespace std;


int main()
{

	// To Test loading the model
	std::unique_ptr<CoreLib::Training> Train = std::make_unique<CoreLib::Training>();
	Train->loadModel("model.bin");
	std::vector<double> output = Train->predict({ 0,0,1 });

	std::cout << "Result : " << std::endl;
	for (auto x : output)
	{
		std::cout << x << "\t ";
	}




	// To test saving the model 
	/*
	vector<vector<double>> inputs{
	   {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, { 0, 1, 1}, { 1, 0, 0}, { 1, 0, 1}, { 1, 1, 0}, { 1, 1, 1}

	};

	vector<vector<double>> targets{
		{1, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1 },

	};





	double lr = 0.01;// { 0.01, 0.1, , 1 };
	vector<int> topology = { (int)inputs[0].size(),8,8,(int)targets[0].size() };


	std::unique_ptr<CoreLib::Training> Train = std::make_unique<CoreLib::Training>(400, lr, topology);

	Train->trainModel(inputs, targets);
	Train->saveModel("model.bin");
	*/

}


