#include <bits/stdc++.h>

using namespace std;

class Picture{
public:
    string type; //the type of file: P2 or P5
    int width;
    int height;
    int white_level;
    vector<vector<int> > matrix;

    Picture(char FILENAME[100]){
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
            OUT_FILE<<type<<" "<<width<<" "<<height<<" "<<white_level<<endl;

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





int main(){
    string type_of_sort;
    int window_size;

    char IN_FILE_NAME[100], OUT_FILE_NAME[100];

    cin>>type_of_sort>>window_size>>IN_FILE_NAME>>OUT_FILE_NAME;

    Picture my_picture(IN_FILE_NAME);

    my_picture.print_data(OUT_FILE_NAME);

    return 0;
}
