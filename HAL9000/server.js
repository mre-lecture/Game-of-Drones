var express = require('express');
var SerialPort = require("serialport");


/* SERIAL-PORT */

SerialPort.list(function (err, ports) {
  if (err)
    return console.log('Error: ', err.message);

  ports.forEach(function(port) {
    console.log(port.comName);
    console.log(port.pnpId);
    console.log(port.manufacturer);
  });
});

return;

var serialBaudRate = 9600;
var path = "/dev/tty-usbserial1";
var port = new SerialPort(path, {
  baudRate: serialBaudRate
});

port.open(function (err) {
  if (err) {
    console.log('Error opening port: ', err.message);
    process.exit(1);
  }
});

/* REST-API */

var app = express();
var restPort = 3000;

app.get('/', function (req, res) {
  res.status(400);
  res.send({error:"y u no read docs"});
});

app.get('/skymaster/height/:val', function (req, res) {
  var val = req.params.val;
  if (val === undefined) {
    res.status(400);
    res.send({error:"val undefined"});
  } else {
    port.write("H:" + val + "\n");
    res.send({success:"Done!"});
  }
});

/*app.get('/skymaster/yaw/:val', function (req, res) {
  var val = req.params.val;
  if (val === undefined) {
    res.status(400);
    res.send({error:"val undefined"});
  } else {
    port.write("Y:" + val + "\n");
    res.send({success:"Done!"});
  }
});*/

app.listen(restPort);
console.log("REST-API listening on port " + restPort)
