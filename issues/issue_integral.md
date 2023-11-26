## Integral
while i have implemented a clamp restriction for integral windup, it has its limits.<br />
<br />
#### integral windup
with integral windup the clamp limits are defined in <integral.h> with the macros<br />
  - CLAMP_LOW_LIMIT
  - CLAMP_HIGH_LIMIT
this means its not possible to change these values from software and a recompilation of hardware is necessary.<br />
<br />
#### ackumalation
when watching code for diffrent pid-controllers they seem to have slightly diffrent accumalating algorithms<br />
depending on if its a slow or fast system. like a slow system that run once every 10 seconds will accumalate more<br />
but the algorithm i have choosen is for fast systems.<br />
possible to implement both and use #ifdef macros to specify.<br />