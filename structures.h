#ifndef HEADER_GUARD
#define HEADER_GUARD

#pragma pack(1)

typedef struct {                            //                                                   40
    unsigned int size;                      // Header size in bytes                              4
    int width;                              //                                                   4
    int height;                             // Width and height of image                         4
    unsigned short int planes;              // Number of colour planes                           2
    unsigned short int bits;                // Bits per pixel                                    2
    unsigned int compression;               // Compression type, 0 for in our case               4
    unsigned int imagesize;                 // Image size in byte                                4
    int xresolution;                        // Pixels per meter                                  4
    int yresolution;                        //                                                   4
    unsigned int ncolours;                  // Number of colours, set to 0                       4
    unsigned int importantcolours;          // Important colours, set to 0                       4
} INFOHEADERBMP; 

typedef struct {                            //                                                   16
    unsigned char width;                    // Width                                             1
    unsigned char height;                   // Height                                            1
    unsigned char colourcount;              // Color count                                       1
    char zero;                              // Reserved, should be 0                             1
    unsigned short int colorplanes;         // Color planes , should be 0 or 1                   2
    unsigned short int bitspp;              // Bits per pixel                                    2
    unsigned int bmpsize;                   // Size of the bitmap data in bytes                  4
    unsigned int offsetsize;                // Offset in the file                                4
} INFOHEADERICO;

typedef struct {                            //                                                   14
    unsigned short int type;                // Magic identifier (Set to 0x424d)                  2
    unsigned int size;                      // File size in bytes                                4
    unsigned short int reserved1;           // Intialize to 0                                    2
    unsigned short int reserved2;           // Same as above                                     2
    unsigned int offset;                    // Offset to image data, bytes                       4
} HEADERBMP;

typedef struct {                            //                                                   6
    unsigned short int zero;                // Reserved. Should always be 0.                     2
    unsigned short int type;                // Set to 1 for our case                             2
    unsigned short int numimage;            // Number of images in the file, 1 for us            2
} HEADERICO;

#endif