#include "AI.h"
// #include "data.cpp"

ArtificialNeuralNetwork::ArtificialNeuralNetwork(){

    /* Randomize Hidden Layer */
    srand (time(NULL));

    std::cout<<"Randomize Wij: \n";
    for(int i=0; i<INPUT_NETWORK; i++) {
        for(int j=0; j<HIDDEN_NETWORK; j++) {
            Wij[i][j] = (rand()%10) /10.0;
        }
    }
    // for(int i=0; i<INPUT_NETWORK; i++) {
    //     for(int j=0; j<HIDDEN_NETWORK; j++) {
    //         std::cout<<"Wij"<<i+1<<j+1<<": "<<Wij[i][j]<<'\n';
    //     }
    // }
    std::cout<<"Randomize Hidden Threshold: \n";
    for(int i=0; i<HIDDEN_NETWORK;i++) {
        threshold_hidden[i] = (rand()%10) /10.0;
        // std::cout<<"Threshold j["<<i<<"]: "<<threshold_hidden[i]<<'\n';
    }

    /* Randomize Output Layer */
    srand (time(NULL));

    std::cout<<"Randomize Wjk: \n";
    for(int i=0; i<HIDDEN_NETWORK; i++) {
        for(int j=0; j<OUTPUT_NETWORK; j++) {
            Wjk[i][j] = (rand()%10) /10.0;
        }
    }
    // for(int i=0; i<HIDDEN_NETWORK; i++) {
    //     for(int j=0; j<OUTPUT_NETWORK; j++) {
    //         std::cout<<"Wjk"<<i+1<<j+1<<": "<<Wjk[i][j]<<'\n';
    //     }
    // }

    std::cout<<"Randomize Output Threshold: \n";
    for(int i=0; i<OUTPUT_NETWORK;i++) {
        threshold_output[i] = (rand()%10) /10.0;
        // std::cout<<"Threshold k["<<i<<"]: "<<threshold_output[i]<<'\n';
    }

    // alpha
    alpha = 0.1;
}

ArtificialNeuralNetwork::~ArtificialNeuralNetwork(){}


void ArtificialNeuralNetwork::feedForward1(){
    // Reset
    for(int j=0; j<HIDDEN_NETWORK; j++) {
        s_hidden[j] = 0;
    }
    // Calculate Strength Hidden
    for(int j=0; j<HIDDEN_NETWORK; j++) {
        int i_temp;
        for(int i=0; i<INPUT_NETWORK; i++) {
            s_hidden[j] += input[i]*Wij[i][j];
            i_temp = i;
        }
        std::cout<<"Wij: "<<Wij[i_temp][j]<<'\n';
    }
    for(int j=0; j<HIDDEN_NETWORK; j++) {
        s_hidden[j] -= threshold_hidden[j];
    }

    // Calculate Activation Function Hidden
    for(int j=0; j<HIDDEN_NETWORK; j++) {
        // Sigmoid
        y_hidden[j] = 1/(1 + exp(-s_hidden[j]));

        // ReLu
        // y_hidden[j] = max(0.0, s_hidden[j]);

        // Leaky ReLu
        // y_hidden[j] = leakyReLU(s_hidden[j]);
        std::cout<<"y_hidden: "<<y_hidden[j]<<'\n';
    }
}

void ArtificialNeuralNetwork::feedForward2(){
    // Reset
    for(int k=0; k<OUTPUT_NETWORK; k++) {
        s_output[k] = 0;
        // std::cout<<"s output "<<k<<": "<<s_output[k]<<"\n";
    }
    // Calculate Output Strength
     for(int k=0; k<OUTPUT_NETWORK; k++) {
        for(int j=0; j<HIDDEN_NETWORK; j++) {
            s_output[k] += y_hidden[j]*Wjk[j][k];
        }
    }
    for(int k=0; k<OUTPUT_NETWORK; k++) {
        s_output[k] -= threshold_output[k];
        // std::cout<<"s output "<<k<<": "<<s_output[k]<<"\n";
    }
    

    // Calculate Activation Function
    for(int k=0; k<OUTPUT_NETWORK; k++) {
        // Sigmoid
        // y_output[k] = 1/(1 + exp(-s_output[k]));

        // ReLu
        // y_output[k] = max(0.0, s_output[k]);

        // Softmax
        double sumExp = 0.0;

        // Compute the sum of exponentials of input values
        for (float val : s_output) {
            sumExp += std::exp(val);
        }
        y_output[k] = (std::exp(s_output[k]) / sumExp);
        
        // std::cout<<"y output "<<k<<": "<<y_output[k]<<"\n";


    }
}

