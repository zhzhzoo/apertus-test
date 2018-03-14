#include <stdio.h>
#define LODEPNG_NO_COMPILE_CPP
#include "lodepng.h"

unsigned char buf_r[1536][2048], buf_g1[1536][2048], buf_g2[1536][2048], buf_b[1536][2048], buf_rgb24[1536][2048][3];

int main()
{
    unsigned char buffer[2048 * 3];
    FILE *fp = fopen("portrait-gainx2-offset2047-20ms-02.raw12", "rb");
    int i, j, x = 0, yy;
    unsigned char c1, c2, c3;
    unsigned error;
    for (int i = 0; i < 1536; i++) {
        fread(buffer, 2048 * 3, 1, fp);
        yy = 0;
        for (int j = 0; j < 2048; j++) {
            c1 = buffer[yy], c2 = buffer[yy + 1], c3 = buffer[yy + 2];
            buf_r[i][j] = c1;
            buf_g1[i][j] = (unsigned int)(c2 << 4) + (c3 >> 4);
            yy += 3;
        }
        fread(buffer, 2048 * 3, 1, fp);
        yy = 0;
        for (int j = 0; j < 2048; j++) {
            c1 = buffer[yy], c2 = buffer[yy + 1], c3 = buffer[yy + 2];
            buf_g2[i][j] = c1;
            buf_b[i][j] = (unsigned int)(c2 << 4) + (c3 >> 4);
            buf_rgb24[i][j][0] = buf_r[i][j];
            buf_rgb24[i][j][1] = ((unsigned int)buf_g1[i][j] + buf_g2[i][j]) >> 1;
            buf_rgb24[i][j][2] = buf_b[i][j];
            yy += 3;
        }
    }
    fclose(fp);
    error = lodepng_encode24_file("portrait-gainx2-offset2047-20ms-02.png", buf_rgb24[0][0], 2048, 1536);
    if(error) printf("error saving 24bit %u: %s\n", error, lodepng_error_text(error));
    error = lodepng_encode_file("portrait-gainx2-offset2047-20ms-02_red.png", buf_r[0], 2048, 1536, LCT_GREY, 8);
    if(error) printf("error saving red %u: %s\n", error, lodepng_error_text(error));
    error = lodepng_encode_file("portrait-gainx2-offset2047-20ms-02_green1.png", buf_g1[0], 2048, 1536, LCT_GREY, 8);
    if(error) printf("error saving green1 %u: %s\n", error, lodepng_error_text(error));
    error = lodepng_encode_file("portrait-gainx2-offset2047-20ms-02_green2.png", buf_g2[0], 2048, 1536, LCT_GREY, 8);
    if(error) printf("error saving green2 %u: %s\n", error, lodepng_error_text(error));
    error = lodepng_encode_file("portrait-gainx2-offset2047-20ms-02_blue.png", buf_b[0], 2048, 1536, LCT_GREY, 8);
    if(error) printf("error saving blue %u: %s\n", error, lodepng_error_text(error));
    return 0;
}
