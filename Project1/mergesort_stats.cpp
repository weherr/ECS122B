#include <limits>
#include <string>
#include <utility>
#include <stdlib.h>
#include <fstream> 
#include <vector>
#include <iostream>

using namespace std;

#define INFTY std::numeric_limits<int>::max()

int recursive = 0;
int transitions = 0;
int compares = 0;

void print(int *input, int x){
    for ( int i = 0; i < x; i++ )
        cout << input[i] << " ";
    cout << endl;
}


void mergesort(int* a, int lo, int hi) {
    recursive++;
    if (hi <= lo) return;
    // Split array into two (roughly) equal sized subarrays
    int midlo = lo + (hi - lo) / 3;
    int midhi = lo + (hi - lo) /1.5;

    mergesort(a, midlo + 1, midhi);
    mergesort(a, midhi + 1, hi);
    mergesort(a, lo, midlo);

    int* b = new int[(midlo-lo+2)];
    int* d = new int[(midhi - midlo +1)]; 
    int* c = new int[(hi - midhi + 1)];


    for (int k = lo; k <= midlo; k++){
       b[k-lo] = a[k];
       // cout << a[k] ;
    }
    for (int k = midlo+1; k <= midhi; k++)
        d[k-midlo-1] = a[k];

    for(int k = midhi + 1; k <= hi; k++)
        c[k-midhi -1] = a[k];


     b[midlo-lo+1] = INFTY; d[midhi - midlo] = INFTY; c[hi - midhi] = INFTY; 


    // // Sentinel values for ease of merge implementation
    int i = 0, j = 0, l = 0;

    string lastCopied ="";
    for (int k = lo; k <= hi; k++){
        int howFar=0;
        if (c[j] < b[i] && c[j] < d[l]){ 
          a[k] = c[j++];

          if(lastCopied != "c" && lastCopied != "")
            transitions++;

          lastCopied = "c";
          howFar = 2;
        }
        else if(d[l] < b[i] && d[l] < c[j]){
          a[k] = d[l++];

          if(lastCopied != "b" && lastCopied != "")
            transitions++;

          lastCopied = "b";
          howFar = 4;
        }
        else{
          a[k] = b[i++];

          if(lastCopied != "a" && lastCopied != "")
            transitions++;

          lastCopied = "a";
          howFar = 4;
        }
        compares += howFar;
      } 
    delete[] b;
    delete[] c;
    delete[] d;
}

int main(int argc, char* argv[]) {

  int k = 0;

  if(argc < 2){
    cerr << "Please give a file to sort" << endl;
    exit(0);
  }

  if(argc > 2)
    k = atoi(argv[2]);

  string line;
  ifstream myfile;
  vector<int> v;

  myfile.open(argv[1], ios_base::out | ios_base::in);
  int temp;
  if (myfile.is_open()){
    while (!myfile.eof() ){
      myfile >> temp;
      v.push_back(temp);

    }
    myfile.close();
  }
  else{
    cerr << "Unable to open file" << endl; 
    exit(0);
  }

  int arr[v.size()];

  for(int i=0; i<v.size(); i++){
        arr[i] = v[i];
  }

  //print(arr, v.size());
  mergesort(arr, 0, v.size()-1);

  // print(arr, v.size());

  cout << "Recursive Calls: " << recursive << endl;
  cout << "Transitions: " << transitions << endl;
  cout << "Compares: " << compares << endl;

  return 0;
}