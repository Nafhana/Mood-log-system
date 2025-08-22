#include <WiFi.h>
#include <HTTPClient.h>
#include <NetworkClientSecure.h>

const char* FavoriotCA PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIF3TCCA8WgAwIBAgIIeyyb0xaAMpkwDQYJKoZIhvcNAQELBQAwfDELMAkGA1UE
BhMCVVMxDjAMBgNVBAgMBVRleGFzMRAwDgYDVQQHDAdIb3VzdG9uMRgwFgYDVQQK
DA9TU0wgQ29ycG9yYXRpb24xMTAvBgNVBAMMKFNTTC5jb20gUm9vdCBDZXJ0aWZp
Y2F0aW9uIEF1dGhvcml0eSBSU0EwHhcNMTYwMjEyMTczOTM5WhcNNDEwMjEyMTcz
OTM5WjB8MQswCQYDVQQGEwJVUzEOMAwGA1UECAwFVGV4YXMxEDAOBgNVBAcMB0hv
dXN0b24xGDAWBgNVBAoMD1NTTCBDb3Jwb3JhdGlvbjExMC8GA1UEAwwoU1NMLmNv
bSBSb290IENlcnRpZmljYXRpb24gQXV0aG9yaXR5IFJTQTCCAiIwDQYJKoZIhvcN
AQEBBQADggIPADCCAgoCggIBAPkP3aMrfcvQKv7sZ4Wm5y4bunfh4/WvpOz6Sl2R
xFdHaxh3a3by/ZPkPQ/CFp4LZsNWlJ4Xg4XOVu/yFv0AYvUiCVToZRdOQbngT0aX
qhvIuG5iXmmxX9sqAn78bMrzQdjt0Oj8P2FI7bADFB0QDksZ4LtO7IZl/zbzXmcC
C52GVWH9ejjt/uIZALdvoVBidXQ8oPrIJZK0bnoix/geoeOy3ZExqysdBP+lSgQ3
6YWkMyv94tZVNHwZpEpox7Ko07fKoZOI68GXvIz5HdkihCR0xwQ9aqkpk8zruFvh
/l8lqjRYyMEjVJ0bmBHDOJx+PYZspQ9AhnwC9FwCTyjLrnGfDzrIM/4RJTXq/LrF
YD3ZfBjVsqnTdXgDciLKOsMf7yzlLqn6niy2UUb9rwPW6mBo6oUWNmuF6R7As93E
JNyAKoFBbZQ+yODJgUEAnl6/f8UImKIYLEJAs/lvOCdLToD0PYFH4Ih86hzOtXVc
US4cK38acijnALXRdMbX5J+tB5O2UzU1/Dfkw/ZdFr4hc96SCvigY2q8lpJqPvi8
ZVWb3vUNiSYE/CUapiVpy8JtynziWV+XrOvvLsi81xtZPCvM8hnIk2snYxnP/Okm
+Mpxm3+T/jRnhE6Z6/yzeAkzcLpmpnbtG3PrGqUNxCITIJRWCk4sbE6x/c+cCbqi
M+2HAgMBAAGjYzBhMB0GA1UdDgQWBBTdBAkHovV6fVJTEpKV7jiAJQ2mWTAPBgNV
HRMBAf8EBTADAQH/MB8GA1UdIwQYMBaAFN0ECQei9Xp9UlMSkpXuOIAlDaZZMA4G
A1UdDwEB/wQEAwIBhjANBgkqhkiG9w0BAQsFAAOCAgEAIBgRlCn7Jp0cHh5wYfGV
cpNxJK1ok1iOMq8bs3AD/CUrdIWQPXhq9LmLpZc7tRiRux6n+UBbkflVma8eEdBc
Hadm47GUBwwyOabqG7B52B2ccETjit3E+ZUfijhDPwGFpUenPUayvOUiaPd7nNgs
PgohyC0zrL/FgZkxdMF1ccW+sfAjRfSda/wZY52jvATGGAslu1OJD7OAUN5F7kR/
q5R4ZJjT9ijdh9hwZXT7DrkT66cPYakylszeu+1jTBi7qUD3oFRuIIhxdRjqerQ0
cuAjJ3dctpDqhiVAq+8zD8ufgr6iIPv2tS0a5sKFsXQP+8hlAqRSAUfdSSLBv9jr
a6x+3uxjMxW3IwiPxg+NQVrdjsW5j+VFP3jbutIbQLH+cU0/4IGiul607BXgk90I
H37hVZkLId6Tngr75qNJvTYw/ud3sqB1l7UtgYgXZSD32pAAn8lSzDLKNXz1PQ/Y
K9f1JmzJBjSWFupwWRoyeXkLtoh/D1JIPb9s2KJELtFOt3JY04kTlf5Eq/jXixtu
nLwsoFvVagCvXzfh1foQC5ichucmj87w7G6KVwuA406ywKBjYZC6VWg3dGq2ktuf
oYYitmUnDuy2n0Jg5GfCtdpBC8TTi2EbvPofkSvXRAdeuims2cXp71NIWuuA8ShY
Ic2wBlX7Jz9TkHCpBB5XJ7k=
-----END CERTIFICATE-----
)EOF";