void ArtificialNeuralNetwork::computeError(){
    float total_err = 0;
    cost = 0;
    for(int k=0;k<OUTPUT_NETWORK;k++){
        error[k] = output_target[k] - y_output[k];
        // total_err += error[k];
        cost += pow(error[k], 2);
        // std::cout<<"error "<<k<<": "<<error[k]<<'\n';
    }
    // cost = 1/2*pow(total_err, 2);
    cost = cost/2;
    // std::cout<<"cost: "<<cost<<'\n';
}

void ArtificialNeuralNetwork::displayLoss(){
    std::cout<<"cost: "<<this->cost<<'\n';
}

// void ArtificialNeuralNetwork::backPropagation1(){
//     //reset
//     gradient_temp = 0;
//     for(int j=0; j<HIDDEN_NETWORK; j++) {
//         for(int k=0; k<OUTPUT_NETWORK; k++) {
//             // std::cout<<"Wjk"<<i+1<<j+1<<": "<<Wjk[j][i]<<'\n';
//             Wjk[j][k] -= alpha * (-error[k]*exp(-s_output[k])*y_hidden[j])/pow((1+exp(-s_output[k])), 2);
//             if(j==0){
//                 gradient_temp += (-error[k]*exp(-s_output[k]))/pow((1+exp(-s_output[k])), 2);
//             }
//         }
//         // std::cout<<"gradient temp: "<<gradient_temp<<'\n';
//     }

//     for(int k=0;k<OUTPUT_NETWORK;k++){
//         threshold_output[k] -= alpha * (error[k]*exp(-s_output[k]))/pow((1+exp(-s_output[k])), 2);
//         // std::cout<<"Threshold k["<<k<<"]: "<<threshold_output[k]<<'\n';
//     }
// }

void ArtificialNeuralNetwork::backPropagation1(){
    //reset
    gradient_temp = 0;
    for(int j=0; j<HIDDEN_NETWORK; j++) {
        for(int k=0; k<OUTPUT_NETWORK; k++) {
            // std::cout<<"Wjk"<<i+1<<j+1<<": "<<Wjk[j][i]<<'\n';
            Wjk[j][k] -= alpha * (-error[k]*y_hidden[j]);
            if(j==0){
                gradient_temp += (-error[k]);
            }
        }
        // std::cout<<"gradient temp: "<<gradient_temp<<'\n';
    }

    for(int k=0;k<OUTPUT_NETWORK;k++){
        threshold_output[k] -= alpha * error[k];
        // std::cout<<"Threshold k["<<k<<"]: "<<threshold_output[k]<<'\n';
    }
}

void ArtificialNeuralNetwork::backPropagation2(){
    // float total_error = 0;
    // for(int k=0;k<4;k++){
    //     total_error += error[k];
    // }
    //reset
    for(int j=0;j<HIDDEN_NETWORK;j++){
        wjk_temp[j] = 0;
    }
    for(int j=0;j<HIDDEN_NETWORK;j++){
        for(int k=0;k<4;k++){
            wjk_temp[j] += Wjk[j][k];
        }
    }
    for(int i=0; i<INPUT_NETWORK; i++) {
        for(int j=0; j<HIDDEN_NETWORK; j++) {
            // std::cout<<"Wij"<<i+1<<j+1<<": "<<Wij[j][i]<<'\n';
            // Wij[i][j] = Wij[i][j] - (-total_error*exp(-s_output[j])*threshold_output[i])/pow((1+exp(-s_output[j])), 2);
            Wij[i][j] -= alpha * gradient_temp*wjk_temp[j]*(exp(-s_hidden[j]))/(pow(1+exp(-s_hidden[j]), 2)) * input[i];
        }
    }

    for(int j=0;j<HIDDEN_NETWORK;j++){
        // threshold_hidden[i] = threshold_hidden[i] - turunan
        threshold_hidden[j] -= alpha * gradient_temp*wjk_temp[j]*(exp(-s_hidden[j]))/(pow(1+exp(-s_hidden[j]), 2)) * (-1);
    }
}

