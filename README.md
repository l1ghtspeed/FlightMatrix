# FlightMatrix
LED Matrix Simulating Real-Time Boeing 787 Flights - Made for WindRiver Innovation Day

### APIs

FlightAware's FlightXML version 3.0; see https://flightaware.com/commercial/flightxml/v3/apiref.rvt for documentation and API reference. This project specifically used the GetFlightTrack call to get the lastest longitude and latitude for a single specified by plane ID.

The plane ID must be manually scraped (we used Python and BeautifulSoup4 for scraping) from the Flight Aware Website, as you can aggregate a list of flights specified by various parameters such as plane type, departure airport location, airline, etc.

The page we scraped lists all active planes of type Boeing 787 
https://flightaware.com/live/aircrafttype/787


### Backend Setup

Make sure you have the latest version of Node, npm, python, and pip installed.

Cd into the backend directory, then:

```
npm install
```

then 

```
pip install requests BeautifulSoup4
```

All external modules and packages should now be set up

### Hardware Setup
