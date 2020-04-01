var express = require('express');
var bodyParser = require('body-parser');
var multer = require('multer');
var upload = multer();
const data = require('./demo.json')

var app = express()
var fs = require('fs');
const jsonfile = require('jsonfile') // new extension for easy appending of json files
var mvdkey = 'abcd';
var crkey = '123456';
app.set('views', './views');
app.engine('html', require('ejs').renderFile); // ejs is a type of templating engine closer to html

app.set('view engine', 'html');

app.get('/', function(req, res) {
    res.render('home');


});


app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use(upload.array());
app.use(express.static('public'));

/////// 


app.post('/auth', function(req, res) {
    var username = req.body.username;
    var password = req.body.password;
    if (username == 'mvd' && password == mvdkey) {
        res.render('contact');
    } else if (username == 'police' && password == crkey) {
        res.header("Content-Type",'application/json');
        res.send(JSON.stringify(data));
          } else {
        res.render('404');
    }
});




app.post('/getdata', function(req, res) {
    console.log(req.body);

    //req.body is not in a JSON format so convert to JSON is by stringify.
    fs.readFile('demo.json', function(err, data) {

        var data = JSON.stringify(req.body)
        var json = JSON.parse(data);

        jsonfile.writeFileSync("demo.json", json, { flag: 'a' }, function(err) { //flag =a is uded for appending to file
            if (err)
                throw err;
            console.log('The "data to append" was appended to file!');
        });

    })

    res.send('The Information Is Successfully registered');

});
app.listen(3800, () => {
    console.log('App listening on port 3800!');
});