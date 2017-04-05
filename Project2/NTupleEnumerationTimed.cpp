#include <limits>
#include <string>
#include <utility>
#include <fstream> 
#include <vector>
#include <iostream>
#include <time.h> 
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string> 
#include <stdlib.h>


using namespace std;

int NTupleFD;
int SubSetFD;
char newlin = '\n';
char buf[256];


bool AllZeros(int a[], int size){
  bool answer = true;
  for(int x=0;x<size;x++){
    if(a[x] != 0 )
      answer = false;
      
  }
  return answer;
}



void addOne(int a[], int b[], int numItems){
  for(int x=0;x<numItems;x++){
    a[x] = a[x] + 1;
    if(a[x] == b[x]){
      a[x] = 0;
    }
    else{
      return;
    }
  }
}



void NTupleEnumeration(int numItems, int allItems[], int allValues[], int allWeights[], 
    int numCopies[], int weightLimit){

    int solutionValue = 0;
    int solutionWeight = 0;
    int soultionArray[numItems];


    bool FirstCheck = true;
    int b[numItems];
    int a[numItems];

    // set array A to all 0's
    for(int x=0;x<numItems;x++)
      a[x] = 0;

    // set array b to make number of copies;
    for(int x=0;x<numItems;x++){
      b[x] = numCopies[x] + 1;
    }


    while(!AllZeros(a, numItems) || FirstCheck){

      int IterationValue = 0;
      int IterationWeight  = 0;
      for(int c=0;c<numItems;c++){
        IterationValue += a[c]*allValues[c];
      }

      for(int c=0;c<numItems;c++){
        IterationWeight += a[c]*allWeights[c];
      }


      if(IterationValue > solutionValue && IterationWeight <= weightLimit){  
        for(int t=0;t<numItems;t++){
          soultionArray[t] = a[t];
        }

        // cout << solutionValue << " " << solutionWeight << endl;
        solutionValue = IterationValue;
        solutionWeight = IterationWeight;

      }


      addOne(a, b, numItems);


      FirstCheck = false;

    }


    // string s = to_string(weightLimit);

    // write(NTupleFD, "Bag weight Limit: ", 19);
    // write(NTupleFD, &s, sizeof(s));
    // write(NTupleFD, &newlin, 1);

    // s = to_string(solutionValue);

    // write(NTupleFD, "Total Value Stolen: ", 20);
    // write(NTupleFD, &s, sizeof(s));
    // write(NTupleFD, &newlin, 1);

    // s = to_string(solutionWeight);

    // write(NTupleFD, "Total weight stolen: ", 21);
    // write(NTupleFD, &s, sizeof(s));
    // write(NTupleFD, &newlin, 1);

    // write(NTupleFD, "Items Stolen ", 13);
    // write(NTupleFD, &newlin, 1);

    // for(int x=0;x<numItems;x++){
    //   write(NTupleFD, "Take ", 5);

    //   string h = to_string(soultionArray[x]);

    //   write(NTupleFD, &h, sizeof(h));
    //   write(NTupleFD, " items of item ", 16);
    //   string b = to_string(x);
    //   write(NTupleFD, &b, sizeof(b));
    //   write(NTupleFD, &newlin, 1);
    // }


} // n-tuple



//For the item weights, use a random integer between 1 and half 
// of the total weight that your knapsack can carry.
// item values should be integers chosen randomly between 1 and 100 and your bag
// weight limit should be half the total value of all of the items 
int main(int argc, char* argv[]) {

    // create my ouput files
    NTupleFD = open("NTupleResults.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU, 777);
    if(NTupleFD < 0){
      cout << NTupleFD << endl;
        cerr << "COULD not create file NTupleResults.txt" << endl;
        exit(0);
    }
    SubSetFD = open("SubSetResults.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU, 777);
    if(SubSetFD < 0){
        cerr << "COULD not create file SubSetResults.txt" << endl;
        exit(0);
    }


  if(argc < 2){
      cerr << "Please give number of items" << endl;
    exit(0);
  }


  int allowedCopies = 1;
  bool forceTwoCopies = false;

  if(argc > 2){
    if( strcmp(argv[2], "sanity_check") == 0){
      forceTwoCopies = true;
    }
    else{
      allowedCopies = atoi(argv[2]);
    }
  }

  int numItems = atoi(argv[1]);

  int numItemsWithCopies = numItems;
  int allValues[numItems];
  int allWeights[numItems];
  int numCopies[numItems];
  int allItems[numItems];

  int totalValues = 0;
  int weightLimit;


  srand(time(NULL)); 


  int x;
  int y;

  for(x=0;x<numItems;x++){
    if(forceTwoCopies)
      numCopies[x] = 2;
    else
      numCopies[x] = rand() % allowedCopies + 1;

    // cout << numCopies[x] << " ";
    numItemsWithCopies += numCopies[x] - 1;
  }



  //give items an id
  for(x=0;x<numItems;x++){
    allItems[x] = x;
  }


  for(x=0;x<numItems;x++){
    allValues[x] = rand() % 100 + 1;
    totalValues += allValues[x];
  }


  weightLimit = totalValues / 2;


  for(x=0;x<numItems;x++){
    allWeights[x] = rand() % (weightLimit / 2) + 1;
  }

  // cout << endl << "NUM items including copies " << numItemsWithCopies <<  endl;

NTupleEnumeration(numItems, allItems, allValues, allWeights, 
    numCopies, weightLimit);


  return 0;
}


