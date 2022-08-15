#include <cmath> 
#include "Image.h"
#include "cs225/PNG.h"
#include <iostream>

using namespace std;
using namespace cs225;

void Image::lighten(){
    unsigned int img_width = width();
    unsigned int img_height = height();
    for (unsigned x = 0; x < img_width; x++) {
        for (unsigned y = 0; y < img_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l <= 0.9){
                pixel.l = pixel.l + 0.1;
            }
            else{
                pixel.l = 1.0;
            }
        }
    }   
}	


void Image::lighten(double amount){
    unsigned int img_width = width();
    unsigned int img_height = height();
    for (unsigned x = 0; x < img_width; x++) {
        for (unsigned y = 0; y < img_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l <= (1.0 - amount)){
                pixel.l = pixel.l + amount;
            }
            else{
                pixel.l = 1.0;
            }
        }
    }   	
}


void Image::darken(){
    unsigned int img_width = width();
    unsigned int img_height = height();
    for (unsigned x = 0; x < img_width; x++) {
        for (unsigned y = 0; y < img_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l >= 0.1){
                pixel.l = pixel.l - 0.1;
            }
            else{
                pixel.l = 0.0;
            }
        }
    }   
}	


void Image::darken(double amount){
    unsigned int img_width = width();
    unsigned int img_height = height();
    for (unsigned x = 0; x < img_width; x++) {
        for (unsigned y = 0; y < img_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l >= (0.0 + amount)){
                pixel.l = pixel.l - amount;
            }
            else{
                pixel.l = 0.0;
            }
        }
    }   	
}


void Image::saturate(){
    unsigned int img_width = width();
    unsigned int img_height = height();
    for (unsigned x = 0; x < img_width; x++) {
        for (unsigned y = 0; y < img_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.s <= 0.9){
                pixel.s = pixel.s + 0.1;
            }
            else{
                pixel.s = 1.0;
            }
        }
    }   
}	


void Image::saturate(double amount){
    unsigned int img_width = width();
    unsigned int img_height = height();
    for (unsigned x = 0; x < img_width; x++) {
        for (unsigned y = 0; y < img_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.s <= (1.0 - amount)){
                pixel.s = pixel.s + amount;
            }
            else{
                pixel.s = 1.0;
            }
        }
    }   	
}


void Image::desaturate(){
    unsigned int img_width = width();
    unsigned int img_height = height();
    for (unsigned x = 0; x < img_width; x++) {
        for (unsigned y = 0; y < img_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.s >= 0.1){
                pixel.s = pixel.s - 0.1;
            }
            else{
                pixel.s = 0.0;
            }
        }
    }   
}	


void Image::desaturate(double amount){
    unsigned int img_width = width();
    unsigned int img_height = height();
    for (unsigned x = 0; x < img_width; x++) {
        for (unsigned y = 0; y < img_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.s >= (0.0 + amount)){
                pixel.s = pixel.s - amount;
            }
            else{
                pixel.s = 0.0;
            }
        }
    }   	
}


void Image::grayscale(){
    unsigned int img_width = width();
    unsigned int img_height = height();
    for (unsigned x = 0; x < img_width; x++) {
        for (unsigned y = 0; y < img_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s = 0;
        }
    }
}


void Image::rotateColor(double degrees){
    unsigned int img_width = width();
    unsigned int img_height = height();
    for (unsigned x = 0; x < img_width; x++) {
        for (unsigned y = 0; y < img_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.h <= (360 - degrees) && (pixel.h > -degrees)){
                pixel.h = pixel.h + degrees;
            }
            else if (pixel.h <= -degrees){
                pixel.h = pixel.h +360 +degrees;
            }
            else{
                pixel.h = pixel.h + degrees;
                pixel.h = pixel.h - 360;
            }
        }
    }
}


void Image::illinify(){
    unsigned int img_width = width();
    unsigned int img_height = height();
    for (unsigned x = 0; x < img_width; x++) {
        for (unsigned y = 0; y < img_height; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if ((pixel.h >= 114)&&(pixel.h <= 293)){
	            pixel.h = 216;
            }
            else{
                pixel.h = 11;
            }
        }
    }
}


void Image::scale(double factor){
    unsigned int img_width = width();
    unsigned int img_height = height();
    unsigned int scaled_img_width = img_width * factor;
    unsigned int scaled_img_height = img_height * factor;
    if (factor > 1.0){
        resize(scaled_img_width, scaled_img_height);
        for (int x = scaled_img_width - 1; x >= 0; x--) {
            for (int y = scaled_img_height - 1; y >= 0; y--) {
                HSLAPixel & blank_pixel = getPixel(x, y);
                unsigned new_x = floor((unsigned)x / (unsigned)factor);
                unsigned new_y = floor((unsigned)y / (unsigned)factor);
                blank_pixel= getPixel(new_x, new_y);
            }
        } 
    } 
    if (factor < 1.0){
        for (unsigned int x = 0; x < scaled_img_width; x++) {
            for (unsigned int y = 0; y < scaled_img_height; y++) {
                HSLAPixel & old_pixel = getPixel((x / factor), (y / factor));
                getPixel(x, y) = old_pixel;
            }
        }
    resize(scaled_img_width, scaled_img_height);        
    } 
}
   


void Image::scale(unsigned w, unsigned h){
    unsigned int img_width = width();
    unsigned int img_height = height(); 
    double ratio_w = (double)w/width();
    double ratio_h = (double)h/height();
    double factor = 1.0;
    
    // cout<<"w = "<<w<<endl;
    // cout<<"h = "<<h<<endl;
    // cout<<"img_width = "<<img_width<<endl;
    // cout<<"img_height = "<<img_height<<endl;
    // cout<<"ratio_w = "<<ratio_w<<endl;
    // cout<<"ratio_h = "<<ratio_h<<endl;


    if (ratio_w <= ratio_h){
        factor = ratio_w;
    }  
    else{
        factor = ratio_h;
    }
    // cout<<"factor = "<<factor<<endl;


    scale(factor);
    
    // unsigned int scaled_img_width = img_width * factor;
    // unsigned int scaled_img_height = img_height * factor;

    
    // if (factor > 1.0){
    //     resize(scaled_img_width, scaled_img_height);
    //     for (int x = scaled_img_width - 1; x >= 0; x--) {
    //         for (int y = scaled_img_height - 1; y >= 0; y--) {
    //             HSLAPixel & blank_pixel = getPixel(x, y);
    //             unsigned new_x = floor((unsigned)x / (unsigned)factor);
    //             unsigned new_y = floor((unsigned)y / (unsigned)factor);
    //             blank_pixel= getPixel(new_x, new_y);
    //         }
    //     } 
    // } 
    // if (factor < 1.0){
    //     for (unsigned int x = 0; x < scaled_img_width; x++) {
    //         for (unsigned int y = 0; y < scaled_img_height; y++) {
    //             HSLAPixel & old_pixel = getPixel((x / factor), (y / factor));
    //             getPixel(x, y) = old_pixel;
    //         }
    //     }
    // resize(scaled_img_width, scaled_img_height);        
    // } 
}
