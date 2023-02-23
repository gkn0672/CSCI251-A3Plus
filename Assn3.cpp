#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <fstream>

#include "algo.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"
#include "MyGraphic.h"
#include "MyTemplates.h"
using namespace std;

string choice;
bool input_read = false;
bool user_exit = false;
const string student_id = "7311217";
const string student_name = "Nguyen Gia Khanh";
string filter_option = "Point2D";
string sort_option = "x-ordinate";
string order_option = "ASC";

vector<Point2D> vec2dp;
vector<Point3D> vec3dp;
vector<Line2D> vec2dl;
vector<Line3D> vec3dl;
set<string> rawdata;

void Menu();
void HandleInput(string choice);
void ReadFile();
void SetFilter();
void SetSort();
void SetOrder();
ostream& ViewData(ostream& out);
void StoreData();
void ProcessData();

int main(){
    Menu();
    return 0;
}

// Display main menu
void Menu() {
    while(true){
        ClearScreen();
        cout << "------------------------------------" << endl;
        cout << "Student ID : " << student_id << endl;
        cout << "Student Name : " << student_name << endl;
        cout << "------------------------------------" << endl;
        cout << "Welcome to Assn3 program!" << endl;
        cout << endl;
        cout << "1) Read in data" << endl;
        if(input_read) {
            cout << "2) Specifying filter_option criteria (current : "<< filter_option << ")" << endl;
            cout << "3) Specify sorting criteria (current : " << sort_option << ")" << endl;
            cout << "4) Specify sorting order (current : " << order_option << ")" << endl;
            cout << "5) View data" << endl;
            cout << "6) Store Data" << endl;
            cout << "7) Point/Line projector" << endl;
        }
        cout << "8) Exit program" << endl;
        cout << endl;
        cout << "Please enter your choice: ";
        cin >> choice;
        HandleInput(TrimSpace(choice));
        if(user_exit){
            cout << "[ Exit ]" << endl;
            ClearScreen();
            break;
        } 
    }
}


//Handle user input
void HandleInput(string choice) {
    if(choice == "1") {
        ReadFile();
    } else if((choice == "2") && (input_read)) {
        SetFilter();
    } else if((choice == "3") && (input_read)) {   
        SetSort();
    } else if((choice == "4") && (input_read)) {
        SetOrder();
    } else if((choice == "5")) {
        ClearScreen();
        cout << "[View data ... ]" << endl;
        ViewData(std::cout);
        Freeze();
    } else if((choice == "6")) {
        StoreData();
    } else if((choice == "7")) {
        ClearScreen();
        if(filter_option == "Point2D") {
            for(int i=0; i<vec2dp.size(); i++) {
                GenerateP2D(vec2dp[i]);
            }
        } else if(filter_option == "Point3D") {
            for(int i=0; i<vec3dp.size(); i++) {
                GenerateP3D(vec3dp[i]);
            }
        } else if(filter_option == "Line2D") {
            for(int i=0; i<vec2dl.size(); i++) {
                GenerateL2D(vec2dl[i]);
            }
        } else {
            for(int i=0; i<vec3dl.size(); i++) {
                GenerateL3D(vec3dl[i]);
            }
        }

        Freeze();
    } else if((choice == "8")) {
        user_exit = true;
    } else {
        cout << "Invalid option!" << endl;
        MySleep(1);
        return;
    }
}

//Read data from file
void ReadFile() {
    ClearScreen();
    string inputFilename;
    cout << "Please enter filename : ";
    cin >> inputFilename;

    fstream inputFile(inputFilename.c_str(), fstream::in);

    if(!inputFile) {
        cout << "Error when reading file" << endl;
        MySleep(1);
        return;
    }

    string aLine;

    while (getline(inputFile, aLine))
    {
        aLine = TrimSpace(aLine);
        if (!aLine.size() || aLine.substr(0, 2) == "//") {
            continue;
        }
        rawdata.insert(aLine);
    }
    ProcessData();
    cout << endl;
    cout << rawdata.size() << " records read in successfully!" << endl;
    input_read = true;
    cout << "Going back to main menu ..." << endl;
    MySleep(1);
}

