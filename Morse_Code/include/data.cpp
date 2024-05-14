#include "data.h"

// data::data(){
//     /* Assign the data*/
//     // input
//     input[0][0] = 0.1;
//     input[0][1] = 0.1;

//     input[1][0] = 0.9;
//     input[1][1] = 0.8;

//     input[2][0] = 0.9;
//     input[2][1] = 0.1;
    
//     input[3][0] = 0.2;
//     input[3][1] = 0.2;

//     input[4][0] = 0.1;
//     input[4][1] = 0.8;

//     input[5][0] = 0.8;
//     input[5][1] = 0.1;

//     input[6][0] = 0.2;
//     input[6][1] = 0.7;
    
//     input[7][0] = 0.7;
//     input[7][1] = 0.9;

//     // output
//     output[0][0] = 0;
//     output[0][1] = 0;
//     output[0][2] = 0;
//     output[0][3] = 1;

//     output[1][0] = 1;
//     output[1][1] = 0;
//     output[1][2] = 0;
//     output[1][3] = 0;

//     output[2][0] = 0;
//     output[2][1] = 1;
//     output[2][2] = 0;
//     output[2][3] = 0;

//     output[3][0] = 0;
//     output[3][1] = 0;
//     output[3][2] = 0;
//     output[3][3] = 1;

//     output[4][0] = 0;
//     output[4][1] = 0;
//     output[4][2] = 1;
//     output[4][3] = 0;

//     output[5][0] = 0;
//     output[5][1] = 1;
//     output[5][2] = 0;
//     output[5][3] = 0;

//     output[6][0] = 0;
//     output[6][1] = 0;
//     output[6][2] = 1;
//     output[6][3] = 0;

//     output[7][0] = 1;
//     output[7][1] = 0;
//     output[7][2] = 0;
//     output[7][3] = 0;
// }

data::data(){
  std::string fileName = "data.txt";
  std::ifstream inputf;

  inputf.open(fileName);

  int idx = 0;

  while(!inputf.eof()) {
    std::string line[46];
    float in[11];
    float out[35];
    for (int i = 0; i < 45; i++) {
      getline(inputf, line[i], ' ');
    }

    float number;
    
    inputf >> number;

    //same functions, to neglect the white spaces
    // input.get();
    inputf >> std::ws;

    // number = std::stof(line[5]);
    // std::cout<<number;

    input[idx][0] = std::stof(line[0])/1000;
    input[idx][1] = std::stof(line[1])/1000;
    input[idx][2] = std::stof(line[2])/1000;
    input[idx][3] = std::stof(line[3])/1000;
    input[idx][4] = std::stof(line[4])/1000;
    input[idx][5] = std::stof(line[5])/1000;
    input[idx][6] = std::stof(line[6])/1000;
    input[idx][7] = std::stof(line[7])/1000;
    input[idx][8] = std::stof(line[8])/1000;
    input[idx][9] = std::stof(line[9])/1000;
    input[idx][10] = std::stof(line[10])/1000;

    output[idx][0] = std::stof(line[11]);
    output[idx][1] = std::stof(line[12]);
    output[idx][2] = std::stof(line[13]);
    output[idx][3] = std::stof(line[14]);
    output[idx][4] = std::stof(line[15]);
    output[idx][5] = std::stof(line[16]);
    output[idx][6] = std::stof(line[17]);
    output[idx][7] = std::stof(line[18]);
    output[idx][8] = std::stof(line[19]);
    output[idx][9] = std::stof(line[20]);
    output[idx][10] = std::stof(line[21]);
    output[idx][11] = std::stof(line[22]);
    output[idx][12] = std::stof(line[23]);
    output[idx][13] = std::stof(line[24]);
    output[idx][14] = std::stof(line[25]);
    output[idx][15] = std::stof(line[26]);
    output[idx][16] = std::stof(line[27]);
    output[idx][17] = std::stof(line[28]);
    output[idx][18] = std::stof(line[29]);
    output[idx][19] = std::stof(line[30]);
    output[idx][20] = std::stof(line[31]);
    output[idx][21] = std::stof(line[32]);
    output[idx][22] = std::stof(line[33]);
    output[idx][23] = std::stof(line[34]);
    output[idx][24] = std::stof(line[35]);
    output[idx][25] = std::stof(line[36]);
    output[idx][26] = std::stof(line[37]);
    output[idx][27] = std::stof(line[38]);
    output[idx][28] = std::stof(line[39]);
    output[idx][29] = std::stof(line[40]);
    output[idx][30] = std::stof(line[41]);
    output[idx][31] = std::stof(line[42]);
    output[idx][32] = std::stof(line[43]);
    output[idx][33] = std::stof(line[44]);
    output[idx][34] = number;

    idx += 1;

    // std::cout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " " << line[4] << " " << line[5] << number<<"--" << '\n';
    // for(int i=0;i<2;i++){
    //     std::cout<<in[i]<<" ";
    // }
    // for(int i=0;i<4;i++){
    //     std::cout<<out[i]<<" ";
    // }
    // std::cout<<'\n';
  }

  generateNumber();
}

void data::generateNumber(){
  // for(int i=0;i<26;i++){
  //   // insert input
  //   for(int j=0;j<25;j++){
  //     if(i==0){
  //       one[j] = input[i][j];
  //     }
  //     else if(i==1){
  //       two[j] = input[i][j];
  //     }
  //     else if(i==2){
  //       three[j] = input[i][j];
  //     }
  //     else if(i==3){
  //       four[j] = input[i][j];
  //     }
  //     else if(i==4){
  //       five[j] = input[i][j];
  //     }
  //   }

  //   // insert output
  //   for(int k=0;k<5;k++){
  //     if(i==0){
  //       one_output[k] = output[i][k];
  //     }
  //     else if(i==1){
  //       two_output[k] = output[i][k];
  //     }
  //     else if(i==2){
  //       three_output[k] = output[i][k];
  //     }
  //     else if(i==3){
  //       four_output[k] = output[i][k];
  //     }
  //     else if(i==4){
  //       five_output[k] = output[i][k];
  //     }
  //   }
    
  // }
  
}