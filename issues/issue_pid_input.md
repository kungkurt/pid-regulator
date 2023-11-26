## pid_input
pid_input component are using far more resources than any other and have a very inconsistant latency (9/342/288,848)
it would probably be a good idea to set Gp, Gi and Gd during compile time, but then you cannot adjust PID settings during runtime.