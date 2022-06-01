const host = '202.148.1.57'
const port = '1883'
const connect_url = `mqtt://${host}:${port}`
const clientID = 'mqttjs_' + Math.random().toString(16).substr(2, 8)
const username = 'app-appktmxemoney'
const password = 'BgkfOGumPp6HP9x6mn2prnsNCJ4Hej'

const options = {
  port: port,
  clientId: clientID,
  username,
  password
}

const sql = require("./app/models/db.js");

const mqtt = require('mqtt')

const client  = mqtt.connect(connect_url, options)

function timeConverter(UNIX_timestamp){
  var datetime = new Date(UNIX_timestamp);
  if (datetime.getUTCMonth() )
  var year = datetime.getUTCFullYear();
  var month = datetime.getUTCMonth()+1;
  var date = datetime.getUTCDate();
  var hour = datetime.getHours();
  var min = datetime.getMinutes();
  var sec = datetime.getSeconds();
  var str_datetime = year + '-' + ('0'+month).slice(-2) + '-' + ('0'+date).slice(-2) + ' ' + ('0'+hour).slice(-2) + ':' + ('0'+min).slice(-2) + ':' + ('0'+sec).slice(-2) ;
  return str_datetime;
}

const getParkirData = (id,result) =>{
  return new Promise((resolve, reject) => {
    sql.query(`SELECT * FROM update_parkir WHERE uid = "${id}"`,(err,result) => {
        if(err){
          console.log('error when getting IDs data..')
          reject(err)
        }
        resolve(result)
    }); 
  });
}

const insertParkir = async (id,datetime) => {
  var IDs = await getParkirData(id);
  console.log('inserting parkir data...')
  console.log(IDs)
  if (IDs.length > 0){
    for (i = 0; i < IDs.length; i++) {
      // apabila tidak sedang parkir
      if (IDs[i].status == 0){
        new_status = 1
      // apabila mau keluar
      } else {
        new_status = -1
      }
      var query_str = `INSERT INTO parkir (id, time, uid, is_parkir) VALUES ?`;
      var values = [[null, datetime, id, new_status]];
      sql.query(query_str, [values], function (err, result) {
        if(err){
          console.log("error: ",err);
          return;
        }
        console.log('SUCCESS inserting parkir data!')
        return;
      });
      var query_str = `UPDATE update_parkir SET status = "${new_status}" WHERE uid = "${id}"`;
      sql.query(query_str, function (err, result) {
        if(err){
          console.log("error: ",err);
          return;
        }
        console.log('SUCCESS updating update_parkir data!')
        return;
      });
      break;
    }
  } else {
    var query_str = `INSERT INTO parkir (id, time, uid, is_parkir) VALUES ?`;
    var values = [[null, datetime, id, 1]];
    sql.query(query_str, [values], function (err, result) {
      if(err){
        console.log("error: ",err);
        return;
      }
      return;
    });
    var query_str = `INSERT INTO update_parkir (uid, status) VALUES ?`;
    var values = [[id, 1]];
    sql.query(query_str, [values], function (err, result) {
      if(err){
        console.log("error: ",err);
        return;
      }
      return;
    });
  }
}

const updatePersensi = async (id,time,matkul,kelas,is_attend,result) =>{
  var IDs = await getSaldoData(id);
  console.log('insert presensi data...')
  console.log(IDs)
  if (IDs.length > 0){
    for (i = 0; i < IDs.length; i++) {
      nim = IDs[i].nim
      var query_str = `INSERT INTO presensi (id,time,matkul,kelas,is_attend) VALUES ?`;
      var values = [[nim,time,matkul,kelas,is_attend]];
      sql.query(query_str, [values], function (err, result) {
        if(err){
          console.log("error: ",err);
          return;
        }
        console.log('SUCCESS inserting presensi data!')
        return;
      });
    }
  }
}

