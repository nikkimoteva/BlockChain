#include "block.h"
#include <iostream>
#include <cmath>
#include <cstdlib>


void Block::build(PNG & im, int column, int width) {
    HSLAPixel emptyPixel(0, 0, 0, 0);
    data.resize(width);
    for (int i = 0; i< width; i++) {
        data[i].resize(im.height());
    }

    for (int x = 0; x < width; x++) {
        for (unsigned y = 0; y < im.height(); y++) {
            data[x][y] = emptyPixel;
        }
    }

    unsigned widthing = column + width;
    if (widthing > im.width()) {
        widthing = im.width();
    }

    for(int x = column; x < widthing; x++) {
        for(unsigned y = 0; y < im.height(); y++) {
            HSLAPixel *pixel = im.getPixel(x, y);
            data[x-column][y].a = pixel->a;
            data[x-column][y].h = pixel->h;
            data[x-column][y].l = pixel->l;
            data[x-column][y].s = pixel->s;
        }
    }
}


void Block::render(PNG & im, int column) const{
    unsigned newWidth = column + data.size();
    unsigned newHeight = height();
    if (newWidth > im.width()){
        newWidth = im.width();
    }
    if (newHeight > im.height()) {
        newHeight = im.height();
    }
    for (unsigned x = column; x < newWidth; x++) {
        for (unsigned y = 0; y < newHeight; y++) {
            HSLAPixel *pixel = im.getPixel(x, y);
            pixel->a = data[x-column][y].a;
            pixel->h = data[x-column][y].h;
            pixel->l = data[x-column][y].l;
            pixel->s = data[x-column][y].s;
        }

    }

}

void Block::greyscale() {
    for (int x = 0; x < width(); x++) {
        for (int y = 0; y < height(); y++) {
          data[x][y].s = 0;
        }
    }

}

int Block::width() const{
    return data.size();
}

int Block::height() const{
    return data[0].size();
}