// WiFi credentials
const char ssid[] = "ihdp";
const char password[] = "ihdpihdp";

// Favoriot credentials
const char deviceDeveloperId[] = "HibiscusSense@nfamfariha";
const char deviceAccessToken[] = "zAWgQSlQFXsVwoqk1iRylR3Tz6AaJuDk";

String userInput = "";
String currentMood = "";
bool waitingForMood = true;
bool waitingForScale = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to WiFi...");
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  promptMood();
}

void promptMood() {
  Serial.println("\nHow are you feeling today?");
  Serial.println("A = Happy");
  Serial.println("B = Sad");
  Serial.println("C = Excited");
  Serial.println("D = Tired");
  Serial.print("Enter A-D: ");
  waitingForMood = true;
  waitingForScale = false;
  userInput = "";
}

void promptScale() {
  Serial.print("\nOn a scale of 1–5, how strong is your feeling of ");
  Serial.print(currentMood);
  Serial.println("? (1 = low, 5 = strong)");
  waitingForMood = false;
  waitingForScale = true;
  userInput = "";
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (userInput.length() > 0) {
        userInput.trim();
        userInput.toUpperCase();

        if (waitingForMood) {
          if (userInput == "A") currentMood = "Happy";
          else if (userInput == "B") currentMood = "Sad";
          else if (userInput == "C") currentMood = "Excited";
          else if (userInput == "D") currentMood = "Tired";
          else {
            Serial.println("Invalid mood option. Please enter A, B, C or D.");
            promptMood();
            return;
          }

          promptScale();

        } else if (waitingForScale) {
          int scale = userInput.toInt();
          if (scale < 1 || scale > 5) {
            Serial.println("Invalid scale. Enter a number between 1 and 5.");
            promptScale();
            return;
          }

          // Build JSON
          String json = "{\"device_developer_id\":\"" + String(deviceDeveloperId) + "\",\"data\":{";
          json += "\"mood\":\"" + currentMood + "\",";
          json += "\"scale\":\"" + String(scale) + "\"";
          json += "}}";

          // Send to Favoriot
          Serial.println("\nSending mood to Favoriot...");
          NetworkClientSecure *client = new NetworkClientSecure;
          if (client) {
            client->setCACert(FavoriotCA);
            HTTPClient https;
            https.begin(*client, "https://apiv2.favoriot.com/v2/streams");
            https.addHeader("Content-Type", "application/json");
            https.addHeader("Apikey", deviceAccessToken);
            int httpCode = https.POST(json);

            if (httpCode > 0) {
              Serial.print("HTTPS Response: ");
              Serial.println(httpCode);
              Serial.println(https.getString());
            } else {
              Serial.print("Request failed: ");
              Serial.println(httpCode);
            }

            https.end();
            delete client;
          }

          // Reset for next entry
          Serial.println("\nThank you! Logged your mood successfully.");
          promptMood();
        }

      }
    } else {
      userInput += c;
    }
  }
}
