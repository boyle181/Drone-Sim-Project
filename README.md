# Team-001-13-homework4
# How to run the Simulation

Here is a quick overview of how to run the visualization

    Go to the project's directory
    
    cd <Path to Project>

    # Build the project with the following command:
    
    make -j
    
    # Run the project with the following command (./build/web-app <port> <web folder>) i.e:
        
    ./build/bin/transit_service 8081 apps/transit_service/web/

    Navigate to http://127.0.0.1:8081 and you should see a visualization.

Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips.

*Note: 8081 will depends on what port you used. If you use port 8082, then it will be http://127.0.0.1:8082 instead.*

# Simulation

## Schedule
You will be able to schedule the robots for a ride in this page http://127.0.0.1:8081/schedule.html. 

Type passenger name, select start and end destination, and press `Schedule Trip` button to schedule a trip. 

Now go to 3D Visualization page and select the view of the entities on top right corner.

## 3D Visualization
You will be able to watch the simulation of the drone and the passenger here http://127.0.0.1:8081.

On top right corner, you can change your camera view into locking the entities.
