var Client = require('node-rest-client').Client;
var fs = require('fs');

var username = 'danthemanzspam';
var apiKey = '528d4c43cbd20e404c88329c1ba0e0316c3dd25e';
var fxmlUrl = 'https://flightxml.flightaware.com/json/FlightXML3/'

var client_options = {
	user: username,
	password: apiKey
};
var client = new Client(client_options);

client.registerMethod('getFlightTrack', fxmlUrl + 'GetFlightTrack', 'GET');


var coordset = [];


async function updateCoords(arr){
    for(let i = 0; i < arr.length-1; i++){
        let output = await gft(arr[i]);
        
        console.log(typeof output.GetFlightTrackResult);

        if(typeof output.GetFlightTrackResult == 'undefined'){
            //restriction due to five calls a minute
            await sleep(65000);
            let newOutput = await gft(arr[i]);
            console.log(typeof newOutput.GetFlightTrackResult);
            if (typeof newOutput.GetFlightTrackResult != 'undefined'){
                coordset[i] = [JSON.stringify(newOutput.GetFlightTrackResult.tracks[newOutput.GetFlightTrackResult.tracks.length-1].longitude),
                        JSON.stringify(newOutput.GetFlightTrackResult.tracks[newOutput.GetFlightTrackResult.tracks.length-1].latitude)];
            }
        } else {
            coordset[i] = [JSON.stringify(output.GetFlightTrackResult.tracks[output.GetFlightTrackResult.tracks.length-1].longitude),
                    JSON.stringify(output.GetFlightTrackResult.tracks[output.GetFlightTrackResult.tracks.length-1].latitude)];
        }
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

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}
  

function gft(inp) {
    return new Promise((res, rej) => {
        console.log(inp)
        client.methods.getFlightTrack({ parameters: { ident: inp } }, function (data, response) {
            res(data);
        });
    });
}


    fs.readFile('./ids.txt', 'utf8', function (err,data) {
        if (err) {
        return console.log(err);
        }
        var idArray = data.split('\n');
        updateCoords(idArray)
    }
);

setInterval(function(){
    fs.readFile('./ids.txt', 'utf8', function (err,data) {
        if (err) {
        return console.log(err);
        }
        var idArray = data.split('\n');
        updateCoords(idArray)
    }
)}, 1800000);


