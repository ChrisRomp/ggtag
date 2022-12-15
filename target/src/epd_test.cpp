#define DEBUG 1
#include "pico/stdlib.h"
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    stdio_init_all();
    // wait for USB CDC connect
    while (!stdio_usb_connected()) {
        tight_loop_contents();
    }
#if defined(EPD_2IN13)
    printf("Using 2.13inch display\n");
#elif defined(EPD_3IN52)
    printf("Using 3.52inch display\n");
#else
    #error "Unsupported display"
#endif
    printf("EPD module init\n");
    if(DEV_Module_Init() != 0) {
        printf("EPD module init failed\n");
        while (1) { tight_loop_contents(); }
    }
    printf("e-Paper Init and Clear...\n");
    EPD_Init();
    //Create a new image cache
    UWORD imgSize = ((EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT;
    UBYTE *img = NULL;
    if((img = (UBYTE *)malloc(imgSize)) == NULL) {
        printf("Failed to allocate memory\n");
        while (1) { tight_loop_contents(); }
    }
    Paint_NewImage(img, EPD_WIDTH, EPD_HEIGHT, 90, WHITE);
    Paint_Clear(WHITE);
    Paint_DrawRectangle(5, 5, EPD_HEIGHT-5, EPD_WIDTH-5, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawString_EN(EPD_HEIGHT/2, EPD_WIDTH/2, "Hello World", &Font16, WHITE, BLACK);
    EPD_Display(img, NULL);
    EPD_Sleep();
    while (1) { tight_loop_contents(); }
    return 0;
}