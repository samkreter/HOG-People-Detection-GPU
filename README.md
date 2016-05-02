##People Dectection CPU and GPU comparision 

Building
--------

1. Perform the standard cmake operations in the to create a build directory

2. run the make command to complie

3. If you are on a GPU capable device with cuda installed you will see two executables

	- GpuCpuTest: this will be the comparision test, the main exectuable to run

	- CpuRun: just a way to test the opencv implmenetion on a device without a GPU

4. Execute the GpuCpuTest in order to see the comparison 
