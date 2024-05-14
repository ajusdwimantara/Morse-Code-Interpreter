#include "include/AI.cpp"
#include "include/data.cpp"

#define training false

int main(){
    ArtificialNeuralNetwork nn1;
    data data1;
    float* inp;
    float* out;

    if(!training){
        nn1.loadModel();
    }
    else{
        for(int i=0;i<2000;i++){
            for(int j=0;j<129;j++){
                inp = data1.input[j];
                out = data1.output[j];
                
                nn1.insertInput(inp);
                nn1.insertOutput(out);

                nn1.feedForward1();
                nn1.feedForward2();
                nn1.computeError();
                nn1.backPropagation1();
                nn1.backPropagation2();

                
            }
            if(i%500 == 0){
                nn1.displayLoss();
            }
            if(nn1.getAlpha()>0.1){
                nn1.setAlpha(nn1.getAlpha()*0.95);
                
            }
            
        }

    }
    // nn1.displayOutput();
    std::cout<<"OK\n";
    int dat = 65;
    for(int i=0;i<5*26;i=i+5){
        inp = data1.input[i];

        nn1.insertInput(inp);
        
        nn1.feedForward1();
        nn1.feedForward2();
        // nn1.computeError();
        char chr_data = static_cast<char>(dat);
        std::cout<<"data: "<<chr_data<<'\n';
        nn1.displayOutput();
        std::cout<<'\n';
        dat++;
    }

    float input[11];
    bool testing = true;
    char chs;
    while(testing){
        std::cout<<"Enter 11 input: ";
        for(int i=0;i<11;i++){
            std::cin>>input[i];
            input[i] = input[i]/1000;
            std::cout<<input[i]<<'\n';
        }

        nn1.insertInput(input);
        // nn1.insertOutput(data1.output[i][0], data1.output[i][1], data1.output[i][2], data1.output[i][3]);

        nn1.feedForward1();
        nn1.feedForward2();
        // nn1.computeError();
        nn1.displayOutput();

        std::cout<<"again?(y/n) : ";
        std::cin>>chs;

        if((chs=='n')||(chs=='N')){
            testing = false;
        }
    }

    if(training){
        // save model
        // nn1.saveModel();
        nn1.displayFeatures();
    }
    // nn1.insertInput(0.7, 0.2);
    // // nn1.insertOutput(data1.output[i][0], data1.output[i][1], data1.output[i][2], data1.output[i][3]);

    // nn1.feedForward1();
    // nn1.feedForward2();
    // // nn1.computeError();
    // nn1.displayOutput();

}