void ArtificialNeuralNetwork::insertInput(float number[]) {
    for(int i=0;i<11;i++){
        this->input[i] = number[i];
    }

}

void ArtificialNeuralNetwork::insertOutput(float number_out[]) {
    for(int i=0;i<35;i++){
        this->output_target[i] = number_out[i];
    }
}

void ArtificialNeuralNetwork::displayFeatures(){
    for(int i=0; i<INPUT_NETWORK; i++) {
        for(int j=0; j<HIDDEN_NETWORK; j++) {
            std::cout<<Wij[i][j]<<", ";
        }
        std::cout<<'\n';
    }

    for(int j=0; j<HIDDEN_NETWORK; j++) {
        std::cout<<threshold_hidden[j]<<", ";
    }
    std::cout<<'\n';
}

void ArtificialNeuralNetwork::displayOutput(){
    int max_index = 0;
    for(int k=0;k<35;k++){
        std::cout<<"y output["<<k+1<<"]"<<y_output[k]<<'\n';
        if(y_output[max_index] < y_output[k]){
            max_index = k;
        }
    }

    int predicted_output[35] = {0};
    predicted_output[max_index] = 1;
    std::cout<<"predicted output: \n";
    // for(int k=0;k<35;k++){
    //     std::cout<<predicted_output[k]<<' ';
    // }
    // std::cout<<'\n';

    std::cout<<static_cast<char>(65+max_index)<<'\n';

    //--write to .txt

    // std::ofstream outputFile;
    // // data predicted_data;
    // std::string outputFileName = "predicted_output.txt";

    // outputFile.open(outputFileName, std::ios_base::app);
    // if(outputFile.is_open())
    // {
    //     std::cout<<"Succed to create file: "<<outputFileName<<'\n';
    //     outputFile <<input[0]<<' ';
    //     outputFile <<input[1]<<' ';

    //     outputFile <<predicted_output[0]<<' ';
    //     outputFile <<predicted_output[1]<<' ';
    //     outputFile <<predicted_output[2]<<' ';
    //     outputFile <<predicted_output[3]<<'\n';

    //     outputFile.close(); 
    // }
    // else
    //     std::cerr<<"Could not create file: "<<outputFileName;
}

double ArtificialNeuralNetwork::getAlpha(){
    return this->alpha;
}

void ArtificialNeuralNetwork::setAlpha(double al){
    this->alpha = al;
}

