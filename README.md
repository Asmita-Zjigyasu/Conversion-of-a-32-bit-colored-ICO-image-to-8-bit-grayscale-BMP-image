# Conversion-of-a-32-bit-colored-ICO-image-to-8-bit-grayscale-BMP-image
A program to convert the ICON image format to 8-bit grayscale BMP image format


COMPILATION:

-Put the 32bit ICO in the folder
-Open the folder in the terminal
-Use make command to compile the code and run ./output
-Converted image will appear in the same folder as the source file

Note:
-Make sure to change the source image name in the program before compilation.
-If the filename specified in the folder does not match the the specified in the program, the program ouputs Image not found and ends.
-Some other conditions like if the image is not 32 bit will also shut down the program.

ABOUT THE CODE:

1. Read the header information of the ico file using its infoheader, its header and bmpinfoheader as defined earlier from the source image. 
2. Assign a color palette for the destination BMP image. Since it is going to have 256 different levels of color(from black to white), we assign an array of size 1024, with all original terms 0. Assign the colors to the palette (0 0 0 0, 1 1 1 0, 2 2 2 0...), 0 0 0 0 = black and 255 255 255 0 = white. 
3. Extract the values of blue, green and red from the source image from each pixel and use a formula for calculating the value of the grayscale variable for the destination image using the previous color values. Assign the grayscale value to the pixels of the destination image.
4. Write the necessary information (i.e. the BMPINFOHEADER, BMPHEADER, new color palette, pixel size, padding correction etc.) to the destination file.
