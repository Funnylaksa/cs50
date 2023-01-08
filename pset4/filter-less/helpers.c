#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r=0; r<height; r++){
        for (int c=0; c<width; c++){
            int avg = round((image[r][c].rgbtRed + image[r][c].rgbtGreen + image[r][c].rgbtBlue)/3.00);
            image[r][c].rgbtRed = avg;
            image[r][c].rgbtGreen = avg;
            image[r][c].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r=0; r<height; r++){
        for (int c=0; c<width; c++){
            int sepiaRed = round(.393 * image[r][c].rgbtRed + .769 * image[r][c].rgbtGreen + .189 * image[r][c].rgbtBlue);
            int sepiaGreen = round(.349 * image[r][c].rgbtRed + .686 * image[r][c].rgbtGreen + .168 * image[r][c].rgbtBlue);
            int sepiaBlue = round(.272 * image[r][c].rgbtRed + .534 * image[r][c].rgbtGreen + .131 * image[r][c].rgbtBlue);
            if (sepiaRed > 255){
                sepiaRed = 255;
            }
            if (sepiaGreen > 255){
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255){
                sepiaBlue = 255;
            }
            image[r][c].rgbtRed = sepiaRed;
            image[r][c].rgbtGreen = sepiaGreen;
            image[r][c].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r=0; r<height; r++){
        for (int c=0; c<width/2; c++){
            RGBTRIPLE temp = image[r][c];
            image[r][c] = image[r][width-1-c];
            image[r][width-1-c] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int r=0; r<height; r++){
        for (int c=0; c<width; c++){
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float counter = 0.00;
            for (int i=-1; i<2; i++){
                for (int j=-1; j<2; j++){
                    if (r+i >= 0 && r+i < height && c+j >= 0 && c+j < width){
                        sumRed += image[r+i][c+j].rgbtRed;
                        sumGreen += image[r+i][c+j].rgbtGreen;
                        sumBlue += image[r+i][c+j].rgbtBlue;
                        counter++;
                    }
                }
            }
            temp[r][c].rgbtRed = round(sumRed/counter);
            temp[r][c].rgbtGreen = round(sumGreen/counter);
            temp[r][c].rgbtBlue = round(sumBlue/counter);
        }
    }
    for (int r=0; r<height; r++){
        for (int c=0; c<width; c++){
            image[r][c] = temp[r][c];
        }
    }
    return;
}