//Handle filter option
void SetFilter() {
    ClearScreen();
    char f_option;
    bool f_check;
    cout << endl;
    cout << "[ Specifying filter_option criteria (current : " << filter_option << ") ]" << endl;
    cout << endl;
    cout << "a) Point2D records" << endl;
    cout << "b) Point3D records" << endl;
    cout << "c) Line2D records" << endl;
    cout << "d) Line3D records" << endl;
    cout << "Please enter your criteria (a - d) : ";
    cin >> f_option;
    cout << endl;
    switch(f_option) {
        case 'a':
            filter_option = "Point2D";
            sort_option ="x-ordinate";
            break;
        case 'b':
            filter_option = "Point3D";
            sort_option ="x-ordinate";
            break;
        case 'c':
            filter_option = "Line2D";
            sort_option = "Pt. 1";
            break;
        case 'd':
            filter_option = "Line3D";
            sort_option = "Pt. 1";
            
            break;
        default:
            f_check = false;
            cout << "Invalid option!" << endl;
            MySleep(1);
            break;
    }

    if(f_check) cout << "filter_option criteria successfully set to '" << filter_option << "'" << endl;
    MySleep(1);
}

// Handle sorting
void SetSort() {
    char s_option;
    bool s_check = true;
    ClearScreen();
    if(filter_option == "Point2D") {
        cout << "\n[ Specifying sorting criteria (current : " << order_option << ") ]\n\n";
		cout << "a)	X ordinate value\n";
		cout << "b)	Y ordinate value\n";
		cout << "c)	Dist. Fr Origin value\n\n";
		cout << "Please enter your criteria (a - c) : ";
		cin >> s_option;

        switch(s_option) {
            case 'a':
                sort_option = "x-ordinate";
                break;
            case 'b':
                sort_option = "y-ordinate";
                break;
            case 'c':
                sort_option = "DistFrOrigin";
                break;
            default:
                s_check = false;
                cout << "Invalid option!" << endl;
                break;
        }
    } else if (filter_option == "Point3D") {
        cout << "[ Specifying sorting criteria (current : " << order_option << ") ]" << endl;
		cout << "a)	X ordinate value\n";
		cout << "b)	Y ordinate value\n";
		cout << "c)	Z ordinate value\n";
		cout << "d)	Dist. Fr Origin value\n\n";
		cout << "Please enter your criteria (a - d) : ";
		cin >> s_option;

        switch(s_option) {
            case 'a':
                sort_option = "x-ordinate";
                break;
            case 'b':
                sort_option = "y-ordinate";
                break;
            case 'c':
                sort_option = "z-ordinate";
                break;
            case 'd':
                sort_option = "DistFrOrigin";
                break;
            default:
                s_check = false;
                cout << "Invalid option!" << endl;
                MySleep(1);
                break;
            }
    } else {
        cout << "[ Specifying sorting criteria (current : " << order_option << ") ]" << endl;
		cout << "a)	Pt. 1's (x, y) values\n";
	    cout << "b)	Pt. 2's (x, y) values\n";
		cout << "c)	Length value\n\n";
		cout << "Please enter your criteria (a - c) : ";
		cin >> s_option;

        switch(s_option) {
            case 'a':
                sort_option = "Pt. 1";
                break;
            case 'b':
                sort_option = "Pt. 2";
                break;
            case 'c':
                sort_option = "Length";
                break;
            default:
                s_check = false;
                cout << "\nInvalid option!\n\n";
                MySleep(1);
                break;
        }
    }

    if(s_check) cout << "\nSorting criteria successfully set to '" << order_option << "'" << endl;
    MySleep(1);
}

// Handle sorting order
void SetOrder() {
    char o_option;
    bool o_check = true;
    ClearScreen();
    cout << "[ Specifying sort criteria (current : " << order_option << ") ]" << endl;
	cout << "a) ASC (ascending order)" << endl;
	cout << "b) DSC (descending order)" << endl;
	cout << "Please enter your criteria (a - b) : ";
	cin >> o_option;
    cout << endl;
    switch(o_option) {
        case 'a':
            order_option = "ASC";
            break;
        case 'b':
            order_option = "DSC";
            break;
        default:
            o_check = false;
            cout << "Invalid option!" << endl;
    }

    if(o_check) cout << "\nSorting order successfully set to '" << order_option << "'" << endl;
    MySleep(1);
}


