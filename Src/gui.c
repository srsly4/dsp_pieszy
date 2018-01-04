#include "gui.h"
#include "main.h"
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
		osDelay(100);
		sprintf(&buffer, "RMS: %d", rms_value);
		print_dbg(buffer);
	}
}
