const https = require('https');
var fs = require('fs');
var YQL = require("yql");

new YQL.exec('select * from data.html.cssselect where url="http://net.tutsplus.com/" and css=".post_title a"', function(response) {
    
    console.log(response);

    
});



   


