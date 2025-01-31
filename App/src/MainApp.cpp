#include "../include/MainApp.h"
#include "../../CoreLibrary/include/Utils.h"
#include<iostream>

namespace App {
    void runApp() {
        std::cout << "App is running..." << std::endl;
        CoreLibrary::printGreeting(); // Calling the function from CoreLibrary
    }
}
