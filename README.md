# imx_perf

There is a PMU for ddr performance in i.MX8. This tool is used to profile ddr with it.

#### INSTALLATION
clone it to $ANDROID\_SRC/external/imx\_perf and mm to build it.  
adb push the generated binary to device.

#### USAGE
imx_perf [type] [config]

For example, to profile ddr cycles,

	imx_perf ddr-perf cycles