void ArtificialNeuralNetwork::saveModel(){
    //--write to .txt

    std::ofstream outputFile1;
    // data predicted_data;
    std::string outputFileName1 = "weight_ij.txt";

    outputFile1.open(outputFileName1, std::ios_base::app);
    if(outputFile1.is_open())
    {
        std::cout<<"Succed to create file: "<<outputFileName1<<'\n';
        for(int i=0;i<INPUT_NETWORK;i++){
            for(int j=0;j<HIDDEN_NETWORK-1;j++){
                outputFile1<<Wij[i][j]<<" ";
            }
            outputFile1<<Wij[i][HIDDEN_NETWORK-1]<<"\n";
        }

        outputFile1.close(); 
    }
    else
        std::cerr<<"Could not create file: "<<outputFileName1;
    
    std::ofstream outputFile2;
    // data predicted_data;
    std::string outputFileName2 = "weight_jk.txt";

    outputFile2.open(outputFileName2, std::ios_base::app);
    if(outputFile2.is_open())
    {
        std::cout<<"Succed to create file: "<<outputFileName2<<'\n';
        for(int j=0;j<HIDDEN_NETWORK;j++){
            for(int k=0;k<OUTPUT_NETWORK-1;k++){
                outputFile2<<Wjk[j][k]<<" ";
            }
            outputFile2<<Wjk[j][OUTPUT_NETWORK-1]<<"\n";
        }

        outputFile2.close(); 
    }
    else
        std::cerr<<"Could not create file: "<<outputFileName2;

    std::ofstream outputFile3;
    // data predicted_data;
    std::string outputFileName3 = "threshold_hidden.txt";

    outputFile3.open(outputFileName3, std::ios_base::app);
    if(outputFile3.is_open())
    {
        std::cout<<"Succed to create file: "<<outputFileName3<<'\n';
        for(int j=0;j<HIDDEN_NETWORK-1;j++){
            outputFile3<<threshold_hidden[j]<<" ";
        }
        outputFile3<<threshold_hidden[HIDDEN_NETWORK-1]<<"\n";

        outputFile3.close(); 
    }
    else
        std::cerr<<"Could not create file: "<<outputFileName3;

    std::ofstream outputFile4;
    // data predicted_data;
    std::string outputFileName4 = "threshold_output.txt";

    outputFile4.open(outputFileName4, std::ios_base::app);
    if(outputFile4.is_open())
    {
        std::cout<<"Succed to create file: "<<outputFileName4<<'\n';
        for(int k=0;k<OUTPUT_NETWORK-1;k++){
            outputFile4<<threshold_output[k]<<" ";
        }
        outputFile4<<threshold_output[OUTPUT_NETWORK-1]<<"\n";

        outputFile4.close(); 
    }
    else
        std::cerr<<"Could not create file: "<<outputFileName4;
}

