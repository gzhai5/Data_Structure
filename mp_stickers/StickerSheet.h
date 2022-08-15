/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include "cs225/PNG.h"


using namespace cs225;
class StickerSheet {
    public:
        StickerSheet (const Image &picture, unsigned max);
        ~StickerSheet ();
        StickerSheet (const StickerSheet &other);
        const StickerSheet & operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate (unsigned index, unsigned x, unsigned y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        Image render () const;

    private:
        void _destroy();


        Image base_pic;
        Image **img;
        unsigned int *x_cord;
        unsigned int *y_cord;
        unsigned max_num;
        // Image **img_temp;
        // unsigned int *x_cord_temp;
        // unsigned int *y_cord_temp;
};
