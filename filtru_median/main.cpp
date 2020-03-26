#include <bits/stdc++.h>

using namespace std;

void bubble_sort(vector<int> &myArray);
void merge_sort(vector<int> &myArray);

class Picture{
public:
    string type; //the type of file: P2 or P5
    string sort_type; //which sort algorithm should be used
    int window_size;
    int width;
    int height;
    int white_level;
    vector<vector<int> > matrix;

    Picture(char FILENAME[100], string i_sort_type, int i_window_size){
        window_size=i_window_size;
        sort_type=i_sort_type;

        ifstream IN_FILE;
        IN_FILE.open(FILENAME);

        if(IN_FILE.is_open()){
            string line;

            getline(IN_FILE, type);
            getline(IN_FILE, line);
            //get through the comments
            while(line[0]=='#'){
                getline(IN_FILE, line);
            }
            //get the width and height from the line
            stringstream stream;
            string temp;
            stream<<line;
            stream>>temp;
            stringstream(temp) >> width;
            temp="";
            stream>>temp;
            stringstream(temp) >> height;
            temp="";

            IN_FILE>>white_level;

            for(int i=0;i<height;i++){
                vector<int> temp;
                for(int j=0;j<width;j++){
                    int temp_value;
                    IN_FILE>>temp_value;
                    temp.push_back(temp_value);
                }
                matrix.push_back(temp);
        }

        }
        else{
            cout<<"Error opening the input file";
        }

    }

    void print_data(char FILENAME[100]){
        ofstream OUT_FILE;
        OUT_FILE.open(FILENAME);

        if(OUT_FILE.is_open()){
            OUT_FILE<<type<<" "<<window_size<<" "<<sort_type<<" "<<width<<" "<<height<<" "<<white_level<<endl;

            for(int i=0;i<height;i++){
                for(int j=0;j<width;j++)
                    OUT_FILE<<matrix[i][j]<<" ";
                OUT_FILE<<endl;
            }
        }
        else{
            cout<<"Error opening the output file";
        }

    }

};

void bubble_sort(vector<int> &myArray){
    for(int i=0; i<myArray.size()-1; i++)
        for(int j=0; j<myArray.size()-i-1;j++)
            if(myArray[j]>myArray[j+1])
                swap(myArray[j], myArray[j+1]);
}

vector<int> merge(vector<int> left,vector<int> right){
  int leftCount = 0;
  int rightCount = 0;

  vector<int> results;

  bool useLeft;
  for (int i=0; i<left.size()+right.size();i++){
    if(leftCount<left.size()){
      if(rightCount<right.size()){
        useLeft = (left[leftCount] < right[rightCount]);
      }
      else{
        useLeft = true;
      }
    }
    else{
      useLeft = false;
    }

    if (useLeft){
      results.push_back(left[leftCount]);
      if (leftCount < left.size()){
        leftCount++;
      }
    }
    else{
      results.push_back(right[rightCount]);
      if (rightCount<right.size()){
        rightCount++;
      }
    }
  }
  return results;
}

vector<int> mergeSort(vector<int> arr){
  if (arr.size() <= 1){
    return arr;
  }
  int len = floor(arr.size()/2);
  vector<int> left(arr.begin(), arr.begin()+len);
  vector<int> right(arr.begin()+len, arr.end());

  return merge(mergeSort(left),mergeSort(right));
}


int main(){
    string type_of_sort;
    int window_size;

    char IN_FILE_NAME[100], OUT_FILE_NAME[100];

    cin>>type_of_sort>>window_size>>IN_FILE_NAME>>OUT_FILE_NAME;

    Picture my_picture(IN_FILE_NAME, type_of_sort, window_size);

    my_picture.print_data(OUT_FILE_NAME);

    vector<int> a_vect;
    for(int i=0;i<window_size;i++){
        int temp;
        cin>>temp;
        a_vect.push_back(temp);
    }

    //bubble_sort(a_vect);
    a_vect=mergeSort(a_vect);

    for(int i=0;i<a_vect.size();i++)
        cout<<a_vect[i]<<" ";

    return 0;
}
