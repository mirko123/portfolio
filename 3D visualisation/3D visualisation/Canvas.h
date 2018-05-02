//
//  Canvas.h
//  3D visualisation
//
//  Created by Мирослав Николов on 10.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef Canvas_h
#define Canvas_h

class Canvas {
    bool isValidIndex(int x, int y, int z) {
        if (x < 0 || y < 0 || z < 0 || x >= camera->displayPlaneHorizontalSize || y >= camera->displayPlaneVerticalSize) {
            return false;
        }
        return true;
    }
public:
    unsigned char* image;
    int width;
    int height;
    Camera *camera;
    
    
    Canvas(unsigned char* image, int width, int height): image(image), width(width), height(height) {
        this->camera = Camera::getCamera();
    }
    unsigned int& get(int x, int y) {
        //        int el = ((unsigned int*)mat)[width*y + x];
        return ((unsigned int*)image)[width*y + x];
    }
    unsigned char& get(int x, int y, int c) {
        int index = 3*(y*width + x) + c;
        unsigned char &el = image[index];
        //        return ((unsigned int)(mat[index]));
        return el;
    }
    void set(int x, int y, unsigned int val) {
        get(x, y) = val;
    }
    void set(int x, int y, int z, unsigned char val) {
        if(!isValidIndex(x,y,z)) return;
        get(x, y, z) = val;
    }
};

#endif /* Canvas_h */
