#include <iostream>
using namespace std;
int main(int argc,char*argv[]){
    float sum = 0;
    float num = argc;
    if (num - 1 == 0){
        cout << "Please input numbers to find average.";
        return 0;
    } 
    for(int i = 0;i < argc - 1;i++){
        sum += atof(argv[i+1]);
    }
    cout << "---------------------------------" << endl;
    cout << "Average of " << num - 1 << " numbers = " << sum/(num-1) << endl;
    cout << "---------------------------------" << endl;

}
