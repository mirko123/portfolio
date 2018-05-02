//
//  Calculator.h
//  3D visualisation
//
//  Created by Мирослав Николов on 10.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef Calculator_h
#define Calculator_h

#include <math.h>
#include <vector>

#include "Point.h"
#include <iostream>

class Calculator {
    
public:
    double calcLineByPoints2d(double x, Point p1, Point p2) {
        double coef1 = (p2.y - p1.y)/(p2.x - p1.x);
        double coef2 = p1.y - p1.x*(p2.y - p1.y)/(p2.x - p1.x);
        return x*coef1 + coef2;
    }
    std::vector<std::pair<double, double>> makeLine2d(Point p1, Point p2) {
        double distance = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
        std::cout<<distance<<std::endl;
        double coef = fabs(p1.x - p2.x)/distance;
        std::cout<<coef<<std::endl;
        std::cout<<"dasdsa"<<std::endl;
        
        std::vector<std::pair<double, double>> result;
        if (p1.x < p2.x) {
            for (double x = p1.x; x < p2.x; x+=coef) {
                double y = calcLineByPoints2d(x,p1, p2 );
                result.push_back(std::pair<double,double>(x,y));
            }
        }
        else {
            
            for (double x = p2.x; x < p1.x; x+=coef) {
                double y = calcLineByPoints2d(x,p1, p2 );
                result.push_back(std::pair<double,double>(x,y));
            }
        }
        return result;
    }
};
#endif /* Calculator_h */
