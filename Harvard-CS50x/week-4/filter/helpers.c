// a program that allows a user to apply
// grayscale, reflection, blur, or edge detection filters to their images
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average_value;
    // looping through each row
    for (int i = 0; i < height; i++)
    {
        // looping through each column of the row
        for (int j = 0; j < width; j++)
        {
            // for each pixel, calculate the average pixel value
            // set each color value to the average value, rounding to nearest integer
            average_value =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average_value;
            image[i][j].rgbtGreen = average_value;
            image[i][j].rgbtRed = average_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loop for each row
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, end = round(width / 2); j < end; j++)
        {
            // swap pixels on horizontally opposite sides
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; // buffer for temporary storage of new colour values

    // average of colour values of pixels within 1 row and 1 column of the original pixel
    for (int i = 0; i < height; i++) // each row
    {
        for (int j = 0; j < width; j++) // for each pixel
        {
            float sum_blue = 0;
            float sum_green = 0;
            float sum_red = 0;
            int counter = 0;
            for (int row = -1; row < 2; row++) // loops thrice
            {
                for (int col = -1; col < 2; col++) // loops thrice
                {
                    if (i + row < 0 || i + row > height - 1) // top row, bottom row considerations
                    {
                        continue;
                    }
                    if (j + col < 0 ||
                        j + col > width - 1) // leftmost/rightmost columns considerations
                    {
                        continue;
                    }
                    sum_blue += image[i + row][j + col].rgbtBlue;
                    sum_green += image[i + row][j + col].rgbtGreen;
                    sum_red += image[i + row][j + col].rgbtRed;
                    counter++;
                }
            }
            temp[i][j].rgbtBlue =
                round(sum_blue / counter); // can't store directly in the image pixel as we still
                                           // need the original colour values for other pixels
            temp[i][j].rgbtGreen = round(sum_green / counter);
            temp[i][j].rgbtRed = round(sum_red / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) // for each pixel
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
// Compute Gx and Gy matrices for each channel of red, green and blue for each pixel
// for pixels at the border, treat any pixels past the border as having all 0 values
// Compute each new channel value as sqr(Gx^2 + Gy^2), make sure you cap this
// value at 255
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++) // each row
    {
        for (int j = 0; j < width; j++) // for each pixel
        {
            float gx_blue = 0;
            float gx_green = 0;
            float gx_red = 0;
            float gy_blue = 0;
            float gy_green = 0;
            float gy_red = 0;
            int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            for (int row = -1; row < 2; row++)
            {
                for (int col = -1; col < 2; col++)
                {
                    if (i + row < 0 || i + row > height - 1) // top row, bottom row considerations
                    {
                        continue;
                    }
                    if (j + col < 0 ||
                        j + col > width - 1) // leftmost/rightmost columns considerations
                    {
                        continue;
                    }
                    gx_blue += image[i + row][j + col].rgbtBlue * gx[row + 1][col + 1];
                    gx_green += image[i + row][j + col].rgbtGreen * gx[row + 1][col + 1];
                    gx_red += image[i + row][j + col].rgbtRed * gx[row + 1][col + 1];
                    gy_blue += image[i + row][j + col].rgbtBlue * gy[row + 1][col + 1];
                    gy_green += image[i + row][j + col].rgbtGreen * gy[row + 1][col + 1];
                    gy_red += image[i + row][j + col].rgbtRed * gy[row + 1][col + 1];
                }
            }
            int blue = round(
                sqrt(gx_blue * gx_blue +
                     gy_blue * gy_blue)); // can't store directly in the image pixel as we still
                                          // need the original colour values for other pixels
            int green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int red = round(sqrt(gx_red * gx_red + gy_red * gy_red));

            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
