# imx_perf

There is a PMU for ddr performance in i.MX8. This tool is used to profile ddr with it.

#### INSTALLATION
clone it to $ANDROID\_SRC/external/imx\_perf and mm to build it.  
adb push the generated binary to device.

#### USAGE
imx_perf [type] [config]

For example, to profile ddr cycles (ddr cycles is 0 in the config)

	imx_perf ddr0 0

Then you can do something on the device. After that, press ctrl+c. It outputs as below,

	received SIGINT
	Used 10219501 cycles

If you want profile in the shell, it needs to be put in the backgroud,

	imx_perf ddr0 0 &

And then you run some shell command. After that, enter fg to bring it back and then ctrl+c.
