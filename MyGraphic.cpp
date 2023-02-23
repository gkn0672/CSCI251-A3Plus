#include "MyGraphic.h"
vector<Point2D> DDA(Point2D p1, Point2D p2);
const int height = 25;
const int width = 50;
int scale2d = 1;
int scale = 1;
Point2D center_Point = Point2D(height / 2, width / 2);
Point2D left_Point = Point2D(height/2, 0);
Point2D right_Point = Point2D(height / 2, width - 1);
Point2D top_Point = Point2D(0, width / 2);
Point2D bottom_Point = Point2D(height -1, width / 2);
Point2D diag_top = Point2D(0, width / 2 - 12);
Point2D diag_bottom = Point2D(height - 1, width / 2 + 12);
bool check_line(int x, int y, vector<Point2D> l);
bool scale_check(int x, int y, int z);
bool check_2d(int x, int y);
bool scale_check_line2d(int x1, int y1, int x2, int y2);

//Draw point2d
void GenerateP2D(Point2D p) {
	cout << "Projection of Point2D[" << p.getX() << ", " << p.getY() << "]" << endl;
	int my_x = p.getX();
	int my_y = p.getY();

	//Find suitable scale
	while(!check_2d(my_x, my_y)) {
		scale2d++;
	}

	my_x = my_x / scale2d;
	my_y = my_y / scale2d;
	int x=0;
	int y=0;
	int xmax;
	int ymax;
	int xmin;
	int ymin;
	if(p.getX() < 0) {
		xmin = my_x - 2;
		xmax = 2;
	} else {
		xmin = 0;
		xmax = my_x + 2;
	}

	if(p.getY() < 0) {
		ymin = my_y - 2;
		ymax = 2;
	} else {
		ymin = 0;
		ymax = my_y + 2;
	}

	//Draw
	cout << "Current scale (one '_'): " << scale2d << endl;
	for(y = ymax; y >= ymin; y--) {
		string sym = "";
		cout << endl;
    	for(x = xmin; x <= xmax; x++) {
			if(x == 0 && y == 0) {
				sym = "0";
			}       
        	else if(x == 0) {
				if(y == ymax) {
					sym = "Y";
				} else {
					sym = "|";
				}
        	} else {
				if(y == 0) {
            		if(x >= xmin || x <= xmax) {
						if(x == xmax) {
							sym = " X";
						} else {
							sym = "-";
						}
            		}
        		} else {
					sym = " ";
        		}
			}
			if(x == my_x && y == my_y) {
				sym = "*";
			}
			cout << sym;
    	}
	}
	scale2d = 1;
	cout << endl;
	cout << endl;
}

//Draw point3D
void GenerateP3D(Point3D p) {
	vector<Point2D> x_axis_left = DDA(left_Point, center_Point);
	vector<Point2D> x_axis_right = DDA(center_Point, right_Point);
	vector<Point2D> z_axis_top = DDA(center_Point, top_Point);
	vector<Point2D> z_axis_bottom = DDA(center_Point, bottom_Point);
	vector<Point2D> y_axis_top = DDA(center_Point, diag_top);
	vector<Point2D> y_axis_bottom = DDA(center_Point, diag_bottom);

	//Convert to point 2D
	Point2D p1 = Normalize(p);
	cout << "Projection of Point3D[" << p.getX() << ", " << p.getY() << ", " << p.getZ() << "]" << endl;
	cout << "Current scale: " << scale << endl;

	//Draw
	for(int i=0; i<height; i++) {
		for(int j=0; j<width; j++) {
			string sym = "";
			if(i == top_Point.getX() && j == top_Point.getY()) {
				sym = "Z";
			} else if(i == right_Point.getX() && j == right_Point.getY()) {
				sym = "X";
			} else if(i == diag_bottom.getX() && j == diag_bottom.getY()) {
				sym = "Y";
			} else {
				if(check_line(i, j, x_axis_left) || check_line(i, j, x_axis_right)) {
					sym = "-";
				} else if(check_line(i, j, z_axis_top) || check_line(i, j, z_axis_bottom)){
					sym = "|";
				} else if(check_line(i, j, y_axis_top) || check_line(i, j, y_axis_bottom)) {
					sym = "\\";
				} else {
					sym = " ";
				}
			}

			if (i == center_Point.getX() && j == center_Point.getY()) {
				sym = "O";
			}

			if(i == p1.getX() && j == p1.getY()) {
				sym = "*";
			}
			cout << sym;
		}
		cout << endl;
	}
	scale = 1;
	cout << endl;
	cout << endl;
}

