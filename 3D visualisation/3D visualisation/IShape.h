//
//  IShape.h
//  3D visualisation
//
//  Created by Мирослав Николов on 9.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef IShape_h
#define IShape_h

class IShape {
public:
    virtual void setBody(unsigned char* mat, double height, double width) = 0;
};

#endif /* IShape_h */
