#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <ESP32Servo.h>

// ---------------- Pin Configuration ----------------
#define TRIG_PIN   5
#define ECHO_PIN   18
#define BUZZER_PIN 19
#define SERVO_PIN  21

Servo myServo;
AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// WiFi Access Point
const char *ssid = "ESP32-Radar";
const char *password = "12345678";

long duration;
int distance;
int pos = 0;

// ---------------- HTML Radar Page ----------------
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>ESP32 Radar</title>
<style>
body { text-align:center; background:#000; color:#0f0; font-family:monospace; }
canvas { background:#111; border:2px solid #0f0; border-radius:50%; }
</style>
</head>
<body>
<h2>ESP32 Radar System</h2>
<canvas id="radar" width="400" height="400"></canvas>

<script>
var ws = new WebSocket("ws://" + location.hostname + ":81/");
var canvas = document.getElementById("radar");
var ctx = canvas.getContext("2d");

ws.onmessage = function(event){
    var data = event.data.split(",");
    var angle = data[0];
    var dist = data[1];

    ctx.clearRect(0,0,400,400);
    ctx.beginPath();
    ctx.arc(200,200,200,0,2*Math.PI);
    ctx.strokeStyle="#0f0";
    ctx.stroke();

    var rad = angle * Math.PI/180;
    var x = 200 + dist*Math.cos(rad);
    var y = 200 - dist*Math.sin(rad);

    ctx.fillStyle="red";
    ctx.fillRect(x,y,5,5);
}
</script>
</body>
</html>
)rawliteral";

// ---------------- Distance Function ----------------
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

// ---------------- Setup ----------------
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  myServo.attach(SERVO_PIN);

  WiFi.softAP(ssid, password);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.begin();
  webSocket.begin();
}

// ---------------- Loop ----------------
void loop() {
  webSocket.loop();

  for(pos = 0; pos <= 180; pos += 2) {
    myServo.write(pos);
    delay(20);

    distance = getDistance();

    if(distance < 20) {
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
    }

    String data = String(pos) + "," + String(distance);
    webSocket.broadcastTXT(data);
  }

  for(pos = 180; pos >= 0; pos -= 2) {
    myServo.write(pos);
    delay(20);

    distance = getDistance();

    String data = String(pos) + "," + String(distance);
    webSocket.broadcastTXT(data);
  }
}
