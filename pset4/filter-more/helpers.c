#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int avg = round((image[r][c].rgbtRed + image[r][c].rgbtGreen + image[r][c].rgbtBlue) / 3.00);
            image[r][c].rgbtRed = avg;
            image[r][c].rgbtGreen = avg;
            image[r][c].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width / 2; c++)
        {
            RGBTRIPLE temp = image[r][c];
            image[r][c] = image[r][width - 1 - c];
            image[r][width - 1 - c] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float counter = 0.00;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (r + i >= 0 && r + i < height && c + j >= 0 && c + j < width)
                    {
                        sumRed += image[r + i][c + j].rgbtRed;
                        sumGreen += image[r + i][c + j].rgbtGreen;
                        sumBlue += image[r + i][c + j].rgbtBlue;
                        counter++;
                    }
                }
            }
            temp[r][c].rgbtRed = round(sumRed / counter);
            temp[r][c].rgbtGreen = round(sumGreen / counter);
            temp[r][c].rgbtBlue = round(sumBlue / counter);
        }
    }
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = temp[r][c];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int GxRed = 0;
            int GxGreen = 0;
            int GxBlue = 0;
            int GyRed = 0;
            int GyGreen = 0;
            int GyBlue = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (r + i >= 0 && r + i < height && c + j >= 0 && c + j < width)
                    {
                        GxRed += image[r + i][c + j].rgbtRed * Gx[i + 1][j + 1];
                        GxGreen += image[r + i][c + j].rgbtGreen * Gx[i + 1][j + 1];
                        GxBlue += image[r + i][c + j].rgbtBlue * Gx[i + 1][j + 1];
                        GyRed += image[r + i][c + j].rgbtRed * Gy[i + 1][j + 1];
                        GyGreen += image[r + i][c + j].rgbtGreen * Gy[i + 1][j + 1];
                        GyBlue += image[r + i][c + j].rgbtBlue * Gy[i + 1][j + 1];
                    }
                }
            }
            int GRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            int GGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            int GBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            if (GRed > 255)
            {
                GRed = 255;
            }
            if (GGreen > 255)
            {
                GGreen = 255;
            }
            if (GBlue > 255)
            {
                GBlue = 255;
            }
            temp[r][c].rgbtRed = GRed;
            temp[r][c].rgbtGreen = GGreen;
            temp[r][c].rgbtBlue = GBlue;
        }
    }
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = temp[r][c];
        }
    }
    return;
}
