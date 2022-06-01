const sql = require("./db.js");

// constructor
const Initialize  = function(presensi) {
  this.id = presensi.id;
  this.waktu = presensi.waktu;
  this.kelas = presensi.kelas;
};

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

const mqtt = require('mqtt')

const client  = mqtt.connect(connect_url, options)

Initialize.requestToSystem = (result) => {
    client.on('connect', () => {
        console.log('connecting to system...')
        client.publish('reader', 'get initialize request message...', { qos: 0, retain: false }, (error) => {
            if (error) {
                console.log('Error when sending data')
                or(error)
            } else {
                console.log('data sent!')
                client.subscribe('reader', function (err) {

                    if (!err) {
                      client.on('message', function (topic, message) {
                        console.log(message.toString())
                      });
                    } else {
                        console.log("Can't subscribe publised data...")
                    }
                });
            }
        })
    })
    result(null,{'message':'send request data to system...'})
    return;
};

Initialize.getData = (matkul,kelas,result) => {
	console.log(`Get presensi data from maetkul ${matkul} kelas ${kelas}`)
	sql.query(`SELECT matkul, kelas, date_format(time, '%Y-%m-%d') as date, COUNT(id) as jumlah FROM presensi WHERE matkul = "${matkul}" AND kelas = ${kelas} GROUP BY matkul, kelas, date_format(time, '%Y-%m-d')`,(err,res) => {
		if(err){
			console.log("error: ",err);
			result(err,null);
			return;
		}
		result(null,res);
		return;
	});
};

module.exports = Initialize;