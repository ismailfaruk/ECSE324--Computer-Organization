# [ECSE324--Computer-Organization](https://www.mcgill.ca/study/2017-2018/courses/ecse-324)

This reopository contains the laboratory projects done for the course ECSE 324, using ARMx86 Assembly and C.

## Description

Lab experiments were done using an ARM processor on an Altera DE1-SoC single board computer. The FPGA chip on the DE1-SoC has an ARM processor in was programmed.

* **G39_Lab0** - Warmup - Flashing the computer system onto the board and running the demo program

*	[**G39_Lab1**(G39_Lab1%20-%20Introduction%20to%20ARM%20Programming/G39_Lab1_Report.pdf) - Introduction to ARM Programming - Fast standard deviation computation, centering an array and sorting in assembly.

*	[**G39_Lab2**](G39_Lab2%20-%20Stacks%2C%20Subroutines%2C%20and%20C/G39_Lab2_Report.pdf) - Stacks, Subroutines, and C - Fibonacci calculation using recursive subroutine calls, implementing stack. Computes the maximum of two numbers and returns the result.

*	[**G39_Lab3**](G39_Lab3%20-%20Basic%20IO%2C%20Timers%20and%20Interrupts/G39_Lab3_Report.pdf) - Basic IO, Timers and Interrupts - Setting up the basic I/O capabilities of the DE1-SoC computer - the slider switches, pushbuttons, LEDs and 7-Segment displays. After writing assembly drivers that interface with the I/O components, timers and interrupts are used to demonstrate polling and interrupt based **stopwatch**.

*	[**G39_Lab4**](G39_Lab4%20-%20High%20level%20IO%20-%20VGA%2C%20PS2%20Keyboard%2C%20and%20Audio/G39_Lab4_Report.pdf) - High level IO - VGA, PS2 Keyboard, and Audio - Used the VGA controller to display pixels and characters, used the PS/2 port to accept input from a keyboard and used the audio controller to play generated tones. The application read raw data from the keyboard and displayed it to the screen if it is valid. It uses the PS/2 keyboard and VGA monitor. Also created a driver for the audio port. The driver takes one integer argument and write it to both the left and the write FIFO only if there is space in both the FIFOs. The subroutine returns an integer value of 1 if the data was written to the FIFOs, and return 0 otherwise. It plays a 100 Hz square wave on the audio out port. 

*	[**G39_Lab5**](G39_Lab5%20-%20Synthesizer/G39_Lab5_Report.pdf) - Synthesizer - Combines the low-level ARM programming techniques acquired in the course and implements a musical synthesizer. Takes as input f and t and returns signal[t]. Uses a timer to feed the generated samples to the audio codec periodically. Implements a volume control with the keyboard so that the user can turn the volume (amplitude) up or down. Displays the waveform on the lab computer monitor.

## Built With

* [C](https://en.wikipedia.org/wiki/C_(programming_language)) - The programming language used
* [ARMx86 Assembly](https://www.ubuntu.com/) - The Linux Distro used for deployment and testing
* [Visual Studio Code](https://code.visualstudio.com/) - The source code editor
* [Altera DE1-SoC](https://www.terasic.com.tw/cgi-bin/page/archive.pl?Language=English&No=836) - The development kit used
* [ARM Cortex-A9](https://en.wikipedia.org/wiki/ARM_Cortex-A9) - The core programmed

![Altera DE1-SoC](Altera%20DE1-SoC.jpg)

## Authors

* [**Ismail Faruk**](https://github.com/ismailfaruk)

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
