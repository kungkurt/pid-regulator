## Integral
while i have implemented a clamp restriction for integral windup, it has its limits.<br />
and also the how much is added for each clock period can be in need of adjusting for diffrent constructions.<br />
<br />
#### integral windup
with integral windup the clamp limits are defined in <integral.h> with the macros<br />
  - CLAMP_LOW_LIMIT
  - CLAMP_HIGH_LIMIT
<br />
#### integral buildup
right now the buildup on the integral will add a fraction of the gain(Gi) based on the update frequency(how often the integral runs)<br />
this should probably need to be adjusted with diffrent constructions. <br />