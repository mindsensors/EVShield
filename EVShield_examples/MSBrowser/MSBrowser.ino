#include <EVShield.h>
#include <EVs_UIModule.h>
#include <ArduinoOTA.h>

const char* ssid     = "your_WiFi_network";
const char* password = "letmein";
const char* uploadPassword = "upload";

EVShield ev;
EVs_UIModule uim;

int iteration = -1;

void setup1() {
    uim.println("This is setup1 running");
}
void loop1() {
    uim.fillRect(++iteration%320, 30+iteration/320, 1, 1, EVs_UIM_RED);
    if (iteration > 5000) ESP.reset();
}

void setup2() {
    uim.println("This is setup2 running");
}
void loop2() {
    uim.fillRect(++iteration%320, 30+iteration/320, 1, 1, EVs_UIM_GREEN);
    if (iteration > 320*(240-30)) {
        uim.clearScreen();
        iteration = -1;
    }
}

void setup3() {
    uim.println("This is setup3 running");
}
void loop3() {
    uim.fillRect(++iteration%320, 30+iteration/320, 1, 1, EVs_UIM_BLUE);
}





void delayWithOTA(unsigned long delayMs) {
  unsigned long timeout = millis() + delayMs;
  do { // using a do while loop so ArduinoOTA.handle() will be called at least once in the case of delay(0);
    ArduinoOTA.handle();
    yield(); // remember to call the *function* yield, not the keyword
  } while (millis() < timeout);
}
#define delay(ms) delayWithOTA(ms)

int selection;

void changeSelection(int newProgramSelection);

void setup() {
    Serial.begin(115200);
    Serial.println();
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) yield();
    ArduinoOTA.setPassword(uploadPassword);
    ArduinoOTA.begin();
    
    ArduinoOTA.onStart([]() {
        uim.setRotation(3);
        uim.clearScreen();
        uim.setTextColor(EVs_UIM_WHITE);
        uim.setCursor(0, 0);
        uim.setTextSize(2);
        uim.println("Beginning OTA upload!");
        uim.print("Progress: ");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        int preX = uim.getCursorX();
        uim.fillRect(preX, 16, 35, 16, EVs_UIM_BLACK);
        uim.print(progress / (total / 100));
        uim.print("%");
        uim.setCursor(preX, 16);
    });
    ArduinoOTA.onError([](ota_error_t error) {
        uim.printf("\nError[%u]: ", error);
             if (error == OTA_AUTH_ERROR)    uim.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR)   uim.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) uim.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) uim.println("Receive Failed");
        else if (error == OTA_END_ERROR)     uim.println("End Failed");
    });
    ArduinoOTA.onEnd([]() {
        ESP.reset();
    });
    
    ev.init();
    uim.begin();
    uim.clearScreen();
    
    uim.setTextSize(4);
    
    uim.fillRect(35, 30, 60, 60, EVs_UIM_RED);
    uim.setCursor(35+10, 30+16);
    uim.println("P1");
    
    uim.fillRect(130, 30, 60, 60, uim.Color565(0,200,0)); //EVs_UIM_GREEN
    uim.setCursor(130+8, 30+16);
    uim.println("P2");
    
    uim.fillRect(225, 30, 60, 60, EVs_UIM_BLUE);
    uim.setCursor(225+8, 30+16);
    uim.println("P3");
    
    uim.fillRect(0, 120, 320, 2, EVs_UIM_WHITE);
    
    uim.fillRect(70, 151, 180, 60, EVs_UIM_WHITE);
    uim.setTextColor(EVs_UIM_BLACK, EVs_UIM_WHITE);
    uim.setCursor(138, 151+16);
    uim.println("GO");
    
    selection = 2; // make sure border gets drawn (this is a "change")
    changeSelection(1);
}

void loop() {
    if (ev.checkButton( 35, 30, 60, 60)) changeSelection(1);
    if (ev.checkButton(130, 30, 60, 60)) changeSelection(2);
    if (ev.checkButton(225, 30, 60, 60)) changeSelection(3);
    
    if (ev.checkButton(70, 151, 180, 60)) {
        uim.clearScreen();
        uim.setTextSize(2);
        uim.setTextColor(EVs_UIM_WHITE);
        uim.setCursor(0, 0);
        
             if (selection == 1) setup1();
        else if (selection == 2) setup2();
        else if (selection == 3) setup3();
        
             if (selection == 1) while(true) { loop1(); delay(1); }
        else if (selection == 2) while(true) { loop2(); delay(1); }
        else if (selection == 3) while(true) { loop3(); delay(1); }
    }
    
    delay(10);
}

void changeSelection(int n) {
    if (n == selection) return;
    
    const int b = 5; // border width;
    // black-out old border
    int x = 35+(selection-1)*95;
    uim.fillRect(x-b, 30-b, 60+2*b, b, EVs_UIM_BLACK); // top
    uim.fillRect(x-b, 30+60, 60+2*b, b, EVs_UIM_BLACK); // bottom
    uim.fillRect(x-b, 30, b, 60, EVs_UIM_BLACK); // left
    uim.fillRect(x+60, 30, b, 60, EVs_UIM_BLACK); // right
    
    selection = n;
    // draw new border
    x = 35+(selection-1)*95;
    uim.fillRect(x-b, 30-b, 60+2*b, b, EVs_UIM_WHITE); // top
    uim.fillRect(x-b, 30+60, 60+2*b, b, EVs_UIM_WHITE); // bottom
    uim.fillRect(x-b, 30, b, 60, EVs_UIM_WHITE); // left
    uim.fillRect(x+60, 30, b, 60, EVs_UIM_WHITE); // right
}
