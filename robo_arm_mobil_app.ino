#include <WiFi.h>
#include <WebServer.h>
#include <Servo.h>

// ==== WiFi credentials (change these) ====
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ==== Servo setup ====
const int NUM_SERVOS = 6;
Servo servos[NUM_SERVOS];
int servoPins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7};
int basePos[NUM_SERVOS]   = {90, 90, 90, 90, 90, 90};

bool testRunning = false;
int testIndex = -1; // Which servo is being tested

WebServer server(80);

// ==== Function to test one servo ====
void testServo(int index) {
  if (index < 0 || index >= NUM_SERVOS) return;

  int currentPos = basePos[index];
  int direction = 1;

  // Infinite loop replaced by periodic execution in loop()
  testRunning = true;
  testIndex = index;
  servos[index].write(currentPos);
}

// ==== Stop test ====
void stopTest() {
  testRunning = false;
  testIndex = -1;
}

// ==== HTTP Handlers ====
void handleRoot() {
  server.send(200, "text/plain", "ESP32 Servo Controller is running!");
}

void handleTestServo() {
  if (!server.hasArg("index")) {
    server.send(400, "text/plain", "Missing index parameter");
    return;
  }
  int idx = server.arg("index").toInt();
  if (idx < 0 || idx >= NUM_SERVOS) {
    server.send(400, "text/plain", "Invalid servo index");
    return;
  }
  testServo(idx);
  String msg = "Testing servo " + String(idx);
  server.send(200, "text/plain", msg);
}

void handleStop() {
  stopTest();
  server.send(200, "text/plain", "Stopped all tests");
}

void setup() {
  Serial.begin(115200);

  // Attach servos
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(basePos[i]);
  }

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  // Setup HTTP routes
  server.on("/", handleRoot);
  server.on("/testServo", handleTestServo);
  server.on("/stop", handleStop);
  server.begin();
}

void loop() {
  server.handleClient();

  // If a test is active, oscillate the servo
  if (testRunning && testIndex >= 0) {
    static int currentPos = basePos[testIndex];
    static int direction = 1;

    currentPos += direction;
    servos[testIndex].write(currentPos);

    if (currentPos >= basePos[testIndex] + 20) direction = -1;
    if (currentPos <= basePos[testIndex] - 20) direction = 1;

    Serial.print("Servo ");
    Serial.print(testIndex);
    Serial.print(": ");
    Serial.println(currentPos);

    delay(20);
  }
}
