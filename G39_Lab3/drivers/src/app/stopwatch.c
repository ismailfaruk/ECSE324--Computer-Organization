//
// stopwatch.c
//



#include "../../inc/pushbuttons.h"
#include "../../inc/HEX_displays.h"
#include "../../inc/HPS_TIM.h"



int program_stopwatch(void)
{
    enum _stopwatch_state
    {
        STARTED,
        STOPPED
    };

    enum _stopwatch_state state = STOPPED;

    int edgecap = 0;

    int minutes = 0;
    int seconds = 0;
    int ds = 0;

    HPS_TIM_config_t hps_tim0;
    HPS_TIM_config_t hps_tim1;

    hps_tim0.tim = TIM0;
    hps_tim0.timeout = 10000;
    hps_tim0.LD_en = 1;
    hps_tim0.INT_en = 1;
    hps_tim0.enable = 1;

    // Configure the stopwatch timer.
    HPS_TIM_config_ASM(&hps_tim0);

    hps_tim1.tim = TIM1;
    hps_tim1.timeout = 5000;
    hps_tim1.LD_en = 1;
    hps_tim1.INT_en = 1;
    hps_tim1.enable = 1;

    // Configure the pushbutton timer.
    HPS_TIM_config_ASM(&hps_tim1);

    // Enable pushbutton interrupts (i.e. so that we can read from edgecapture register).
    enable_PB_INT_ASM(PB0 | PB1 | PB2 | PB3);

    // Start off by displaying a stopwatch time of 00:00:00.
    HEX_write_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5, 0);

    // Loop forever.
    while (1)
    {
        // Check if the pushbutton timer has finished.
        if (HPS_TIM_read_INT_ASM(TIM1))
        {
            // Reset the pushbutton timer.
            HPS_TIM_clear_INT_ASM(TIM1);

            // Read which buttons have been pushed since the last read.
            edgecap = read_PB_edgecap_ASM();

            // Clear pushbutton edgecapture register.
            PB_clear_edgecap_ASM(PB0 | PB1 | PB2 | PB3);

            if (edgecap & PB0)
            {
                // Start the stopwatch.
                state = STARTED;
            }
            if (edgecap & PB1)
            {
                // Stop the stopwatch.
                state = STOPPED;
            }
            if (edgecap & PB2)
            {
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
        }

        switch (state)
        {
            case STARTED:
                // Check if the stopwatch timer has finished.
                if (HPS_TIM_read_INT_ASM(TIM0))
                {
                    // Reset the stopwatch timer.
                    HPS_TIM_clear_INT_ASM(TIM0);

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
