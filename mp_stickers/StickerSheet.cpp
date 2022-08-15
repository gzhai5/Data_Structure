#include "Image.h"
#include "cs225/PNG.h"
#include "StickerSheet.h"


using namespace cs225;

StickerSheet::StickerSheet (const Image &picture, unsigned max){
    base_pic = picture;
    max_num = max;
    img = new Image*[max_num];
    x_cord = new unsigned[max_num];
    y_cord = new unsigned[max_num];
    for (unsigned i=0; i<max_num; i++){
        img[i] = NULL;
        x_cord[i] = 0;
        y_cord[i] = 0;
    }
}

StickerSheet::~StickerSheet (){
    _destroy();
}


void StickerSheet::_destroy(){
    if(img != NULL){
        delete[] img;
    }
    if(x_cord != 0){
        delete[] x_cord;
    }
    if(y_cord != 0){
        delete[] y_cord;
    }
}




StickerSheet::StickerSheet (const StickerSheet &other){
    base_pic = other.base_pic;
    max_num = other.max_num;
    img = new Image*[max_num];
    x_cord = new unsigned[max_num];
    y_cord = new unsigned[max_num];
    for (unsigned i=0; i<max_num; i++){
        img[i] = other.img[i];
        x_cord[i] = other.x_cord[i];
        y_cord[i] = other.y_cord[i];
    }
}


const StickerSheet & StickerSheet::operator= (const StickerSheet & other){
    _destroy();
    this->base_pic = other.base_pic;
    this->max_num = other.max_num;
    this->img = new Image*[max_num];
    this->x_cord = new unsigned[max_num];
    this->y_cord = new unsigned[max_num];
    for (unsigned i=0; i<max_num; i++){
        this->img[i] = other.img[i];
        this->x_cord[i] = other.x_cord[i];
        this->y_cord[i] = other.y_cord[i];
    }
    return *this;
}	


void StickerSheet::changeMaxStickers (unsigned max){
    if (max != max_num){
        Image **img_temp = new Image*[max];
        unsigned *x_cord_temp = new unsigned[max];
        unsigned *y_cord_temp = new unsigned[max];
    
        if (max > max_num){
            for (unsigned i=0; i<max; i++){
                if (i < max_num){
                    img_temp[i] = img[i];
                    x_cord_temp[i] = x_cord[i];
                    y_cord_temp[i] = y_cord[i];
                }
                else{
                    img_temp[i] = NULL;
                    x_cord_temp[i] = 0;
                    y_cord_temp[i] = 0;
                }
            }
            max_num = max;
            _destroy();
            img = new Image*[max];
            x_cord = new unsigned[max];
            y_cord = new unsigned[max];
            for (unsigned i=0; i<max; i++){
                img[i] = img_temp[i];
                x_cord[i] = x_cord_temp[i];
                y_cord[i] = y_cord_temp[i];
            }
            // img = img_temp;
            // x_cord = x_cord_temp;
            // y_cord = y_cord_temp;
        }  
        if (max < max_num){
            for (unsigned i=0; i<max; i++){
                img_temp[i] = img[i];
                x_cord_temp[i] = x_cord[i];
                y_cord_temp[i] = y_cord[i];
            }
            max_num = max;
            _destroy();
            img = new Image*[max];
            x_cord = new unsigned[max];
            y_cord = new unsigned[max];
            for (unsigned i=0; i<max; i++){
                img[i] = img_temp[i];
                x_cord[i] = x_cord_temp[i];
                y_cord[i] = y_cord_temp[i];
            }
        } 
        if(img_temp != NULL){
            delete[] img_temp;
        }
        if(x_cord_temp != 0){
            delete[] x_cord_temp;
        }
        if(y_cord_temp != 0){
            delete[] y_cord_temp;
        }
    }
}	



int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
    int minusone = -1;
    for (unsigned i=0; i<max_num; i++){
        if (img[i] == NULL){
            img[i] = &sticker;
            x_cord[i] = x;
            y_cord[i] = y;
            return i;
        }
    }
    return minusone;
}


bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
    if ((index > max_num) || (img[index] == NULL)){
        return false;
    }
    else{
        for (unsigned i=0; i<max_num; i++){
            if (i == index){
                x_cord[i] = x;
                y_cord[i] = y;
            }
        }
        return true;    
    }
}	


void StickerSheet::removeSticker (unsigned index){
    for (unsigned i=0; i<max_num; i++){
        if (i == index){
            img[i] = NULL;
        }
    }
}




Image *StickerSheet::getSticker (unsigned index){
    if (index > max_num){
        return NULL;
    }
    else{
        return img[index];
    }
}



Image StickerSheet::render() const{
    unsigned final_width = base_pic.width();
    unsigned final_height = base_pic.height();
    for (unsigned i=0; i<max_num; i++){
        if (img[i] != NULL){
            if ((x_cord[i] + img[i]->width()) > base_pic.width()){
                final_width = x_cord[i] + img[i]->width();
            }
            // if ((x_cord[i] + img[i]->width()) <= base_pic.width()){
            //     final_width = base_pic.width();
            // }
            if ((y_cord[i] + img[i]->height()) > base_pic.height()){
                final_height = y_cord[i] + img[i]->height();
            }
            // if ((y_cord[i] + img[i]->height()) <= base_pic.height()){
            //     final_height = base_pic.height();
            // }
        }    
    }
    Image img_final = base_pic;
    img_final.resize(final_width, final_height);
    for(unsigned i = 0; i < max_num; i++){
        if(img[i] != NULL){
            for(unsigned x = x_cord[i]; x < (x_cord[i] + img[i]->width()); x++){
                for(unsigned y = y_cord[i]; y < (y_cord[i] + img[i]->height()); y++){
                    unsigned int new_x = x - x_cord[i];
                    unsigned int new_y = y - y_cord[i];
                    HSLAPixel &pixel1 = img[i]->getPixel(new_x, new_y);
                    HSLAPixel &pixel2 = img_final.getPixel(x,y);
                    if(pixel1.a != 0){
                        pixel2 = pixel1;
                    }
                }
            }
        }
    }
    return img_final;    
}







