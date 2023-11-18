## Generating Testbench

when compiling the testbench (modelsim) fails so we cannot get information from 'verification statistics' and we only get estimated resource usage.<br />
it says too look at hls/pid-controller-simulation.prj/debug.log but nothing except "info" labels are there<br />
but i think it is because i am relying on previous result from each component so i cannot que several invocations.<br />
there is probably another way to tackle this with a new testbench but there is no time.<br >
<br />
i can at least run testbench on x86 with expected results.<br />
but since i need results to calculte new sensor value for next iteration makes me kinda stuck.