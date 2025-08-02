# philosophers_sim

This is a simulation of the 'dining philosophers problem'- a metaphor used to illustrate a problem called
data-races that occur commonly in multi-threading/parallel processing/concurrent programming.

The idea is that a group of philosophers are dining at a circular table, and they each share a fork 
with the philosopher on either side of them. However, they can only eat with two forks. This means
their eating times must be carefully coordinated so they don't try to use the same fork at the same 
time and become stuck fighting over the fork.

make all to compile :)
./philo to run
