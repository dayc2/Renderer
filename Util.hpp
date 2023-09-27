//
// Created by Cameron Day on 7/9/23.
//

#include <iostream>

#ifndef RENDERER_UTIL_HPP
#define RENDERER_UTIL_HPP

#endif //RENDERER_UTIL_HPP

#pragma once

static void matMul(const float* matrix1, int width1, int height1, const float* matrix2, int width2, int height2, float*& dest){
    if(height1 != width2){
        std::cout << "Matrix multiplication error: height1 != width2" << std::endl;
        return;
    }
    delete dest;
    dest = new float[height1 * width2];
    for(int k = 0; k < height1 * width2; k++) {
        dest[k] = 0;
        for (int i = 0; i < width1; i++) {
            dest[k] += matrix1[i + (k/height1)*width1] * matrix2[width2 * i + (k%width2)];
//                std::cout << k << ", " << result[k] << ", " << i+(k/height1)*width1 << ", " << width2 * i + (k%width2) << ", " << matrix1[i+(k/height1)*width1] << ", " << matrix2[width2 * i + (k%width2)] << std::endl;
        }
    }
}