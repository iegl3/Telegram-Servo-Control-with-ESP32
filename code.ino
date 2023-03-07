#include <Servo.h>
#include <WiFi.h>
#include <UniversalTelegramBot.h>

// Replace with your network credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

// Initialize Telegram BOT
#define BOTtoken "<your_bot_token>"

WiFiClient client;
UniversalTelegramBot bot(BOTtoken, client);

// Create a new servo object
Servo servo;

void handleNewMessages(int numNewMessages) {
Serial.println("handleNewMessages");
Serial.println(String(numNewMessages));

for (int i=0; i<numNewMessages; i++) {
// Chat id of the requester
String chat_id = String(bot.messages[i].chat_id);

String text = bot.messages[i].text;

Serial.println(text);

if (text == "/on") {
  servo.write(0);
} else if (text == "/off") {
  servo.write(90);
}
}
}

void setup() {
Serial.begin(115200);
servo.attach(2); // Pin D4

// Connect to Wi-Fi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// Set Telegram bot token
bot.updateToken(BOTtoken);
}

void loop() {
// Check for new messages
bot.getUpdates(0L);
}
