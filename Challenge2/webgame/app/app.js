import * as mqtt from "mqtt"  // import everything inside the mqtt module and give it the namespace "mqtt"
import express from "express";
import { Server } from "socket.io";
import http from "http";
import {exec} from 'child_process'
/*
@lcoal with mosquitto:
username: admin
password: 1234

@subscribe:
mosquitto_sub -d -u admin -P 1234 -t webgame


@publish:
mosquitto_pub -d -u admin -P 1234 -t webgame -m "idle"

*/
// disable keys
let isdisabled = false


function disableKeys(){
  if(isdisabled) return console.log('already disabled')
  isdisabled=true
  exec('bash /home/pi/webgame/disablekeys', (error, stdout, stderr)=>{
      if(error) console.log(error)
      if(stderr) console.log(stderr)
      if(stdout) console.log(stdout)
  })
}

/* MQTT SERVER CONST */
const host ='192.168.50.45' //'192.168.50.20' // IP address of the MQTT server
const mqtt_port = '1883' // Port of the MQTT server
const clientId = `mqtt_webgame_${Math.random().toString(16).slice(3)}` // Generate a random client ID

const connectUrl = `mqtt://${host}:${mqtt_port}`

const client = mqtt.connect(connectUrl, {
  clientId,
  clean: true,
  connectTimeout: 4000,
  username: 'admin',
  password: '1234',
  reconnectPeriod: 1000,
})

// In&out-box from the prop
const publishTopic =  'Room/squad1/Props/webgame/outbox'
const subscribeTopic = 'Room/squad1/Props/webgame/inbox'

const app = express();
const server = http.createServer(app)
const port = 9919
const __dirname = process.cwd()
const io = new Server(server)


client.on('connect', () => {
  console.log('Mqtt status: connecting..')
  client.subscribe([subscribeTopic], () => {
    console.log(`Mqtt status: connected. Subscribed to topic '${subscribeTopic}'`)
  })
})



client.on('message', (publishTopic, payload) => {
    const message = payload.toString();
    
    console.log('message:', message)
    
    io.emit('state', message)
})


client.on('connect', () => {
    client.publish(publishTopic, 'test connection: 2 way handshake', { qos: 0, retain: false }, (error) => {
      if (error) {
          console.error(error)
      }
    })
})


// functions
function publishEnd(str) {
  client.publish(publishTopic, "game:end", { qos: 0, retain: false }, (error) => {
      if (error) {
          console.error(error)
      }
  })
  //client.send(str)
}


// app routing
app.use(express.static('src'));



app.get('/', (req, res) => {    

  disableKeys()
  res.sendFile('src/login/login.html', { root: __dirname})
  
})



app.get('/game', (req, res) => {
  res.sendFile('src/game/game.html', { root: __dirname })

})


app.get('/won', (req, res) => {
  publishEnd()
  res.sendFile('src/endscreen/endscreen.html', { root: __dirname })
})


app.get('/idle', (req, res) => {
  res.sendFile('src/idle/idle.html', { root: __dirname })
})

app.get('*', (req, res) => {
  res.redirect('/')
})



server.listen(port, () => {
  console.log(`App on port: ${port}`) 
})


