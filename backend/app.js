var Client = require('node-rest-client').Client;

var username = 'danthemanzspam';
var apiKey = '291f22ec397138d6d12a82e268e974d719a673a9';
var fxmlUrl = 'https://flightxml.flightaware.com/json/FlightXML3/'

var client_options = {
	user: username,
	password: apiKey
};
var client = new Client(client_options);

client.registerMethod('findFlights', fxmlUrl + 'FindFlight', 'GET');
client.registerMethod('weatherConditions', fxmlUrl + 'WeatherConditions', 'GET');

var findFlightArgs = {
	parameters: {
		aircrafttype: 'B787'
	}
};

client.methods.findFlights(findFlightArgs, function (data, response) {
	console.log('Number of Flights: %j', data.FindFlightResult.num_flights);
	console.log('First flight found: %j', data.FindFlightResult.flights[0]);
});

