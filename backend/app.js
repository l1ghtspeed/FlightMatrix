var Client = require('node-rest-client').Client;
var fs = require('fs');


var username = 'danthemanzspam';
var apiKey = '291f22ec397138d6d12a82e268e974d719a673a9';
var fxmlUrl = 'https://flightxml.flightaware.com/json/FlightXML3/'

var client_options = {
	user: username,
	password: apiKey
};
var client = new Client(client_options);

client.registerMethod('getFlightTrack', fxmlUrl + 'GetFlightTrack', 'GET');


var coordset = [];


async function updateCoords(arr){
    for(let i = 0; i < arr.length-2; i++){
        let output = await gft(arr[i]);
        coordset[i] = [JSON.stringify(output.GetFlightTrackResult.tracks[output.GetFlightTrackResult.tracks.length-1].longitude),
                JSON.stringify(output.GetFlightTrackResult.tracks[output.GetFlightTrackResult.tracks.length-1].latitude)];
    }

    let final = "";

    for(let i = 0; i < coordset.length; i++){
        final += coordset[i][0] + " "+ coordset[i][1] + "\n";
    }

    fs.writeFile("../src/out.txt", final, function(err) {
        if(err) {
            return console.log(err);
        }
        console.log("The file was saved!");
    }); 
}

function gft(inp) {
    return new Promise((res, rej) => {
        client.methods.getFlightTrack({ parameters: { ident: inp } }, function (data, response) {
            res(data);
        });
    });
}


setInterval(function(){
    fs.readFile('./ids.txt', 'utf8', function (err,data) {
        if (err) {
        return console.log(err);
        }
        var idArray = data.split('\n');
        updateCoords(idArray)
    }
)}, 3000000);


