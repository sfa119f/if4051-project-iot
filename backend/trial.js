const host = 'localhost'
const port = '8080'
const connect_url = `mqtt://${host}:${port}`
const clientID = '3441ae5a865a4815b2769d77fda5bbf6'
const username = 'app-appktmxemoney'

const mqtt = require('mqtt')

const client  = mqtt.connect(connect_url)

// client.on('connect', () => {
//     console.log("Connected to MQTT Broker");
    
//     // When receiving message
//     client.on('message', (topic, message, packet) => {
//         // Session Start
//         if((topic == 'waterHeightDetectorEFSS') && (!sessionStart)){
//             console.log("Initiate Session");
//             sensorTimer()
//             sessionTimer()

//             let session = new SessionData({
//                 start_time: new Date().toISOString()
//             })

//             console.log(session);
//             // Subscribe to another sensor topics
//             client.subscribe('alertActuatorEFSS');
//             client.subscribe('waterHeightAlertEFSS');
//             client.subscribe('raindropSensorEFSS');

//             session.save();

//             sessionId = session.start_time;
//             sessionStart = true;
//         }

//         // Receive Data
//         if(sessionStart) {
//             console.log("Receive Data from ", topic, "with data", JSON.parse(message.toString()));

//             if(topic == "waterHeightDetectorEFSS"){
//                 clearTimeout(resetSensorTimer);
//                 sensorTimer();
//             }
//             collectSessionData(topic, message, packet, sessionId);
//         }
//     })

// })

client.on('connect', function () {
  client.subscribe('reader', function (err) {
    if (!err) {
      client.publish('reader', '{"timestamp":1652968991775,"payload":{"12":"123"}}')
    }
  })
})

client.on('message', function (topic, message) {
  // message is Buffer
  console.log(message.toString())
  client.end()
})