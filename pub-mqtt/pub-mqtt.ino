#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 4
#define DHTTYPE    DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// Update these with values suitable for your network.

const char* ssid = "Your-WiFi-SSID";
const char* password = "Your-WiFi-Password";
const char* mqtt_server = "<Your-MQTT-Server>";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int units_prod = 0;
int humidity_per = 0;
int temperature_cel = 0;

int machinceState1 = 0;
int machinceState2 = 0;
int machinceState3 = 0;
int machinceState4 = 0;
int machinceState5 = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  sensor_t sensor;
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
    
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;

    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    }
    else {
      Serial.print(F("Temperature: "));
      temperature_cel = event.temperature;
      Serial.print(temperature_cel);
      Serial.println(F("°C"));
    }
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println(F("Error reading humidity!"));
    }
    else {
      Serial.print(F("Humidity: "));
      humidity_per = event.relative_humidity;
      Serial.print(humidity_per);
      Serial.println(F("%"));
    }

    machinceState1 = digitalRead(2);
    machinceState2 = digitalRead(14);
    machinceState3 = digitalRead(12);
    machinceState4 = digitalRead(13);
    machinceState5 = digitalRead(15);
    
    ++units_prod;
    int machines = 5;
    int running_machines = machinceState1 + machinceState2 + machinceState3 + machinceState4 + machinceState5;
    int units_def = random(0, 5);
    int energy_mach_1 = random(80, 120);
    int energy_mach_2 = random(80, 120);
    int energy_mach_3 = random(80, 120);
    int energy_mach_4 = random(80, 120);
    int energy_mach_5 = random(80, 120);

// Sensor data
    snprintf (msg, MSG_BUFFER_SIZE, "%ld", humidity_per);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Factory/factory1/sensor/humidity", msg);

    snprintf (msg, MSG_BUFFER_SIZE, "%ld", temperature_cel);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Factory/factory1/sensor/temperature", msg);

// Machine data
    snprintf (msg, MSG_BUFFER_SIZE, "%ld", machines);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Factory/factory1/machines/number", msg);

    snprintf (msg, MSG_BUFFER_SIZE, "%ld", running_machines);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Factory/factory1/machines/running", msg);

// Unit Data
    snprintf (msg, MSG_BUFFER_SIZE, "%ld", units_prod);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Factory/factory1/units/produced", msg);
    
    snprintf (msg, MSG_BUFFER_SIZE, "%ld", units_def);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Factory/factory1/units/defected", msg);

// Energy Data
    snprintf (msg, MSG_BUFFER_SIZE, "%ld", energy_mach_1);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Factory/factory1/energy/machine1", msg);

    snprintf (msg, MSG_BUFFER_SIZE, "%ld", energy_mach_2);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Factory/factory1/energy/machine2", msg);

    snprintf (msg, MSG_BUFFER_SIZE, "%ld", energy_mach_3);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Factory/factory1/energy/machine3", msg);

    snprintf (msg, MSG_BUFFER_SIZE, "%ld", energy_mach_4);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Factory/factory1/energy/machine4", msg);

    snprintf (msg, MSG_BUFFER_SIZE, "%ld", energy_mach_5);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Factory/factory1/energy/machine5", msg);

    Serial.println(" ");

  }
}
