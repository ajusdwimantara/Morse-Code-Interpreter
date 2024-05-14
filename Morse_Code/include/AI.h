#ifndef _AI_H_
#define _AI_H_

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <fstream>

#define INPUT_NETWORK 11
#define HIDDEN_NETWORK 25 //15
#define OUTPUT_NETWORK 35

class ArtificialNeuralNetwork {
    private:

    // --- Input layer to Hidden layer ----
    double Wij[INPUT_NETWORK][HIDDEN_NETWORK], threshold_hidden[HIDDEN_NETWORK];
    double s_hidden[HIDDEN_NETWORK], y_hidden[HIDDEN_NETWORK];
    float input[INPUT_NETWORK];
    
    // --- Hidden layer to Output layer
    double Wjk[HIDDEN_NETWORK][OUTPUT_NETWORK], threshold_output[OUTPUT_NETWORK];
    double s_output[OUTPUT_NETWORK], y_output[OUTPUT_NETWORK];

    // Target, Error
    double output_target[OUTPUT_NETWORK];
    double error[OUTPUT_NETWORK];
    double cost;

    double gradient_temp = 0;
    double wjk_temp[HIDDEN_NETWORK];

    double alpha;

    public:
    ArtificialNeuralNetwork();
    ~ArtificialNeuralNetwork();

    void feedForward1();
    void feedForward2();

    void computeError();

    void backPropagation1();
    void backPropagation2();

    void insertInput(float number[]);
    void insertOutput(float number_out[]);

    void displayOutput();
    void displayLoss();
    double getAlpha();
    void setAlpha(double al);


    void saveModel();
    void loadModel();

    void displayFeatures();

    float max(float a, float b) {
        return (a > b) ? a : b;
    }

    float leakyReLU(float x, float alpha = 0.001) {
        return (x > 0) ? x : alpha * x;
    }

};

#endif