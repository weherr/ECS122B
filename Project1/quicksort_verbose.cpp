#include <iostream>
#include <stdlib.h>
#include <fstream> 
#include <string>
#include <vector>
using namespace std;


void insertion_sort (int arr[], int start,  int end);
int partition(int input[], int p, int r);


void insertion_sort (int arr[], int start,  int end){
 // cout << "LOOK" << endl;
      int j, temp;
            
      for (int i = start; i < end; i++){
            j = i;
            
            while (j > start && arr[j] < arr[j-1]){
                  temp = arr[j];
                  arr[j] = arr[j-1];
                  arr[j-1] = temp;
                  j--;
            }
      }
}

// A simple print function
void print(int *input, int x){
    for ( int i = 0; i < x; i++ )
        cout << input[i] << " ";
    cout << endl;
}


// The partition function
int partition(int* input, int p, int r){
    int pivot = input[(rand()%(r-p))+p];

    while ( p < r ){
        while ( input[p] < pivot )
            p++;

        while ( input[r] > pivot )
            r--;

        if ( input[p] == input[r] )
            p++;
        else if ( p < r ){
            int tmp = input[p];
            input[p] = input[r];
            input[r] = tmp;
        }
    }

    return r;
}

// The quicksort recursive function
void quicksort(int* input, int p, int r, int k){
    if(r-p < k){
      insertion_sort(input, p, r + 1);
      return;
    }
    if ( p < r ){
        int j = partition(input, p, r);        
        quicksort(input, p, j-1, k);
        quicksort(input, j+1, r, k);
    }
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
  quicksort(arr, 0, v.size()-1, k);

  print(arr, v.size());

  return 0;
}