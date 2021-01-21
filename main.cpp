#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Point
{
    double X;
    double Y;

    void OutputPoint(){
        cout << "(" << X << ';' << Y << ")" << endl;
    }

    Point(double x, double y){
        X = x;
        Y = y;
    }

    Point(){}
};

struct Vector
{
    double X;
    double Y;

    Vector(Point From, Point To){
        X = To.X - From.X;
        Y = To.Y - From.Y;
    }

    Vector(double x, double y){
        X = x;
        Y = y;
    }

    double GetLeng(){
        return sqrt(pow(X, 2) + pow(Y, 2));
    }
};

void Input(vector < Point > &arrayOfPoints){
    int n;
    cout << "введіть к-ть точок: ";
    cin >> n;
    for (int i = 0; i < n; i++){
        double x, y;
        cout << "введіть точоку: ";
        cin >> x >> y;
        Point p(x, y);
        arrayOfPoints.push_back(p);
    }
}

int FindIndexStartPoint(vector < Point > arrayOfPoints){
    int index = 0;
    for (int i = 1; i < arrayOfPoints.size(); i++){
        if (arrayOfPoints[index].Y > arrayOfPoints[i].Y){
            index = i;
        } else if (arrayOfPoints[index].Y == arrayOfPoints[i].Y && arrayOfPoints[index].X > arrayOfPoints[i].X){
            index = i;
        }
    }
    return index;
}

double FindCOSBetweenVectors(Vector A, Vector B){
    double topPart = A.X * B.X + A.Y * B.Y;
    return topPart / (A.GetLeng() * B.GetLeng());
}

vector < Point > FindVectorOfSortPoints(vector < Point > arrayOfPoints, int indexOfStartPoint){
    vector < Point > SortPoints;
    vector < double > COSPoints;

    SortPoints.push_back(arrayOfPoints[indexOfStartPoint]);
    COSPoints.push_back(0);

    for (int i = 0; i < arrayOfPoints.size(); i++){
        if (i != indexOfStartPoint) {
            Vector A(arrayOfPoints[indexOfStartPoint], arrayOfPoints[i]);
            Vector B(1, 0);
            double COS = FindCOSBetweenVectors(A, B);
            COSPoints.push_back(COS);
            SortPoints.push_back(arrayOfPoints[i]);
            int pos = COSPoints.size() - 1;
            while (pos > 1 && COSPoints[pos] > COSPoints[pos - 1]) {
                swap(COSPoints[pos], COSPoints[pos - 1]);
                swap(SortPoints[pos], SortPoints[pos - 1]);
                pos--;
            }
        }
    }

    return SortPoints;
}

bool IsTurnRight(Point A, Point B, Point C){
    double vectorMultip = (B.X - A.X) * (C.Y - A.Y) - (B.Y - A.Y) * (C.X - A.X);
    if (vectorMultip < 0){
        return true;
    }
    return false;
}

vector < Point > FindConvexChell(vector < Point > arrayOfPoints){
    int indexOfStartPoint = FindIndexStartPoint(arrayOfPoints);
    vector < Point > sortPoints = FindVectorOfSortPoints(arrayOfPoints, indexOfStartPoint);

    vector < Point > convexShell;
    convexShell.push_back(sortPoints[0]);
    convexShell.push_back(sortPoints[1]);
    for (int i = 2; i < sortPoints.size(); i++){
        convexShell.push_back(sortPoints[i]);

        int shellSize = convexShell.size()-1;
        while (IsTurnRight(convexShell[shellSize-2], convexShell[shellSize-1], convexShell[shellSize])){
            convexShell.erase(convexShell.end() - 2);
            shellSize--;
        }
    }
    return convexShell;
}

double FindPerimetr(vector < Point > M){
    double P = 0;
    for (int i = 0; i < M.size()-1; i++){
        Vector v(M[i], M[i+1]);
        double l = v.GetLeng();
        P += l;
    }
    return P;
}

vector < Point > FindMaxPerimetr(vector < Point > convexShell){
    double maxSqure = 0;
    vector < Point > biggestTriangle;
    for (int i = 0; i < convexShell.size()-2; i++){
        for (int j = i+1; j < convexShell.size()-1; j++){
            for (int k = j+1; k < convexShell.size(); k++){
                vector < Point > triangle = {convexShell[i], convexShell[j], convexShell[k]};
                double squre = abs(FindPerimetr(triangle));
                if (squre > maxSqure) {
                    maxSqure = squre;
                    biggestTriangle = triangle;
                }
            }
        }
    }
    return biggestTriangle;
}

int main() {
    vector < Point > arrayOfPoints;
    Input(arrayOfPoints);
    if (arrayOfPoints.size() == 1){
        arrayOfPoints[0].OutputPoint();
        return 0;
    }
    vector < Point > convexShell = FindConvexChell(arrayOfPoints);
    vector < Point > biggestTriangle = FindMaxPerimetr(convexShell);
    for (int i = 0; i < biggestTriangle.size(); i++){
        biggestTriangle[i].OutputPoint();
    }
}
