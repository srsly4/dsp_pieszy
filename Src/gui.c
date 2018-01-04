#include "gui.h"
#include "main.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "cmsis_os.h"


static TS_StateTypeDef  TS_State;

void startTouchscreenTask(void const *arguments) {
	char buffer[30];
	uint16_t x, y;
	print_dbg("Touch task started");

	while(1) {
		BSP_TS_GetState(&TS_State);
		x = TS_State.touchX[0];
		y = TS_State.touchY[0];

		if (TS_State.touchDetected) {
			sprintf(&buffer, "Touch det at %d/%d", x, y);
			print_dbg(buffer);
			osDelay(250);
		}
		osDelay(50);
		//sprintf(&buffer, "RMS: %d", rms_value);
		//print_dbg(buffer);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(BSP_LCD_GetXSize()-32, 0, 32, BSP_LCD_GetYSize());
		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetBackColor(LCD_COLOR_DARKBLUE);
		uint32_t rms_height = (rms_value*BSP_LCD_GetYSize()/4000);
		rms_height = rms_height > BSP_LCD_GetYSize() ? BSP_LCD_GetYSize() : rms_height;
		BSP_LCD_FillRect(BSP_LCD_GetXSize()-32, BSP_LCD_GetYSize()-rms_height, 32, rms_height);
	}
}
