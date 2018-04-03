//
// stopwatch_int.c
//



#include "../../inc/HEX_displays.h"
#include "../../inc/HPS_TIM.h"
#include "../../inc/ISRs.h"
#include "../../inc/int_setup.h"
#include "../../inc/pushbuttons.h"



int program_stopwatch_with_interrupts(void)
{
    enum _stopwatch_state
    {
        STARTED,
        STOPPED
    };

    enum _stopwatch_state state = STOPPED;

    int minutes = 0;
    int seconds = 0;
    int ds = 0;

    // Setups ISRs for FPGA Pushbutton KEYs and HPS Timer 0.
    int_setup(2, (int[]){ 73, 199 });

    HPS_TIM_config_t hps_tim0;

    hps_tim0.tim = TIM0;
    hps_tim0.timeout = 10000;
    hps_tim0.LD_en = 1;
    hps_tim0.INT_en = 0;
    hps_tim0.enable = 1;

    // Configure the stopwatch timer.
    HPS_TIM_config_ASM(&hps_tim0);

    // Enable pushbutton interrupts (i.e. so that we can read from edgecapture register).
    enable_PB_INT_ASM(PB0 | PB1 | PB2 | PB3);

    // Start off by displaying a stopwatch time of 00:00:00.
    HEX_write_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5, 0);

    // Loop forever.
    while (1)
    {
        if (fpga_pb_key0_flag)
        {
            fpga_pb_key0_flag = 0;

            // Start the stopwatch.
            state = STARTED;
        }
        if (fpga_pb_key1_flag)
        {
            fpga_pb_key1_flag = 0;

            // Stop the stopwatch.
            state = STOPPED;
        }
        if (fpga_pb_key2_flag)
        {
            fpga_pb_key2_flag = 0;

            // Redraw the display here if the stopwatch is stopped.
            if (state == STOPPED)
            {
                // Display stopwatch time of 00:00:00.
                HEX_write_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5, 0);
            }

            // Reset the stopwatch.
            minutes = 0;
            seconds = 0;
            ds = 0;
        }

        switch (state)
        {
            case STARTED:
                // Check if the stopwatch timer has finished.
                if (hps_tim0_int_flag)
                {
                    hps_tim0_int_flag = 0;

                    // Print the current elapsed time to the HEX display.
                    HEX_write_ASM(HEX0, ds % 10);
                    HEX_write_ASM(HEX1, ds / 10);
                    HEX_write_ASM(HEX2, seconds % 10);
                    HEX_write_ASM(HEX3, seconds / 10);
                    HEX_write_ASM(HEX4, minutes % 10);
                    HEX_write_ASM(HEX5, minutes / 10);

                    // Update the current elapsed time.
                    ds += 1;
                    seconds += ds / 100;
                    ds %= 100;
                    minutes += seconds / 60;
                    seconds %= 60;

                    // Check if we have reached our maximum elapsed time.
                    if (minutes >= 60)
                    {
                        // Stop / reset the stopwatch.
                        state = STOPPED;
                        minutes = 0;
                        seconds = 0;
                        ds = 0;
                    }
                }

                break;

            case STOPPED:
                // Do nothing.

                break;
        }
    }

    // Unreachable

    return 0;
}
