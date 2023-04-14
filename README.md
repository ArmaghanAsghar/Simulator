# Breif
This is a small project to simulator the flight and charging of N number of aircrafts using multi-threading and thread synchronization strategies. 

# Code Flow
![Blank diagram](https://user-images.githubusercontent.com/54956731/232123872-bf7941c4-4a32-4703-ac52-bfde88ab3d35.jpeg)


# Architecture
![Simulator UML-3](https://user-images.githubusercontent.com/54956731/232108518-6100cc33-10ac-4b74-bc24-f40526dad104.jpeg)

# Working
* This simulator takes as input "total number of aircrafts", "total number of charging stations" and "hours of simulation". 
* The simulation is scaled with reference to 1 hr being equal to 1 second. So, a 3 hr simulation would be 3 seconds long. 
* The simulation consists of a main thread and multiple childern threads. Each child thread is associated with a aircraft object to perform operations of flying and charging. 
* The flow to charging stations is controlled using a counting semaphore. I have designed a custom semaphore as the C++20 semaphore did not allow dynamic assignment. 
* The simulation ends when the main thread times out i.e. when "hours of simulation" expire. At this point, the main thread notifies all childern thread 
to interrupt their operation, which in return stops populating the stats. (Some assumptions are made in this regard). 

# Logging
For the purpose of verifying the simulation, I have used thread-safe logging on console which shows all the events of the simulation as they happen for every aircraft. The numbers [x] is type of aircraft.<br/>

```
2023-03-27 12:32:30.867 [Main] Starting Planes!
2023-03-27 12:32:30.868 [Main] Aircraft types: 0, 0, 3, 2, 2, 1, 0, 3, 3, 4, 1, 2, 4, 0, 0, 2, 3, 0, 1, 0
2023-03-27 12:32:30.868 [0] isFlying
2023-03-27 12:32:30.868 [1] isFlying
...
2023-03-27 12:32:30.073 [1] hasCompleteFlight
...
2023-03-27 12:32:30.073 [3] InQueueToCharge
...
2023-03-27 12:32:31.274 [4] ChargeFull
...
2023-03-27 12:32:33.873 [Main] Stop all simulation
...
2023-03-27 12:32:33.873 [0] FlightInterrupted
...
2023-03-27 12:32:33.873 [2] ChargeInterrupted
...
2023-03-27 12:32:33.875 [Main] All simulations stopped!
```

# Results

```
Type: Aircraft A
Average flight time per flight: 1.44444
Average distance traveled per flight: 173.333
Average time charging per charge session: 0.6
Total number of faults: 6.61667
Total number of passenger miles: 72800

Type: Aircraft B
Average flight time per flight: 0.666667
Average distance traveled per flight: 66.6667
Average time charging per charge session: 0.2
Total number of faults: 0.633333
Total number of passenger miles: 8000

Type: Aircraft C
Average flight time per flight: 0.625
Average distance traveled per flight: 100
Average time charging per charge session: 0
Total number of faults: 0.125
Total number of passenger miles: 4799

Type: Aircraft D
Average flight time per flight: 1.33333
Average distance traveled per flight: 120
Average time charging per charge session: 0.62
Total number of faults: 1.60307
Total number of passenger miles: 4800

Type: Aircraft E
Average flight time per flight: 0.862069
Average distance traveled per flight: 25.8621
Average time charging per charge session: 0.3
Total number of faults: 2.46945
Total number of passenger miles: 413
```
