# About

This is a school project for my electronics class (12th Grade).
It involves 2 ESPs (ESP-WROOM-32) and a Broker Server.

# Main ESP

It collects data from its sensors:
- Temperature
- Humidity
- Soil Moisture
- Light
  
Then it shows this data on its screen and sends the data to the Broker Server.

# Broker Server

One of the challenges that comes with worldwide communication is hosting a server,
which involves opening ports and even paying monthly for a static IP (which I had to pay for).

If I created the server on the Main ESP itself, every time I moved it I would be required to repeat this process.
Instead, I can create a server at my home that never moves and do this process only once.

Also, running a server is intensive work, especially if it is multi-threaded.

# Client ESP

It receives the sensor data from the Broker Server and shows it on its screen.

In a situation where the received data implies that the condition of the greenhouse is not good,
an alarm will be set off until it is fixed.

# HTML Client

It receives the sensor data from the Broker Server and displays it in a web browser (via HTML).
