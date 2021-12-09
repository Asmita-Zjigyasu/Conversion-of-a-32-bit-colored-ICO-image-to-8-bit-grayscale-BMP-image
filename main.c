#include<stdio.h>
#include<stdlib.h>
#include "structures.h"

#pragma pack(1)

int main()
{
    FILE* fin = fopen("fg.ico", "rb");
    FILE* fout = fopen("lplp.bmp", "wb");

    if (fin == NULL){
        printf("Image not detected");
        fclose(fout);
        return 0;
    }

    HEADERICO hi;
    INFOHEADERICO ihi;
    INFOHEADERBMP ihj;//ihj is reused as infoheader of bmp

    HEADERBMP hb;

    fread(&hi, sizeof hi, 1, fin);
    fread(&ihi, sizeof ihi, 1, fin);
    fread(&ihj, sizeof ihj, 1, fin);

    if ( hi.type != 1 || hi.numimage != 1 || ihi.colorplanes != 1 || ihi.bitspp != 32 ){
        printf("Header values don't match");
        fclose(fin);
        fclose(fout);
        return 0;
    }

    int row_size_32 = ((( ihi.width*32 + 31 ) /32 )*4 );//due to padding
    int row_size_8 = ((( ihi.width*8 + 31 ) /32 )*4 );//note the value will not be an integer, this equation assumes int will act as a floor function

    int pixel_array_size_32 = row_size_32*ihi.height;
    int pixel_array_size_8 = row_size_8*ihi.height;

	ihj.width = ihi.width;
	ihj.height = ihi.height;
	ihj.imagesize = 54 + 1024 + pixel_array_size_8;
    ihj.bits = 8;

	hb.type = 0x4d42;//due to little endian 424d is stored
	hb.size = 54 + 1024 + pixel_array_size_8;
	hb.reserved1 = 0;
	hb.reserved2 = 0;
	hb.offset = 54;
 
    //We'll read the source image in rows
    unsigned char *pixel_32 = (unsigned char *)malloc(pixel_array_size_32);
    unsigned char *pixel_8 = (unsigned char *)malloc(pixel_array_size_8);

/*  unsigned char paxel_32[pixel_array_size_32];
    unsigned char paxel_8[pixel_array_size_8];
    unsigned char *pixel_32 = paxel_32;
    unsigned char *pixel_8 = paxel_8;

    ^An alternate to malloc(for this case)(remove free function in that case)
*/        

    fread(pixel_32, 1, pixel_array_size_32, fin);

    unsigned char colour_palette[1024] = {0};//8-bit bmp needs a colour palette
    
    for(int i = 0; i < 256; i++){
        colour_palette[ i*4 + 0 ] = (unsigned char)i;
        colour_palette[ i*4 + 1 ] = (unsigned char)i;
        colour_palette[ i*4 + 2 ] = (unsigned char)i;
    }

    unsigned char blue, green, red, greyscaled;

    for(int i = ihj.height - 1; i >= 0; i--)
        for(int j = 0; j < ihj.width; j++){
            blue = pixel_32[ i*row_size_32 + j*4 + 0 ];
            green = pixel_32[ i*row_size_32 + j*4 + 1 ];
            red = pixel_32[ i*row_size_32 + j*4 + 2 ];
            greyscaled = (unsigned char)( 0.299*red + 0.587*green + 0.114*blue );
            pixel_8[ i*row_size_8 + j ] = greyscaled; //this will match the index in fout
        }

    fwrite(&hb, sizeof hb, 1, fout);
    fwrite(&ihj, sizeof ihj, 1, fout);

    fwrite(colour_palette, 1, 1024, fout);

    fwrite(pixel_8, 1, pixel_array_size_8, fout);

    free(pixel_32);//deallocating the memory used by malloc
    free(pixel_8);

    fclose(fout);
    fclose(fin);

    return 0;
}