// Generate object
void ProcessData() {
    for(string data : rawdata) {
        vector<string> data_entry = ProcessString(data, ",");
        if(data_entry[0] == "Point2D") {
            int x = ConvertStringToInteger(ProcessCoordinate(data_entry[1]));
            int y = ConvertStringToInteger(ProcessCoordinate(data_entry[2]));
            Point2D p2d = Point2D(x, y);
            vec2dp.push_back(p2d);
        } else if(data_entry[0] == "Point3D") {
            int x = ConvertStringToInteger(ProcessCoordinate(data_entry[1]));
            int y = ConvertStringToInteger(ProcessCoordinate(data_entry[2]));
            int z = ConvertStringToInteger(ProcessCoordinate(data_entry[3]));
            Point3D p3d = Point3D(x, y, z);
            vec3dp.push_back(p3d);
        } else if(data_entry[0] == "Line2D") {
            int x1 = ConvertStringToInteger(ProcessCoordinate(data_entry[1]));
            int y1 = ConvertStringToInteger(ProcessCoordinate(data_entry[2]));
            int x2 = ConvertStringToInteger(ProcessCoordinate(data_entry[3]));
            int y2 = ConvertStringToInteger(ProcessCoordinate(data_entry[4]));
            Line2D l2d = Line2D(Point2D(x1, y1), Point2D(x2, y2));
            vec2dl.push_back(l2d);
        } else {
            int x1 = ConvertStringToInteger(ProcessCoordinate(data_entry[1]));
            int y1 = ConvertStringToInteger(ProcessCoordinate(data_entry[2]));
            int z1 = ConvertStringToInteger(ProcessCoordinate(data_entry[3]));
            int x2 = ConvertStringToInteger(ProcessCoordinate(data_entry[4]));
            int y2 = ConvertStringToInteger(ProcessCoordinate(data_entry[5]));
            int z2 = ConvertStringToInteger(ProcessCoordinate(data_entry[6]));
            Line3D l3d = Line3D(Point3D(x1, y1, z1), Point3D(x2, y2, z2));
            vec3dl.push_back(l3d);
        }
    }
}

