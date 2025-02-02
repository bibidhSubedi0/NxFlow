#ifndef _Network_HPP_
#define _Network_HPP_

#include <iostream>
#include "Matrix.h"
#include "Layer.h"
#include <vector>
using namespace std;

class Network
{
public:
    Network(vector<int> topology, double learningRate);
    Network(vector<int> topology);
    void setCurrentInput(vector<double> input);
    void printToConsole();
    void printWeightMatrices();
    void printBiases();
    void forwardPropogationTrain();
    void forwardPropogationPred();
    Layer* GetLayer(int nth);

    void setErrors();
    void setTarget(vector<double> target);

    void printErrors();
    double getGlobalError();
    double lastEpoachError();
    void printHistErrors();
    void saveHistErrors();
    double getLearningRate();
    void setErrorDerivatives();
    vector<double> gethisterrors();
    void updateWeights();
    vector<Matrix*> gardientComputation();
    vector<Matrix*> averageGradients(vector<vector<Matrix*>>);
    void saveThisError(double error);
    vector<vector<vector<double>>> getWeightMatricesVectorForm();
    vector<vector<double>> getBiasesVectorForm();
    void setNetworkFromModel(std::vector<int>& topologyLoaded, std::vector<std::vector<std::vector<double>>>& weights, std::vector<std::vector<double>>& biases, const std::string& filename);

    void setWeightMatrices(std::vector<std::vector<std::vector<double>>>& weights);
    void setBiasMatrices(std::vector<std::vector<double>>& biases);

private:
    int topologySize;
    vector<int> topology;
    vector<Layer*> layers;
    vector<Matrix*> weightMatrices;
    vector<Matrix*> GradientMatrices;
    vector<double> input;
    vector<Matrix*> BaisMatrices;
    double error;
    vector<double> target;
    vector<double> errors;
    vector<double> histErrors;
    vector<double> errorDerivatives;
    double learningRate;



};

#endif
