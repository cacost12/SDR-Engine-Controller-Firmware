<h1>Liquids Engine Controller Firmware</h1>

<p>PCB: Liquids Engine Controller L0002</p>
<p>MCU: STM32H750VBT6 </p>
<p>MPU Architecture: ARM Cortex-M7</p>

<p>Description: The Liquids Engine Controller PCB is the main embedded processor of SDR's Liquid Engine. The controller is 
equipped wth an STM32 ARM Cortex M4 processor and 4Mb of external flash for data logging. The board includes a 
micro-SD card jack for easy access to the logged data. The board includes many power sources for flexible use of the 
controller during testing and normal operation. These inlcude a 12V power jack, a USB Type B connector, and female 
header pins which are regulated down to 5V and 3.3V with a buck converter and linear regulator power supply. 
Additionally, the board includes a reset button and several LEDs for visual indication of the power and firmware status 
of the controller. </p>

<h2>Working Directory Structure</h2>

<p>
app: application code for the flight computer containing source directories

auto: auto-generated code from STM32CubeMX (not compiled into application)

init: Microcontroller initialization and configuration code

lib: third-party libraries for device drivers and middleware, microcontroller pin and peripheral configurations 

mod: Hardware modules containing hardware specific code for SDR boards

test: Test code
</p>

<h2>Source Directories:</h2>
<p>
blink:blinks status LED to test programmer and board setup 

cta: firmware to be run on the component test apparatus

demo: firmware containing small demo code

hotfire: firmware to be run during hotfire testing

terminal: firmware to allow terminal access to all PCB hardware 
</p>
