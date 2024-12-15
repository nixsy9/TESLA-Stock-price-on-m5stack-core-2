before compiling add your API KEY along with wifi password and SSID insode the code to 

// WiFi credentials
const char* ssid = "PUT YOUR WIFI SSID IN HERE";
const char* password = "AND ITS PASSWORD HERE";

// Finnhub API endpoint for Tesla quote data //REPLACE API-KEY-HERE with your free api from https://finnhub.io/
const String stockAPI = "https://finnhub.io/api/v1/quote?symbol=TSLA&token=API-KEY-HERE";

make sure platformio is enabled inside vscode hit compile and then upload to your core 2

BIG THanks to Lexx he did 99% of the code and big thanks to https://finnhub.io/ for the api in the first place making this possible