// Draw line 2D
void GenerateL2D(Line2D l) {
	int x1 = l.getPt1().getX();
	int y1 = l.getPt1().getY();
	int x2 = l.getPt2().getX();
	int y2 = l.getPt2().getY();
	cout << "Projection of Line2D[ A(" << x1 << ", " << y1 << "), B(" << x2 << ", " << y2 << ") ]" << endl;
	while(!scale_check_line2d(x1, y1, x2, y2)) {
		scale2d++;
	}
	int x=0;
	int y=0;
	int xmax;
	int xmin;
	int ymax;
	int ymin;
	x1 = x1 / scale2d;
	y1 = y1 / scale2d;
	x2 = x2 / scale2d;
	y2 = y2 / scale2d;
	vector<Point2D> line = DDA(Point2D(x1, y1), Point2D(x2, y2));
	xmax = max(x1, x2);
	xmin = min(x1, x2);
	ymax = max(y1, y2);
	ymin = min(y1, y2);

	if(xmax > 0) {
		if(xmin > 0) {
			xmax += 2;
			xmin = -1;
		} else {
			xmax += 2;
			xmin -= 2;
		}
	} else {
		xmax = 1;
		xmin -= 2;
	}

	if(ymax > 0) {
		if(ymin > 0) {
			ymax += 2;
			ymin = -1;
		} else {
			ymax += 2;
			ymin -= 2;
		}
	} else {
		ymax = 1;
		ymin -= 2;
	}

	cout << "Current scale (one '_'): " << scale2d << endl;
	for(y = ymax; y >= ymin; y--) {
		string sym = "";
		cout << endl;
    	for(x = xmin; x <= xmax; x++) {
			if(x == 0 && y == 0) {
				sym = "0";
			}       
        	else if(x == 0) {
				if(y == ymax) {
					sym = "Y";
				} else {
					sym = "|";
				}
        	} else {
				if(y == 0) {
            		if(x >= xmin || x <= xmax) {
						if(x == xmax) {
							sym = " X";
						} else {
							sym = "-";
						}
            		}
        		} else {
					sym = " ";
        		}
			}

			if((check_line(x, y, line)) && (sym != "0")) {
				sym = ".";
        	}

			if(x == x1 && y == y1) {
				sym = "A";
			}
			if(x == x2 && y == y2) {
				sym = "B";
			}

			cout << sym;
    	}
	}
	scale2d = 1;
	cout << endl;
	cout << endl;
}