const updateTransaksi = async (id,time,new_saldo,result) =>{
  var IDs = await getSaldoData(id);
  console.log('insert transaksi data...')
  console.log(IDs)
  if (IDs.length > 0){
    for (i = 0; i < IDs.length; i++) {
      nim = IDs[i].nim
      amount = parseInt(IDs[i].saldo) - parseInt(new_saldo)
      console.log(parseInt(IDs[i].saldo),parseInt(new_saldo))
      console.log(nim,time,amount)
      if (amount > 0) {
        var query_str = `INSERT INTO transaksi (id,time,amount) VALUES ?`;
        var values = [[nim,time,amount]];
        sql.query(query_str, [values], function (err, result) {
          if(err){
            console.log("error: ",err);
            return;
          }
          console.log('SUCCESS inserting transaksi data!')
          
          var query_str = `UPDATE kartu SET saldo = "${new_saldo}" WHERE uid = "${id}"`;
          sql.query(query_str, function (err, result) {
            if(err){
              console.log("error: ",err);
              return;
            }
            console.log('SUCCESS updating saldo from kartu data!')
            return;
          });
          return;
        });
      }
    }
  }
}

const getSaldoData = (id,result) =>{
  console.log('getting saldo data...')
  return new Promise((resolve, reject) => {
    sql.query(`SELECT * FROM kartu WHERE uid = "${id}"`,(err,result) => {
        if(err){
          console.log('error when getting IDs data..')
          reject(err)
        }
        resolve(result)
    }); 
  });
}

client.on('connect', function () {
  console.log('connected...')
  client.subscribe('reader', function (err) {

    if (!err) {
      client.on('message', function (topic, message) {
        console.log(message.toString())
        msg = JSON.parse(message.toString())
        datetime = timeConverter(msg.timestamp)
        device = msg.payload.device
        uid = msg.payload.uid
        mode = msg.payload.mode
        try {
          saldo = msg.payload.saldo
        } catch {
          
        }
        console.log(`unix_time:${msg.timestamp}, time:${datetime}, device:${device}, uid:${uid}, mode:${mode}`)

        var query_str = `INSERT INTO all_data (timestamp, uid, device, mode) VALUES ?`;
        var values = [[datetime,uid,device,mode]];
        sql.query(query_str, [values], function (err, result) {
          if(err){
            console.log("error: ",err);
            result(err,null);
            return;
          }
        });

        // mode 0 = parkir
        if (mode == 0){
          console.log('handling parkir data...')
          insertParkir(uid,datetime)
        }
        // mode 1 = persensi
        else if (mode == 1) {
          console.log('handling presensi data...')
          if (device == '7C:9E:BD:F8:9B:38'){
            matkul ='IOT'
            kelas = 1
          } else {
            matkul ='ML'
            kelas = 2
          }
          updatePersensi(uid,datetime,matkul,kelas,1)
        }
        // mode 2 = transaksi
        else if (mode == 2) {
          console.log('handling transaksi data...')
          updateTransaksi(uid,datetime,saldo)
        }
        // mode 3 = inisialisasi
        else if (mode == 3) {
          console.log('inisialisasi kartu...')
          var query_str = `INSERT INTO kartu (uid, nama, saldo) VALUES ?`;
          var values = [[uid,null,null]];
          sql.query(query_str, [values], function (err, result) {
            if(err){
              console.log("error: ",err);
              result(err,null);
              return;
            }
          });
        }
      })
    } else {
      console.log('error get subscribe ')
    }
  })
})

const express = require("express");
const bodyParser = require("body-parser");
// const sql = require("./models/db.js");

const app = express();
var cors = require('cors')
app.use(cors())
// parse requests of content-type: application/json
app.use(bodyParser.json());

// parse requests of content-type: application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: true }));

// simple route
app.get("/", (req, res) => {
  res.json({ message: "iot-be-trial-connected..." });
});

require("./app/routes/presensi.routes.js")(app)
require("./app/routes/parkir.routes.js")(app)
require("./app/routes/transaksi.routes.js")(app)
require("./app/routes/initialize.routes.js")(app)

// set port, listen for requests
const PORT = process.env.PORT || 8080;

app.listen(PORT, console.log(`Server started on port ${PORT}`));