void ArtificialNeuralNetwork::loadModel(){
    std::string fileName1 = "weight_ij.txt";
    std::ifstream inputf1;

    inputf1.open(fileName1);

    int idx1 = 0;

    while(!inputf1.eof()) {
        std::string line[HIDDEN_NETWORK];
        for (int i = 0; i < HIDDEN_NETWORK-1; i++) {
        getline(inputf1, line[i], ' ');
        }

        float number;
        
        inputf1 >> number;

        //same functions, to neglect the white spaces
        // input.get();
        inputf1 >> std::ws;

        // number = std::stof(line[5]);
        // std::cout<<number;

        Wij[idx1][0] = std::stof(line[0]);
        Wij[idx1][1] = std::stof(line[1]);
        Wij[idx1][2] = std::stof(line[2]);
        Wij[idx1][3] = std::stof(line[3]);
        Wij[idx1][4] = std::stof(line[4]);
        Wij[idx1][5] = std::stof(line[5]);
        Wij[idx1][6] = std::stof(line[6]);
        Wij[idx1][7] = std::stof(line[7]);
        Wij[idx1][8] = std::stof(line[8]);
        Wij[idx1][9] = std::stof(line[9]);
        Wij[idx1][10] = std::stof(line[10]);
        Wij[idx1][11] = std::stof(line[11]);
        Wij[idx1][12] = std::stof(line[12]);
        Wij[idx1][13] = std::stof(line[13]);
        Wij[idx1][14] = std::stof(line[14]);
        Wij[idx1][15] = std::stof(line[15]);
        Wij[idx1][16] = std::stof(line[16]);
        Wij[idx1][17] = std::stof(line[17]);
        Wij[idx1][18] = std::stof(line[18]);
        Wij[idx1][19] = std::stof(line[19]);
        Wij[idx1][20] = std::stof(line[20]);
        Wij[idx1][21] = std::stof(line[21]);
        Wij[idx1][22] = std::stof(line[22]);
        Wij[idx1][23] = std::stof(line[23]);
        Wij[idx1][24] = number;

        idx1 += 1;

        // std::cout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " " << line[4] << " " << line[5] << number<<"--" << '\n';
        // for(int i=0;i<2;i++){
        //     std::cout<<in[i]<<" ";
        // }
        // for(int i=0;i<4;i++){
        //     std::cout<<out[i]<<" ";
        // }
        // std::cout<<'\n';
    }

    std::string fileName2 = "weight_jk.txt";
    std::ifstream inputf2;

    inputf2.open(fileName2);

    int idx2 = 0;

    while(!inputf2.eof()) {
        std::string line[OUTPUT_NETWORK];
        for (int i = 0; i < OUTPUT_NETWORK-1; i++) {
        getline(inputf2, line[i], ' ');
        }

        float number;
        
        inputf2 >> number;

        //same functions, to neglect the white spaces
        // input.get();
        inputf2 >> std::ws;

        // number = std::stof(line[5]);
        // std::cout<<number;

        Wjk[idx2][0] = std::stof(line[0]);
        Wjk[idx2][1] = std::stof(line[1]);
        Wjk[idx2][2] = std::stof(line[2]);
        Wjk[idx2][3] = std::stof(line[3]);
        Wjk[idx2][4] = std::stof(line[4]);
        Wjk[idx2][5] = std::stof(line[5]);
        Wjk[idx2][6] = std::stof(line[6]);
        Wjk[idx2][7] = std::stof(line[7]);
        Wjk[idx2][8] = std::stof(line[8]);
        Wjk[idx2][9] = std::stof(line[9]);
        Wjk[idx2][10] = std::stof(line[10]);
        Wjk[idx2][11] = std::stof(line[11]);
        Wjk[idx2][12] = std::stof(line[12]);
        Wjk[idx2][13] = std::stof(line[13]);
        Wjk[idx2][14] = std::stof(line[14]);
        Wjk[idx2][15] = std::stof(line[15]);
        Wjk[idx2][16] = std::stof(line[16]);
        Wjk[idx2][17] = std::stof(line[17]);
        Wjk[idx2][18] = std::stof(line[18]);
        Wjk[idx2][19] = std::stof(line[19]);
        Wjk[idx2][20] = std::stof(line[20]);
        Wjk[idx2][21] = std::stof(line[21]);
        Wjk[idx2][22] = std::stof(line[22]);
        Wjk[idx2][23] = std::stof(line[23]);
        Wjk[idx2][24] = std::stof(line[24]);
        Wjk[idx2][25] = std::stof(line[25]);
        Wjk[idx2][26] = std::stof(line[26]);
        Wjk[idx2][27] = std::stof(line[27]);
        Wjk[idx2][28] = std::stof(line[28]);
        Wjk[idx2][29] = std::stof(line[29]);
        Wjk[idx2][30] = std::stof(line[30]);
        Wjk[idx2][31] = std::stof(line[31]);
        Wjk[idx2][32] = std::stof(line[32]);
        Wjk[idx2][33] = std::stof(line[33]);
        Wjk[idx2][34] = number;

        idx2 += 1;

        // std::cout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " " << line[4] << " " << line[5] << number<<"--" << '\n';
        // for(int i=0;i<2;i++){
        //     std::cout<<in[i]<<" ";
        // }
        // for(int i=0;i<4;i++){
        //     std::cout<<out[i]<<" ";
        // }
        // std::cout<<'\n';
    }

    std::string fileName3 = "threshold_hidden.txt";
    std::ifstream inputf3;

    inputf3.open(fileName3);

    int idx3 = 0;

    while(!inputf3.eof()) {
        std::string line[HIDDEN_NETWORK];
        for (int i = 0; i < HIDDEN_NETWORK-1; i++) {
        getline(inputf3, line[i], ' ');
        }

        float number;
        
        inputf3 >> number;

        //same functions, to neglect the white spaces
        // input.get();
        inputf3 >> std::ws;

        // number = std::stof(line[5]);
        // std::cout<<number;

        threshold_hidden[0] = std::stof(line[0]);
        threshold_hidden[1] = std::stof(line[1]);
        threshold_hidden[2] = std::stof(line[2]);
        threshold_hidden[3] = std::stof(line[3]);
        threshold_hidden[4] = std::stof(line[4]);
        threshold_hidden[5] = std::stof(line[5]);
        threshold_hidden[6] = std::stof(line[6]);
        threshold_hidden[7] = std::stof(line[7]);
        threshold_hidden[8] = std::stof(line[8]);
        threshold_hidden[9] = std::stof(line[9]);
        threshold_hidden[10] = std::stof(line[10]);
        threshold_hidden[11] = std::stof(line[11]);
        threshold_hidden[12] = std::stof(line[12]);
        threshold_hidden[13] = std::stof(line[13]);
        threshold_hidden[14] = std::stof(line[14]);
        threshold_hidden[15] = std::stof(line[15]);
        threshold_hidden[16] = std::stof(line[16]);
        threshold_hidden[17] = std::stof(line[17]);
        threshold_hidden[18] = std::stof(line[18]);
        threshold_hidden[19] = std::stof(line[19]);
        threshold_hidden[20] = std::stof(line[20]);
        threshold_hidden[21] = std::stof(line[21]);
        threshold_hidden[22] = std::stof(line[22]);
        threshold_hidden[23] = std::stof(line[23]);
        threshold_hidden[24] = number;

        idx3 += 1;

        // std::cout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " " << line[4] << " " << line[5] << number<<"--" << '\n';
        // for(int i=0;i<2;i++){
        //     std::cout<<in[i]<<" ";
        // }
        // for(int i=0;i<4;i++){
        //     std::cout<<out[i]<<" ";
        // }
        // std::cout<<'\n';
    }

    std::string fileName4 = "threshold_output.txt";
    std::ifstream inputf4;

    inputf4.open(fileName4);

    int idx4 = 0;

    while(!inputf4.eof()) {
        std::string line[OUTPUT_NETWORK];
        for (int i = 0; i < OUTPUT_NETWORK-1; i++) {
        getline(inputf4, line[i], ' ');
        }

        float number;
        
        inputf4 >> number;

        //same functions, to neglect the white spaces
        // input.get();
        inputf4 >> std::ws;

        // number = std::stof(line[5]);
        // std::cout<<number;

        threshold_output[0] = std::stof(line[0]);
        threshold_output[1] = std::stof(line[1]);
        threshold_output[2] = std::stof(line[2]);
        threshold_output[3] = std::stof(line[3]);
        threshold_output[4] = std::stof(line[4]);
        threshold_output[5] = std::stof(line[5]);
        threshold_output[6] = std::stof(line[6]);
        threshold_output[7] = std::stof(line[7]);
        threshold_output[8] = std::stof(line[8]);
        threshold_output[9] = std::stof(line[9]);
        threshold_output[10] = std::stof(line[10]);
        threshold_output[11] = std::stof(line[11]);
        threshold_output[12] = std::stof(line[12]);
        threshold_output[13] = std::stof(line[13]);
        threshold_output[14] = std::stof(line[14]);
        threshold_output[15] = std::stof(line[15]);
        threshold_output[16] = std::stof(line[16]);
        threshold_output[17] = std::stof(line[17]);
        threshold_output[18] = std::stof(line[18]);
        threshold_output[19] = std::stof(line[19]);
        threshold_output[20] = std::stof(line[20]);
        threshold_output[21] = std::stof(line[21]);
        threshold_output[22] = std::stof(line[22]);
        threshold_output[23] = std::stof(line[23]);
        threshold_output[24] = std::stof(line[24]);
        threshold_output[25] = std::stof(line[25]);
        threshold_output[26] = std::stof(line[26]);
        threshold_output[27] = std::stof(line[27]);
        threshold_output[28] = std::stof(line[28]);
        threshold_output[29] = std::stof(line[29]);
        threshold_output[30] = std::stof(line[30]);
        threshold_output[31] = std::stof(line[31]);
        threshold_output[32] = std::stof(line[32]);
        threshold_output[33] = std::stof(line[33]);
        threshold_output[34] = number;

        idx4 += 1;

        // std::cout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " " << line[4] << " " << line[5] << number<<"--" << '\n';
        // for(int i=0;i<2;i++){
        //     std::cout<<in[i]<<" ";
        // }
        // for(int i=0;i<4;i++){
        //     std::cout<<out[i]<<" ";
        // }
        // std::cout<<'\n';
    }
}