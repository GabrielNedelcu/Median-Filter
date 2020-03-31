#include <bits/stdc++.h>

using namespace std;

void bubble_sort(vector<int> &myArray);
void Unite(int st, int middle, int dr, vector<int>& a, vector<int>& aux);
void Merge_sort(int st, int dr, vector<int>& a, vector<int> &aux);


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

            for(int row=0;row<height;row++){
                vector<int> temp;
                for(int col=0;col<width;col++){
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
            OUT_FILE<<type<<endl<<width<<" "<<height<<endl<<white_level<<endl;

            for(int row=0;row<height;row++){
                for(int col=0;col<width;col++)
                    OUT_FILE<<matrix[row][col]<<" ";
                OUT_FILE<<endl;
            }
        }
        else{
            cout<<"Error opening the output file";
        }

    }
};

int calculate_new_pixel_value(vector<vector<int> > &matrix, int x, int y, int width, int height,string sort_type, int window_size, vector<int> &aux){
    int dir, counter=0;
    dir=(window_size-1)/2;  //how much should i go left, right, up, down from the current position

    vector<int> values;

    for(int row=x-dir; row<=x+dir; row++){
        for(int col=y-dir; col<=y+dir; col++){
            int tmp_row, tmp_col;
            tmp_row=row;
            tmp_col=col;
            //change the indexes in case the pixel is out of range
            if(row<0)   tmp_row=0;
            if(row>height-1) tmp_row=height-1;
            if(col<0)   tmp_col=0;
            if(col>width-1) tmp_col=width-1;

            values.push_back(matrix[tmp_row][tmp_col]); //add the value to my array
            counter++;
        }
    }

    //sort the values and return the middle one

    if(sort_type.compare("merge")==0){
        Merge_sort(0,counter-1,values,aux);
        return values.at(window_size*window_size/2);
    }

    else if(sort_type.compare("bubble")==0){
        bubble_sort(values);
        return values.at(window_size*window_size/2);
    }

    else{
        cout<<"Error: The sorting method is not recognised";
        return -1;
    }

}

void filter(Picture &my_picture, string sort_type, int window_size){

        vector<vector<int> > my_picture_copy(my_picture.matrix); //copy of the original matrix
        vector<int> aux(window_size*window_size+1, 0);
        for(int row=0;row<my_picture.height;row++){
            for(int col=0;col<my_picture.width;col++){
                //update the original matrix
                my_picture.matrix[row][col]=calculate_new_pixel_value(my_picture_copy, row, col, my_picture.width,my_picture.height, sort_type, window_size, aux);
            }
        }
}

void bubble_sort(vector<int> &myArray){
    for(unsigned i=0; i<myArray.size()-1; i++)
        for(unsigned j=0; j<myArray.size()-i-1;j++)
            if(myArray[j]>myArray[j+1])
                swap(myArray[j], myArray[j+1]);
}

void Unite(int st, int middle, int dr, vector<int>& a, vector<int>& aux){
    int i = st;
    int j = middle+1;
    int k=0;

    while(i<=middle && j<=dr){
        if(a.at(i)<a.at(j)){
            aux.at(++k)=a.at(i);
            i++;
        }
        else{
            aux.at(++k)=a.at(j);
            j++;
        }
    }

    while(i<=middle){
            aux.at(++k)=a.at(i);
            i++;
        }
    while(j<=dr){
            aux.at(++k)=a.at(j);
            j++;
        }

    for(int i=st; i<=dr; ++i)
        a.at(i)=aux.at(i-st+1);
}

void Merge_sort(int st, int dr, vector<int>& a, vector<int> &aux){
    int m;
    if(dr>st){
        m=(st+dr)/2;
        Merge_sort(st, m, a, aux);
        Merge_sort(m+1, dr, a, aux);
        Unite(st, m, dr, a, aux);
    }
}


int main(){
    string type_of_sort;
    int window_size;

    char IN_FILE_NAME[100], OUT_FILE_NAME[100];

    clock_t t_start, t_end;

    t_start=clock();

    cin>>type_of_sort>>window_size>>IN_FILE_NAME>>OUT_FILE_NAME;


    Picture my_picture(IN_FILE_NAME);

    filter(my_picture, type_of_sort, window_size);

    my_picture.print_data(OUT_FILE_NAME);

    t_end=clock();

    double time_taken = double(t_end - t_start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;

    return 0;
}
