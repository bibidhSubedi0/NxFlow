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
        
        // This will be for just loading model
        Training();

        Training(int epochs, double learningRate, std::vector<int> topology);
        //Training(int epochs, double learningRate,const std::string filename); // To load the modal Directly


        // trainModel()
        void trainModel(const std::vector<std::vector<double>>& data,
            const std::vector<std::vector<double>>& labels);

        // predict()
        std::vector<double> predict(const std::vector<double>& data);


        // saveModel()
        void saveModel(const std::string);

        // loadModel()
        void loadModel(const std::string);



    private:
        int m_epochs;
        double m_learningRate; 
        std::unique_ptr<Network> Net;
        std::vector<int> m_topology;
    }; 

} // namespace CoreLib

#endif // CORELIB_TRAINING_H
