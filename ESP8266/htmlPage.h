#ifndef HTMLPAGE_H
#define HTMLPAGE_H

const char *htmlPage=
"\
<!DOCTYPE html><html>\
<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
<link rel=\"icon\" href=\"data:,\">\
\
<!-- //// CSS for styling -->\
<style> \
  html { \
    font-family: Helvetica; \
    display: inline-block; \
    margin: 0px auto; \
    text-align: center;\
  }\
\
  .button { \
    background-color: #195B6A;\
    border: none; \
    color: white; \
    padding: 16px 40px;\
    text-decoration: none; \
    font-size: 30px; \
    margin: 2px; \
    cursor: pointer;\
  }\
\
  .slider {\
      -webkit-appearance: none;\
      width: 100%;\
      height: 15px;\
      border-radius: 5px;\
      background: #d3d3d3;\
      outline: none;\
      opacity: 0.7;\
      -webkit-transition: .2s;\
      transition: opacity .2s;\
  }\
\
  .slider::-webkit-slider-thumb {\
      -webkit-appearance: none;\
      appearance: none;\
      width: 25px;\
      height: 25px;\
      border-radius: 50%; \
      background: #4CAF50;\
      cursor: pointer;\
  }\
\
  .slider::-moz-range-thumb {\
      width: 25px;\
      height: 25px;\
      border-radius: 50%;\
      background: #4CAF50;\
      cursor: pointer;\
  }\
</style>\
<!-- end CSS -->\
\
<!-- //// javascript -->\
<script>\
  var slider = document.getElementById(\"servoRange\");\
  var textOutput = document.getElementById(\"degreeText\");\
  var setOpenBlindsHRef = document.getElementById(\"setOpenBlinds\");\
  var setCloseBlindsHRef = document.getElementById(\"setCloseBlinds\");\
  textOutput.innerHTML = slider.value;\
\
  slider.oninput = function() {\
    textOutput.innerHTML = this.value;\
  }\
\
</script>\
\
<!-- javascript for submitting open/close settings -->\
<script>\
\
  function setOpenBlinds() {\
    setOpenBlindsText.innerHTML = slider.value;\
    setOpenBlindsHRef.href = '/setOpenBlinds=\"' + slider.value + '\"';\
  }\
\
  function setCloseBlinds() {\
    setCloseBlindsText.innerHTML = slider.value;\
    setCloseBlindsHRef.href = '/setCloseBlinds=\"' + slider.value + '\"';\
  }\
\
</script>\
</head>\
\
<!-- //// HTML -->\
<body>\
  <h1>ESP8266 Web Server</h1>\
\
  <!-- servo slider -->\
  <div class=\"slidecontainer\">\
    <input type=\"range\" min=\"0\" max=\"200\" value=\"0\" class=\"slider\" id=\"servoRange\">\
    <p>Servo degrees: <span id=\"degreeText\"></span></p>\
  </div>\
\
  <!-- open blinds action button -->\
  <p><a href=\"/openBlinds\"><button class=\"button\">Open blinds</button></a></p>\
  <p><a href=\"#\" id=\"setOpenBlinds\" onclick=\"setOpenBlinds();\"><button class=\"button\">Set blinds open</button></a></p>\
  <p>Open setting: <span id=\"setOpenBlindsText\"></span></p>\
\
  <!-- close blinds action button -->\
  <p><a href=\"/closeBlinds\"><button class=\"button\">Close blinds</button></a></p>\
  <p><a href=\"#\" id=\"setCloseBlinds\" onclick=\"setCloseBlinds();\"><button class=\"button\">Set blinds closed</button></a></p>\
  <p>Close setting: <span id=\"setCloseBlindsText\"></span></p>\
\
  <!-- formatters for the NIST time -->\
  <p>Local Time (24hr): %02d:%02d:%02d</p>\
\
</body></html> \
";

#endif //HTMLPAGE_H