// Generate report
ostream& ViewData(ostream& out) {
	out << "filtering criteria : " << filter_option << endl;
	out << "sorting criteria : " << sort_option << endl;
	out << "sorting order : " << order_option << endl << endl;
    if(filter_option == "Point2D") {
        out << setw(5) << "X" << setw(6) << "Y" << "    Dist. Fr Origin" << endl;
		out << "- - - - - - - - - - - - - - - - - - -" << endl;
        if (sort_option == "x-ordinate") {
			if (order_option == "ASC") {
				sort(vec2dp.begin(), vec2dp.end(), [](Point2D one, Point2D two){return one.getX() < two.getX();});
			} else if (order_option == "DSC") {
				sort(vec2dp.begin(), vec2dp.end(), [](Point2D one, Point2D two){return (one).getX() > (two).getX();});
			}
		} else if (sort_option == "y-ordinate") {
			if (order_option == "ASC") {
				sort(vec2dp.begin(), vec2dp.end(), [](Point2D one, Point2D two){return (one).getY() < (two).getY();});
			}
			else if (order_option == "DSC") { 
				sort(vec2dp.begin(), vec2dp.end(), [](Point2D one, Point2D two){return (one).getY() > (two).getY();});
			}
		} else if (sort_option == "DistFrOrigin") {
			if (order_option == "ASC") {
				sort(vec2dp.begin(), vec2dp.end(), [](Point2D one, Point2D two){return (one).getScalarValue() < (two).getScalarValue();});
			} else if (order_option == "DSC"){
				sort(vec2dp.begin(), vec2dp.end(), [](Point2D one, Point2D two){return (one).getScalarValue() > (two).getScalarValue();});
			}
		}
        for (auto line : vec2dp) {
			out << line << endl;
		}
    } else if (filter_option == "Point3D") {
        out << setw(5) << "X" << setw(6) << "Y" << setw(6) << "Z" << "    Dist. Fr Origin" << endl;
		out << "- - - - - - - - - - - - - - - - - - -" << endl;
        if (sort_option == "x-ordinate") {
			if (order_option == "ASC") {
				sort(vec3dp.begin(), vec3dp.end(), [](Point3D one, Point3D two){return (one).getX() < (two).getX();});
			}
			else if (order_option == "DSC"){
				sort(vec3dp.begin(), vec3dp.end(), [](Point3D one, Point3D two){return (one).getX() > (two).getX();});
			}
		} else if (sort_option == "y-ordinate") {
			if (order_option == "ASC") {
				sort(vec3dp.begin(), vec3dp.end(), [](Point3D one, Point3D two){return (one).getY() < (two).getY();});
			}
			else if (order_option == "DSC") {
				sort(vec3dp.begin(), vec3dp.end(), [](Point3D one, Point3D two){return (one).getY() > (two).getY();});
			}
		} else if (sort_option == "z-ordinate") {
			if (order_option == "ASC") {
				sort(vec3dp.begin(), vec3dp.end(), [](Point3D one, Point3D two){return (one).getZ() < (two).getZ();});
			} else if (order_option == "DSC") {
				sort(vec3dp.begin(), vec3dp.end(), [](Point3D one, Point3D two){return (one).getZ() > (two).getZ();});
			}
		} else if (sort_option == "DistFrOrigin") {
			if (order_option == "ASC") {
				sort(vec3dp.begin(), vec3dp.end(), [](Point3D one, Point3D two){return (one).getScalarValue() < (two).getScalarValue();});
			} else if (order_option == "DSC") {
				sort(vec3dp.begin(), vec3dp.end(), [](Point3D one, Point3D two){return (one).getScalarValue() > (two).getScalarValue();});
			}
		}

        for (auto line : vec3dp) {
			out << line << endl;
		}
    } else if (filter_option == "Line2D") {
        out << setw(5) << "P1-X" << setw(6) << "P1-Y" << "   " << setw(6) << "P2-X" << setw(6) << "P2-Y" << "    Length" << endl;
		out << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        if (sort_option == "Pt. 1") {
			if (order_option == "ASC") {
				sort(vec2dl.begin(), vec2dl.end(), [](Line2D one, Line2D two){return (one).getPt1() < (two).getPt1();});
			} else if (order_option == "DSC"){
				sort(vec2dl.begin(), vec2dl.end(), [](Line2D one, Line2D two){return (one).getPt1() > (two).getPt1();});
			}
		} else if (sort_option == "Pt. 2") {
			if (order_option == "ASC") {
				sort(vec2dl.begin(), vec2dl.end(), [](Line2D one, Line2D two){return (one).getPt2() < (two).getPt2();});
			} else if (order_option == "DSC") {
				sort(vec2dl.begin(), vec2dl.end(), [](Line2D one, Line2D two){return (one).getPt2() > (two).getPt2();});
			}
		} else if (sort_option == "Length") {
			if (order_option == "ASC") {
				sort(vec2dl.begin(), vec2dl.end(), [](Line2D one, Line2D two){return (one).getScalarValue() < (two).getScalarValue();});
			} else if (order_option == "DSC"){
				sort(vec2dl.begin(), vec2dl.end(), [](Line2D one, Line2D two){return (one).getScalarValue() > (two).getScalarValue();});
			}
		}

        for (auto line : vec2dl) {
			out << line << endl;
		}
    } else if (filter_option == "Line3D") {
        out << setw(5) << "P1-X" << setw(6) << "P1-Y"<< setw(6) << "P1-Z" << "   " << setw(6) << "P2-X" << setw(6) << "P2-Y"<< setw(6) << "P2-Z" << "    Length" << endl;
		out << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        if (sort_option == "Pt. 1") {
			if (order_option == "ASC") {
				sort(vec3dl.begin(), vec3dl.end(), [](Line3D one, Line3D two){return (one).getPt1() < (two).getPt1();});
			} else if (order_option == "DSC") {
				sort(vec3dl.begin(), vec3dl.end(), [](Line3D one, Line3D two){return (one).getPt1() > (two).getPt1();});
			}
		} else if (sort_option == "Pt. 2") {
			if (order_option == "ASC") {
				sort(vec3dl.begin(), vec3dl.end(), [](Line3D one, Line3D two){return (one).getPt2() < (two).getPt2();});
			} else if (order_option == "DSC") {
				sort(vec3dl.begin(), vec3dl.end(), [](Line3D one, Line3D two){return (one).getPt2() > (two).getPt2();});
			}
		} else if (sort_option == "Length") {
			if (order_option == "ASC") {
				sort(vec3dl.begin(), vec3dl.end(), [](Line3D one, Line3D two){return (one).getScalarValue() < (two).getScalarValue();});
			} else if (order_option == "DSC") {
				sort(vec3dl.begin(), vec3dl.end(), [](Line3D one, Line3D two){return (one).getScalarValue() > (two).getScalarValue();});
			}
		}
        for (auto line : vec3dl) {
			out << line << endl;
        }
    }
    return out;
}

// Store data in file
void StoreData() {
    string fileName;
    int size = 0;
	cout << endl << "Please enter filename : ";
	cin >> fileName;
	ofstream outData;
	outData.open (fileName.c_str());
	ViewData(outData);
	outData.close();
	if (filter_option == "Point2D")
		size = vec2dp.size();
	else if (filter_option == "Point3D")
		size = vec3dp.size();
	else if (filter_option == "Line2D")
		size = vec2dl.size();
	else if (filter_option == "Line3D")
		size = vec3dl.size();
	cout << size << " records output successfully!" << endl;
	cout << "Going back to main menu ... " << endl;
    MySleep(1);
}
