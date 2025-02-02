#define CORELIB_EXPORTS
#include <../include/public/Training.h>

#include <iostream>
#include<fstream>
#include<memory>

namespace CoreLib {

	Training::Training(int epochs, double learningRate, std::vector<int> topology) : m_epochs(epochs), m_learningRate(learningRate), topology(topology) {
		this->Net = std::make_unique<Network>(topology, learningRate);
	}

	void Training::trainModel(const std::vector<std::vector<double>>& data, const std::vector<std::vector<double>>& labels) {
		std::cout << "Training model for " << m_epochs << " epochs with learning rate " << m_learningRate << std::endl;


		double error_for_epoch = 0;
		vector<double> avg_error_over_epoch;

		for (int epochs = 0; epochs < this->m_epochs; epochs++)
		{
			cout << "Epoch : " << epochs << endl;;
			error_for_epoch = 0;
			for (int j = 0; j < data.size(); j++)
			{

				this->Net->setCurrentInput(data[j]);
				this->Net->setTarget(labels[j]);

				this->Net->forwardPropogation();
				this->Net->setErrors();
				error_for_epoch += this->Net->getGlobalError();

				vector<Matrix* > grad = this->Net->gardientComputation();
				vector<vector<Matrix*>> allGradientsInOneEpoch;
				allGradientsInOneEpoch.push_back(grad);
				vector<Matrix*> avgG = this->Net->averageGradients(allGradientsInOneEpoch);

				this->Net->updateWeights();
			}
			avg_error_over_epoch.push_back(error_for_epoch / 7);

		}

		std::cout << "Training Complete : \n";
	}

	std::vector<double> Training::predict(const std::vector<double>& data)
	{
		Net->setCurrentInput(data);
		Net->forwardPropogation();
		Net->setErrors();
		

		std::vector<double> result;

		//  std::cout << "FUclkkxxxxxxxx" << std::endl;

		for (int i = 0;i < this->topology.at(this->topology.size()-1);i++){
			result.push_back(this->Net->GetLayer(this->topology.size() - 1)->getNeuron(i)->getActivatedVal());
		}
		return result;
	}
	
	void Training::saveModel(const std::string filename)
	{
		// this->topology
		std::vector<std::vector<std::vector<double>>> weights = Net->getWeightMatricesVectorForm();	
		std::vector<std::vector<double>> biases = Net->getBiasesVectorForm();

		std::ofstream file(filename, std::ios::binary);
		if (!file) {
			std::cerr << "Error opening file for writing!\n";
			return;
		}

		int layers = topology.size();
		file.write(reinterpret_cast<const char*>(&layers), sizeof(int));
		file.write(reinterpret_cast<const char*>(topology.data()), layers * sizeof(int));

		for (const auto& layerWeights : weights) {
			for (const auto& neuronWeights : layerWeights) {
				file.write(reinterpret_cast<const char*>(neuronWeights.data()), neuronWeights.size() * sizeof(double));
			}
		}

		for (const auto& layerBiases : biases) {
			file.write(reinterpret_cast<const char*>(layerBiases.data()), layerBiases.size() * sizeof(double));
		}

		file.close();

	}

	void Training::loadModel(const std::string filename)
	{
		std::vector<std::vector<std::vector<double>>> weights;// = Net->getWeightMatricesVectorForm();
		std::vector<std::vector<double>> biases;// = Net->getBiasesVectorForm();


		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			std::cerr << "Error opening file for reading!\n";
			return;
		}

		int layers;
		file.read(reinterpret_cast<char*>(&layers), sizeof(int));
		topology.resize(layers);
		file.read(reinterpret_cast<char*>(topology.data()), layers * sizeof(int));

		weights.resize(layers - 1);
		biases.resize(layers - 1);

		for (int i = 0; i < layers - 1; ++i) {
			weights[i].resize(topology[i + 1], std::vector<double>(topology[i]));
			for (auto& neuronWeights : weights[i]) {
				file.read(reinterpret_cast<char*>(neuronWeights.data()), neuronWeights.size() * sizeof(double));
			}
		}

		for (int i = 0; i < layers - 1; ++i) {
			biases[i].resize(topology[i + 1]);
			file.read(reinterpret_cast<char*>(biases[i].data()), biases[i].size() * sizeof(double));
		}

		file.close();
	}
	
} // namespace CoreLib
