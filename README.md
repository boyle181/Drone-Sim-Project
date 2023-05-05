# Team-001-13-homework4

# How to run the Simulation (With this repo)

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
    
    
    
# Simulation

## Schedule
You will be able to schedule the robots for a ride in this page http://127.0.0.1:8081/schedule.html. 

Type passenger name, select start and end destination, and press `Schedule Trip` button to schedule a trip. 

Now go to 3D Visualization page and select the view of the entities on top right corner.

## 3D Visualization
You will be able to watch the simulation of the drone and the passenger here http://127.0.0.1:8081.

On top right corner, you can change your camera view into locking the entities.

SINGLETON ANALYSIS 

TIME VS DISTANCE There is not an apparent relationship between time and the distance. As the time increases, it is not always the case that the distance increases or decreases

TIME VS ACCOUNT($) For the time and account($) for the robots, there is a positive relationship between the time of the trip and the account of the robots 

DISTANCE VS ACCOUNT($): There does not seem to be any relationship between these two variables

DRONE DISTANCE AND ACCOUNT BALANCEAs expected for the drone, as the distance increased, the account balances increased as well

DRONE NUMBER OF TRIPS AND ACCOUNT have a positive relationship

DRONE NUMBER OF TRIPS AND Distance have a positive relationship