//Draw line 3D
void GenerateL3D(Line3D l) {
	int scale = 3;
	Point3D p1 = l.getPt1();
	Point3D p2 = l.getPt2();
	Point2D p3 = Normalize(p1);
	Point2D p4 = Normalize(p2);

	//Generate coordinate system
	vector<Point2D> x_axis_left = DDA(left_Point, center_Point);
	vector<Point2D> x_axis_right = DDA(center_Point, right_Point);
	vector<Point2D> z_axis_top = DDA(center_Point, top_Point);
	vector<Point2D> z_axis_bottom = DDA(center_Point, bottom_Point);
	vector<Point2D> y_axis_top = DDA(center_Point, diag_top);
	vector<Point2D> y_axis_bottom = DDA(center_Point, diag_bottom);
	vector<Point2D> line = DDA(p3, p4);

	//Draw
	cout << "Projection for Line3D [ A(" << p1.getX() << ", " << p1.getY() << ", " << p1.getZ() << "), B(" << p2.getX() << ", " << p2.getY() << ", " << p2.getZ()  << ") ]" << endl;
	cout << "Current scale (one '-') = " << scale << endl;
	for(int i=0; i<height; i++) {
		for(int j=0; j<width; j++) {
			string sym = "";
			if(i == top_Point.getX() && j == top_Point.getY()) {
				sym = "Z";
			} else if(i == right_Point.getX() && j == right_Point.getY()) {
				sym = "X";
			} else if(i == diag_bottom.getX() && j == diag_bottom.getY()) {
				sym = "Y";
			} else {
				if(check_line(i, j, x_axis_left) || check_line(i, j, x_axis_right)) {
					sym = "-";
				} else if(check_line(i, j, z_axis_top) || check_line(i, j, z_axis_bottom)){
					sym = "|";
				} else if(check_line(i, j, y_axis_top) || check_line(i, j, y_axis_bottom)) {
					sym = "\\";
				} else {
					sym = " ";
				}
			}

			if (i == center_Point.getX() && j == center_Point.getY()) {
				sym = "O";
			}

			if(check_line(i, j, line)) {
				sym = ".";
			}

			if (i == p3.getX() && j == p3.getY()) {
				sym = "A";
			}

			if (i == p4.getX() && j == p4.getY()) {
				sym = "B";
			}
			cout << sym;
		}
		cout << endl;
	}
	scale = 1;
	cout << endl;
	cout << endl;
}


//Convert 3D to 2D
Point2D Normalize(Point3D p) {
	int x = p.getX();
	int y = p.getY();
	int z = p.getZ();
	while(!scale_check(x, y, z)) {
		scale += 1;
	}
	x = x / scale;
	y = y / scale;
	z = z / scale;

	int current_x = center_Point.getX();
	int current_y = center_Point.getY();

	current_y += x;
	current_x += y;
	current_y += y;
	current_x -= z;
	return Point2D(current_x, current_y);
}


//Scale
bool scale_check(int x, int y, int z) {
	if(abs(x / scale) >= 10) {
		return false;
	}

	if(abs(y / scale) >= 10) {
		return false;
	}

	if(abs(z / scale) >= 10 ) {
		return false;
	}

	if(center_Point.getX() + (y / scale) - (z / scale) <= 0) {
		return false;
	}

	if(center_Point.getX() + (y / scale) - (z / scale) >= 20) {
		return false;
	}

	return true;
}

bool scale_check_line2d(int x1, int y1, int x2, int y2) {
	if(abs(x1 / scale2d) >= 20) {
		return false;
	}

	if(abs(y1 / scale2d) >= 20) {
		return false;
	}

	if(abs(x2 / scale2d) >= 20 ) {
		return false;
	}

	if(abs(y2 / scale2d) >= 20 ) {
		return false;
	}
	return true;
}

bool check_line(int x, int y, vector<Point2D> l) {
	for( int i=0; i<l.size(); i++) {
		if(x == l[i].getX() && y == l[i].getY()) {
			return true;
		}
	}
	return false;
}

bool check_2d(int x, int y) {
	if(abs(x / scale2d) >= 20) {
		return false;
	}

	if(abs(y / scale2d) >= 20) {
		return false;
	}
	return true;
}

//Draw a line on terminal from p1 to p2
vector<Point2D> DDA(Point2D p1, Point2D p2) {
	vector<Point2D> result;
	float x1 = p1.getX();
	float y1 = p1.getY();
	float x2 = p2.getX();
	float y2 = p2.getY();
	int k;

	float dx = x2 - x1;
	float dy = y2 - y1;

	if (abs(dx) >= abs(dy))
		k = abs(dx);
	else
		k = abs(dy);
	if (k != 0) {
		float xinc = dx / k;
		float yinc = dy / k;

		float x = x1;
		float y = y1;
		Point2D p;
		p.setX(x);
		p.setY(y);
		result.push_back(p);

		for (int i = 1; i < k; i++)
		{
			x = x + xinc;
			y = y + yinc;
			Point2D p;
			p.setX(x);
			p.setY(y);
			result.push_back(p);
		}
	}
	
	return result;
}