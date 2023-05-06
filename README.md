# Team-001-13
Jason Paciorek (pacio017) , Aidan Boyle, Rebecca Hoff (hoff15420) , Nuh Misirli (misir002)

# What is the project about (overview of the whole project, not just the hw4)?
This project is about created a simulation of the University of Minnesota Campus with multiple entities (drone, robots, etc) and having all those entities all being able to travel through the simulation. To make the simulation a battery and wallet system were incorporated to create a transcation system and place for the drone to recharge after completing ths trip
# How to run the simulation (overview of the whole project, not just the hw4)?
Here is a quick overview of how to run the visualization

    Go to the project's directory
    
    cd <Path to Project>

    # Build the project with the following command:
    
    make -j
    
    # Run the project with the following command (./build/web-app <port> <web folder>) i.e:
        
    ./build/bin/transit_service 8081 apps/transit_service/web/

Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips.

*Note: 8081 will depends on what port you used. If you use port 8082, then it will be http://127.0.0.1:8082 instead.*

# How to run the simulation (through Docker)
Follow the docker hub link below or see the instructions below
    Go to the following docker repo: https://hub.docker.com/r/jasonpaciorek/drone_sim_battery_wallet_datacollection
<br>
<br>
Docker Pull Command for repo: 
```
    docker pull jasonpaciorek/drone_sim_battery_wallet_datacollection
```
How to Run Docker image: 
<br>
```
    docker run --rm -it -p 8091:8091 jasonpaciorek/drone_sim_battery_wallet_datacollection
```
How to interact with the Docker image:

   To **view** the simulation go to: http://127.0.0.1:8091

   To **schedule trips** in the simulation go to: http://127.0.0.1:8091/schedule.html
What does the simulation do specifically (individual features ie movement of entities etc) (overview of the whole project, not just the hw4)?
# Simulation

## Schedule
You will be able to schedule the robots for a ride in this page http://127.0.0.1:8081/schedule.html. 

Type passenger name, select start and end destination, and press `Schedule Trip` button to schedule a trip. 

Now go to 3D Visualization page and select the view of the entities on top right corner.

## 3D Visualization
You will be able to watch the simulation of the drone and the passenger here http://127.0.0.1:8081.

On top right corner, you can change your camera view into locking the entities.

# Video Presentation
https://www.youtube.com/watch?v=GVFuLKMziKA

# NEW FEATURES

## DATA COLLECTION
Data collection allows us to collect valuable data throughout the duration of the simulation. Data such as the time since a entity has been initially created, the total distance traveled by a particular entity, the account information of the entity (See wallet feature), The battery usage by a drone (See wallet feature), and the total number of trips that the drone has done. Multiple simulations can be run, and a folder called “CSV” will populate with data regarding each run of the simulation. The files contained in “CSV” will be named according to the time the simulation was ran. The user can interact with the CSVs by browsing the CSV/ directory. This adds to the existing work by allowing data to be outputted that can be analyzed. Data collection was implemented in the  using the singleton design pattern.

## WALLET
### What does it do?
The wallet sytem is a feature which allows our simulation to track the robot and the drones money held in there own accounts.
### Why is it significantly interesting?
This is significantly interesting because it allows us to create more diverse interactions between entities. This also creates a more realistic travel application similar to our modern apps like uber. There is now dynamics between robots, the drone, and recharge statrions, adding income to the trip process as well as adding payments as the robots pay for rides.
### How does it add to the existing work?  
It adds to existing work because it allows the drone to collect tolls from the robots, as it is performing a service. And the Recharge stations toll the robots as well, being payed to recharge the battery of the drone.
### Which design pattern did you choose to implement it and why? 
We used the decorator pattern as we wanted to wrap this with the battery as well as the entity it was with. Then we could update all these objects simultaneously.
### Instruction to use this new feature (if the new feature is not user interactable, please mention this as well) 
NOT USER INTERACTABLE

## BATTERY
### What does it do?
Our second feature is the Battery which allows our simulation to keep track of the drones battery.
### Why is it significantly interesting?
The reason that this feature is important is because it sets a limitation on the drone’s traveling capabilities. The drone only completes the trip if it has enough battery. The model is more realistic when the drone can only complete certain trips with its battery limitations. Anytime during the trip, if the drone does not have enough battery, it can always stop at a recharge station, recharge, and continue its trip.
### How does it add to the existing work? 
It adds to existing work because it allows for the already created Drone to have a limit to the number of trips it can complete before having to go to a recharge station
### Which design pattern did you choose to implement it and why? 
Decorator Pattern because the battery is modified during runtime. Similalry, other instances of the same class will not be affected by this(if there were more drone), so the individual object has the modified behavior. Through the decorator pattern we were able to add attrbiutes to the decorator dynamically. 
### Instruction to use this new feature (if the new feature is not user interactable, please mention this as well) 
NOT USER INTERACTABLE

# Sprint Retrospective 
# Pros
Working together in collaborative sessions helped team memmbers bounce of each others ideas

# Cons 
Assigning work more independently
Inferring that people have clear tasks that need to be done 

# DATA ANALYSIS 

TIME VS DISTANCE There is not an apparent relationship between time and the distance. As the time increases, it is not always the case that the distance increases or decreases

TIME VS ACCOUNT($) For the time and account($) for the robots, there is a positive relationship between the time of the trip and the account of the robots 

DISTANCE VS ACCOUNT($): There does not seem to be any relationship between these two variables

DRONE DISTANCE AND ACCOUNT BALANCEAs expected for the drone, as the distance increased, the account balances increased as well

DRONE NUMBER OF TRIPS AND ACCOUNT have a positive relationship

DRONE NUMBER OF TRIPS AND Distance have a positive relationship


