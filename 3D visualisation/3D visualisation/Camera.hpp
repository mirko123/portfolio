//
//  Camera.h
//  3D visualisation
//
//  Created by Мирослав Николов on 15.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "Point.h"

class Camera {
    static Camera *camera;
    Camera();
//    Camera(const Camera& other) = delete;
    Camera(Point position, Point direction, double displayPlaneVerticalSize, double displayPlaneHorizontalSize);
public:
    Point position;
    Point direction;
    double displayPlaneVerticalSize;
    double displayPlaneHorizontalSize;
    
    static Camera* getCamera();
    static Camera* setCamera(Point position, Point direction, double displayPlaneVerticalSize, double displayPlaneHorizontalSize);
    
    void move(double coef);
    void moveLeft(double coef);
    void moveRight(double coef);
    void moveTop(double coef);
    void moveBot(double coef);
    
    void rotateLeft(double coef);
    void rotateRight(double coef);
    
    void rotateTop(double coef);
    void rotateBot(double coef);
};
#endif /* Camera_h */

