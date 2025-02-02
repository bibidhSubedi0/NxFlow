#ifndef CORELIB_TRAINING_H
#define CORELIB_TRAINING_H

#ifdef _WIN32
#ifdef CORELIB_EXPORTS
#define CORELIB_API __declspec(dllexport)
#else
#define CORELIB_API __declspec(dllimport)
#endif
#else
#define CORELIB_API
#endif


#include <vector>  // Keep includes minimal!
#include <../include/core/TotalNetwork.h>

namespace CoreLib {

    class CORELIB_API Training {
    public:
        Training(int epochs, double learningRate, std::vector<int> topology);

        void trainModel(const std::vector<std::vector<double>>& data,
            const std::vector<std::vector<double>>& labels);

        std::vector<double> predict(const std::vector<double>& data);

        void saveModel(const std::string);

        void loadModel(const std::string);

    private:
        int m_epochs;
        double m_learningRate; 
        std::unique_ptr<Network> Net;
        std::vector<int> topology;
    }; 

} // namespace CoreLib

#endif // CORELIB_TRAINING_H
