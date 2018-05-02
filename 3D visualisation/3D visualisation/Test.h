//
//  Test.h
//  3D visualisation
//
//  Created by Мирослав Николов on 16.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef Test_h
#define Test_h

# define M_PIl

void test_distance3d_1() {
    Point p1(1,-2,3);
    Point p2(4,5,6);
    
    if(Calculator::distance3d(p1, p2) != sqrt(9 + 49 + 9)) {
        throw std::invalid_argument("distance");
    }
}
void test_distance3d_2() {
    Point p1(7,0,0);
    Point p2(1,0,0);
    
    if(Calculator::distance3d(p1, p2) != 6) {
        throw std::invalid_argument("distance 3d");
    }
}
void test_distance3d_3() {
    Point p1(0,0,7);
    Point p2(0,0,1);
    
    if(Calculator::distance3d(p1, p2) != 6) {
        throw std::invalid_argument("distance 3d");
    }
}

void test_distanceOfIntersectToDirection_1() {
    Point position(0,0,0);
    Point direction(3,0,0);
    Camera::setCamera(position, direction, 720, 1400);
    Camera* camera = Camera::getCamera();
    Point target(3,3,0);
    
    double result = Calculator::distanceOfIntersectToDirection(*camera, target);
    double expected = 3;
    
    if(result != expected) {
        throw std::invalid_argument("distance of intersect to direction");
    }
}

void test_distanceToLineV2_1() {
    Point position(0,0,0);
    Point direction(3,0,0);
    Camera::setCamera(position, direction, 720, 1400);
    Point target(3,3,0);
    
    double result = Calculator::distanceToLine(position, direction, target);
    double expected = 3;
    if(result != expected) {
        throw std::invalid_argument("distance of intersect to direction");
    }
}
void test_distanceToLineV2_2() {
    Point position(0,0,0);
    Point direction(3,0,0);
    Camera::setCamera(position, direction, 720, 1400);
    Point target(6,6,0);
    
    double result = Calculator::distanceToLine(position, direction, target);
    double expected = 6;
    if(result != expected) {
        throw std::invalid_argument("distance of intersect to direction");
    }
}
void test_distanceToLineV2_3() {
    Point position(0,0,0);
    Point direction(3,0,0);
    Camera::setCamera(position, direction, 720, 1400);
    Point target(3,0,6);
    
    double result = Calculator::distanceToLine(position, direction, target);
    double expected = 6;
    if(result != expected) {
        throw std::invalid_argument("distance of intersect to direction");
    }
}

void test_angleBetweenPoints2d_1() {
    Point p1(5,5,0);
    Point p2(5,-5,0);
    Point center(0,0,0);
    
    //    Point p1(2,-1,0);
    //    Point p2(3,-2,1);
    //    Point center(1,1,1);
    
    double result = Calculator::angleBetweenPoints2d(p1, center, p2);
    double expected = 90;
    
    
    if(result != expected) {
        throw std::invalid_argument("distance of intersect to direction");
    }
}
void test_angleBetweenPoints2d_2() {
    Point p1(5,5,0);
    Point p2(5,-5,0);
    Point center(0,0,0);
    
    //    Point p1(2,-1,0);
    //    Point p2(3,-2,1);
    //    Point center(1,1,1);
    
    double result = Calculator::angleBetweenPoints2d(p2, center, p1);
    double expected = -90;
    
    
    if(result != expected) {
        throw std::invalid_argument("distance of intersect to direction");
    }
}

void test_angleBetweenPoints3d_1() {
    Point p1(5,0,5);
    Point p2(0,0,0);
    Point center(5,0,0);
    
    double result = Calculator::angleBetweenPoints3d(p1, center, p2);
    double expected = 90;
    
    if(result != expected) {
        throw std::invalid_argument("distance of intersect to direction");
    }
}
void test_angleBetweenPoints3d_2() {
    Point p1(5,5,0);
    Point p2(5,0,0);
    Point center(0,0,0);
    
    double result = Calculator::angleBetweenPoints3d(p1, center, p2);
    double expected = 45;
    
    if(result != expected) {
//        throw std::invalid_argument("distance of intersect to direction");
    }
}
void test_angleBetweenPoints3d_3() {
    Point p1(0,5,0);
    Point p2(5,0,0);
    Point center(0,0,0);
    
    double result = Calculator::angleBetweenPoints3d(p1, center, p2);
    double expected = 90;
    
    if(result != expected) {
        throw std::invalid_argument("distance of intersect to direction");
    }
}
void test_angleBetweenPoints3d_4() {
    Point p1(5,5,0);
    Point p2(5,0,0);
    Point center(0,0,0);
    
    double result = Calculator::angleBetweenPoints3d(p1, center, p2);
    double expected = 45;
    
    if(expected != result) {
        throw std::invalid_argument("dont work :(");
    }
}

void test_horisontalPerpendicular_1() {
    Point direction(5,0,5);
    Point center(0,0,2);
    double length = 5;
    
    Point expected(0,5,2);
    Point result = Calculator::horizontalPerpendicular(center, direction, 1, length);
    
    if(expected != result) {
        throw std::invalid_argument("dont work :(");
    }
    
}
void test_horisontalPerpendicular_2() {
    Point direction(5,0,5);
    Point center(0,0,2);
    double length = 5;
    
    Point expected(0,-5,2);
    Point result = Calculator::horizontalPerpendicular(center, direction, -1, length);
    
    if(expected != result) {
        throw std::invalid_argument("dont work :(");
    }
    
}
void test_horisontalPerpendicular_3() {
    Point direction(5,-5,5);
    Point center(0,0,2);
    double length = sqrt(50);
    
    Point expected(5,5,2);
    Point result = Calculator::horizontalPerpendicular(center, direction, 1, length);
    
    if(expected != result) {
        throw std::invalid_argument("dont work :(");
    }
}

void test_horisontalPerpendicular_4() {
    Point direction(20,-20,5);
    Point center(0,0,2);
    double length = sqrt(400);
    Point expected(10,10,2);
    Point result = Calculator::horizontalLeftPerpendicular(center, direction, length);
    Point result2 = Calculator::horizontalRightPerpendicular(direction, center, length);
    Point result3 = Calculator::horizontalLeftPerpendicular(direction, center, length);
    
    if(expected != result) {
//        throw std::invalid_argument("dont work :(");
    }
    center.Print();
    direction.Print();
    result.Print();
    result2.Print();
    result3.Print();
    
    Calculator::crossProduct(Point(3,-2,7), Point(2,-1,2)).Print();
}

void test() {
    Point camera(0,0,0);
    Point direction(950,0,0);
    double height = 600;
    double width = 900;
    Camera::setCamera(camera, direction, height, width);
    
//    test_distance3d_1();
//    test_distance3d_2();
//    test_distance3d_3();
//    
//    test_distanceOfIntersectToDirection_1();
//    test_distanceToLineV2_1();
//    test_distanceToLineV2_2();
//    test_distanceToLineV2_3();
//
//    test_angleBetweenPoints2d_1();
//    test_angleBetweenPoints2d_2();
//    
//    test_angleBetweenPoints3d_1();
//    test_angleBetweenPoints3d_2();
//    test_angleBetweenPoints3d_3();
//    test_angleBetweenPoints3d_4();
    
    test_horisontalPerpendicular_1();
    test_horisontalPerpendicular_2();
    test_horisontalPerpendicular_3();
    test_horisontalPerpendicular_4();
}

#endif /* Test_h */
