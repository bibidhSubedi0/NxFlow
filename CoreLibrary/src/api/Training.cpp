#define CORELIB_EXPORTS
#include <../include/public/Training.h>

#include <iostream>
#include<fstream>
#include<memory>

namespace CoreLib {

	Training::Training(int epochs, double learningRate, std::vector<int> topology) : m_epochs(epochs), m_learningRate(learningRate), m_topology(topology) {
		this->Net = std::make_unique<Network>(topology, learningRate);
	}

	Training::Training()
	{
		this->m_epochs = 0;
		this->m_learningRate = 0;
		this->m_topology = {};
	}

	void Training::loadModel(const std::string filename)
	{
		std::vector<std::vector<std::vector<double>>> weights;// = Net->getWeightMatricesVectorForm();
		std::vector<std::vector<double>> biases;// = Net->getBiasesVectorForm();
		std::vector<int> topology;

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
		this->m_topology = topology;

		this->Net = std::make_unique<Network>(this->m_topology);


		this->Net->setBiasMatrices(biases);
		this->Net->setWeightMatrices(weights);

	}
	// Load model directly through the Train Constructor

	/*Training::Training(int epochs, double learningRate, const std::string filename) : m_epochs(epochs), m_learningRate(learningRate)
	{

	}
	*/
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

				this->Net->forwardPropogationTrain();
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
		//// Verify the network
		//std::cout << "-----------------------------------------------" << std::endl;
		//Net->printToConsole();
		//std::cout << "-----------------------------------------------" << std::endl;
		//Net->printWeightMatrices();
		//std::cout << "-----------------------------------------------" << std::endl;
		//Net->printBiases();
		//std::cout << "-----------------------------------------------" << std::endl;
		Net->setCurrentInput(data);
		Net->forwardPropogationPred();
		// Net->setErrors();
		
		

		std::vector<double> result;

		for (int i = 0;i < this->m_topology.at(this->m_topology.size()-1);i++){
			result.push_back(this->Net->GetLayer(this->m_topology.size() - 1)->getNeuron(i)->getActivatedVal());
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

		int layers = m_topology.size();
		file.write(reinterpret_cast<const char*>(&layers), sizeof(int));
		file.write(reinterpret_cast<const char*>(m_topology.data()), layers * sizeof(int));

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

} // namespace CoreLib
