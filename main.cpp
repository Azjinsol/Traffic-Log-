/*
Author: Azjinsol
*/
#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
using namespace std;
//my program
 
int main() {
    //file name variable
    string fileName = "";

    //declare the vector variables
    vector<string> plate, date, time;
    vector<int> weight, speed;

    //declare file stream variables
    ifstream iFile;
    ofstream oFile;

    string headers = "";
    string line = "";

    getline(iFile, line);

    //stringstream lineStream(line);

    int comma_loc = 0;
    int violation = 0;
    int count = 0;
    //Check for errors
    do {
        //inputing the file name
        cout << "Open File: ";
        cin >> fileName;
        //Open input file
        iFile.open(fileName);
   
        getline(iFile, headers);
 
        //check if it is valid name
        if (!iFile.is_open()) {
            cout << "Could not open " << fileName << endl;
            continue;
        }

        while (getline(iFile, line)) {
            //searching plate
            comma_loc = line.find(',');
            plate.push_back(line.substr(0, comma_loc));
            line = line.substr(comma_loc+1, line.length());

            //searching pdate
            comma_loc = line.find(',');
            date.push_back(line.substr(0, comma_loc));
            line = line.substr(comma_loc+1, line.length());

            //searching time
            comma_loc = line.find(',');
            time.push_back(line.substr(0, comma_loc));
            line = line.substr(comma_loc+1, line.length());

            //searching weight
            comma_loc = line.find(',');
            weight.push_back(stoi(line));
            line = line.substr(comma_loc+1, line.length());

            //searching speed
            speed.push_back(stoi(line));
            
            count++;
        }

    }
    while (!iFile.is_open());

    //close the input file
    iFile.close();

    //searching violations type
    for (int i = 0; i < count; i++) {
        if (date[i - 1] != date[i]) {
            oFile.close();
            string report = "[" + date[i] + "] Report.txt";
            oFile.open(report);
        }
        if (weight[i] < 5000 && speed[i] > 45) {
            oFile << "[" << time[i] << "] " << plate[i] << endl;
            violation++;
            continue;
        }
        if (weight[i] >= 5000 && speed[i] > 30) {
            oFile << "[" << time[i] << "] " << plate[i] << endl;
            violation++;
            continue;
        }
    }
    
    //close the output file
    oFile.close();

    //displaying the amount of violations
    cout << violation << " violations logged.\n";

    return 0;
}
