#include <iostream>
#include <string>

int neuralNetworkMenu(){
    int inputS;
    printf("============ Neural Network Main Menu ============\n");
    printf("1) Begin\n");
    printf("2) Quit\n");
    std::cin >> inputS;
    switch(inputS){
        case 1:
        {
            printf("Welcome! We'll get things set right up for you in a second, \n");
            std::string trainingFileBase;
            std::string testingFileBase;
            printf("First, Enter training directory (no need to end in a /): \n>> ");
            std::cin.ignore();
            getline(std::cin, trainingFileBase);
            if(trainingFileBase.empty()){
                trainingFileBase = "/home/theo/Documents/projects/math/tensorFlow/cTensor/src/Data/images/mnist_jpgfiles/train";
            }
            printf("Using Training Directory: \n>> %s\n\n", trainingFileBase.c_str());
            printf("Please Enter testing directory (no need to end in a /): \n>> ");
            getline(std::cin, testingFileBase);
            if(testingFileBase.empty()){
                testingFileBase = "/home/theo/Documents/projects/math/tensorFlow/cTensor/src/Data/images/mnist_jpgfiles/train";
            }

            printf("Using Testing Directory: \n>> %s\n\n", testingFileBase.c_str());
 

            int a;
            int b;
            float c;

            printf("Enter Desired Number of Hidden Layers (2 seems to work)\n");
            scanf("%d", &a);
            printf("Enter size of the hidden Layers (16 - 50 for speed 100 for accuracy)\n");
            scanf("%d", &b);
            printf("Enter the training rate (.1 seems to work) \n");
            scanf("%f", &c);
            printf("%d %d %f", a, b, c);
            return 1;
        }
        default:
            printf("invalid");
            return -1;

    }
    return 0;
}


int main(){
    int j = neuralNetworkMenu();
    return 0;


}
