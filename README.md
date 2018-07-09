# imx_perf

Simple program to access PMU through perf system call.

#### INSTALLATION
clone it to $ANDROID\_SRC/external/imx\_perf and mm to build it.  
adb push the generated binary to device.

#### USAGE
imx_perf [type] [config]

For example, to profile ddr cycles (ddr cycles is 0 in the config)

	imx_perf ddr0 0

Then start doing something on the device. After that, press ctrl+c. It outputs as below,

	received SIGINT
	Used 10219501 cycles

It can be put in the background as below, this is useful when profile in the shell:

	imx_perf ddr0 0 &

And then you run some shell command. After that, enter fg to bring it back and then ctrl+c.
