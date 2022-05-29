
#include "DeviceSetup.h"

AsyncWebServer server(80);                       // instantiate the webserver

struct deviceDetails {                           
  char wifiSSID[30];
  char wifiPassword[30];
  char deviceName[30];
  char emailAdd[30];
  char userName[15];
  bool isSetup;
};

// ----------------------------------------------------------------- H T M L   F I E L D   N A M E S -----------------------------------------------------------------
const char* WIFI_SSID_FIELD = "wifissid";        
const char* WIFI_PASS_FIELD = "wifipass";
const char* DEVICE_NAME_FIELD = "devname";
const char* EMAIL_ADD_FIELD = "emailadd";
const char* USER_NAME_FIELD = "username";

// ------------------------------------------------- S T R I N G S   T O   S T O R E    F I E L D    C O N T E N T S -------------------------------------------------
String wifiSSID;
String wifiPassword;
String deviceName;
String emailAdd;
String userName;

// -------------------------------------------------------------------- H T M L   W E B   F O R M --------------------------------------------------------------------
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Device Setup</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
  body{color:white; background-color:#141414; font-family: Helvetica, Verdana, Arial, sans-serif}
  h1{text-align:center;}
  p{text-align:center;}
  div{margin: 5%; background-color:#242424; padding:10px; border-radius:8px;}
  br{display: block; margin: 10px 0; line-height:22px; content: " ";}
  label{text-align:left; padding:2%;}
  input{border-radius: 4px; border: 2px solid #0056a8; width:90%; padding:10px; display:block; margin-right:auto; margin-left:auto;}
  input[type="submit"]{font-size: 25px; background-color:#0056a8; color:white; border-radius:8px; height:50px; width:95%;}
  </style>
  </head><body>
  <div>
    <h1>Device Setup</h1>
    <p>Please enter the following details to setup your device:</p>
    <form action="/get">
      <label>Wi-Fi Details</label>
      <br>
      <input type="text" name="wifissid" id="wifissid" placeholder="Wi-Fi SSID">
      <br>
      <input type="password" name="wifipass" id="wifipass" placeholder="Wi-Fi Password">
      <br>
      <label for="devname">Device Name</label>
      <br>
      <input type="text" name="devname" id="devname">
      <br>
      <label for="emailadd">Email Address</label>
      <br>
      <input type="email" name="emailadd" id="emailadd">
      <br>
      <label for="username">Your Name</label>
      <br>
      <input type="text" name="username" id="username">
      <br>
      <input type="submit" value="Submit">
    </form><br>
  </div>
</body></html>)rawliteral";

// ----------------------------------------------------------------- W E B P A G E   N O T   F O U N D -----------------------------------------------------------------
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

// ---------------------------------------------- G E T   C R E D E N T I A L S   V I A   W E B   A C C E S S   P O I N T ----------------------------------------------
struct deviceDetails getCredsViaWebAP()
{
  deviceDetails formSubmission{                                             // struct to store credentials
    "",
    "",
    "",
    "",
    "",
    false
  };

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){              // when the user goes to the server IP 
    request->send_P(200, "text/html", index_html);                          // send the contents of index_html (the web form)
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {         // when the user goes to the form submitted page
    
    if (request->hasParam(WIFI_SSID_FIELD)) {                               // if the wifi field has been filled out get the contents from each field and store in a string
      wifiSSID = request->getParam(WIFI_SSID_FIELD)->value();
      wifiPassword = request->getParam(WIFI_PASS_FIELD)->value();
      deviceName = request->getParam(DEVICE_NAME_FIELD)->value();
      emailAdd = request->getParam(EMAIL_ADD_FIELD)->value();
      userName = request->getParam(USER_NAME_FIELD)->value();
    }
    else {                                                                  // if the SSID field has no contents, then all fields have no contents
      wifiSSID = "";
      wifiPassword = "";
      deviceName = "";
      emailAdd = "";
      userName = "";
    }
    
    Serial.println(wifiSSID);                                               // print out the contents of all fields
    Serial.println(wifiPassword);
    Serial.println(deviceName);
    Serial.println(emailAdd);
    Serial.println(userName);

    // \/ send the form submission page \/
    request->send(200, "text/html", "<meta name=viewport content=width=device-width, initial-scale=1><style>body{color:white; text-align:center; background-color:#141414; font-family: Helvetica, Verdana, Arial, sans-serif}div{margin: 5%; background-color:#242424; padding:10px; border-radius:8px;}br{display: block; margin: 10px 0; line-height:22px; content: " ";}table{margin-left: auto; margin-right: auto;}</style>"
                                    "<body><div><h1>Device Settings</h1>"
                                    "<table><tr><td><b>Wi-Fi SSID: </b></td><td>" + wifiSSID
                                  + "</td></tr><tr><td><b>Wi-Fi Password: </b></td><td>" + wifiPassword
                                  + "</td></tr><tr><td><b>Device Name: </b></td><td>" + deviceName 
                                  + "</td></tr><tr><td><b>Email Address: </b></td><td>" + emailAdd 
                                  + "</td></tr><tr><td><b>Your Name: </b></td><td>" + userName + "</td></tr></table>");
  });
  server.onNotFound(notFound);   // if the webpage can't be found, send a 404
  server.begin();


  
  while(1)                                                         // loop forever (wait)     
  {
    if (wifiSSID != "")                                            // if the wifi ssid is not empty
    { 
      Serial.println("Form Submitted");                            // print to the console that the form has been submitted

      wifiSSID.toCharArray(formSubmission.wifiSSID, 30);           // convert all of the strings to char arrays and populate the formSubmission struct
      wifiPassword.toCharArray(formSubmission.wifiPassword, 30);
      deviceName.toCharArray(formSubmission.deviceName, 30);
      emailAdd.toCharArray(formSubmission.emailAdd, 30);
      userName.toCharArray(formSubmission.userName, 15);

      formSubmission.isSetup = true;                               // mark the setup as complete
    
      return formSubmission;                                       // return the contents of the formSubmission struct
    }   
  }
}
